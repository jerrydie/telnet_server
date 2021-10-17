#include "session.hpp"
#include "server.hpp"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <boost/bind/bind.hpp>
#include <vector>

namespace ba = boost::asio;
namespace bs = boost::system;
namespace bp = boost::process;
namespace bai = boost::asio::ip;

namespace hse::Telnet
{

	Session::Session(ba::io_service& io_service)
	    : socket_(io_service), ap(io_service), shell(getenv("SHELL")) {}

	void Session::start()
	{
	    std::cout << "Telnet session started\n"; // вывод для просмотра процесса работы программы
	    socket_.async_read_some(boost::asio::buffer(buffer, max_length),
		boost::bind(&Session::handle_read, this, ba::placeholders::error, ba::placeholders::bytes_transferred));
	}

	void Session::handle_read(const bs::error_code& error, size_t bytes_transferred)
	{
	    if (!error)
	    {
		std::cout << "Session::handle_read " << (int) bytes_transferred << " bytes\n";
		for (int i = 0; i < bytes_transferred; i++)
			shell_file_buffer.push_back(buffer[i]);
		// Если команда не дочиталась, продолжаем чтение
		if (bytes_transferred == max_length) {
			socket_.async_read_some(ba::buffer(buffer, max_length),
		    		boost::bind(&Session::handle_read, this, ba::placeholders::error, ba::placeholders::bytes_transferred));
		}
		// Если название дочиталось, запускаем файл на асинхронное выполнение, результат записываем в пайп
		// и пишем его в сокет.
		else {

			bp::child c(shell, shell_file_buffer.data(), bp::std_out > ap);
			ba::async_read(ap, ba::buffer(result_buffer), [](const bs::error_code &ec, std::size_t size){});
			c.wait();
			if (c.exit_code() == 0)
				ba::async_write(socket_, ba::buffer(result_buffer), 
				   	boost::bind(&Session::handle_write, this, ba::placeholders::error));
			else
			{
				std::cerr << "Session::handle_read child error occured. Session terminated.\n";
				delete this;
			}
		}
	    }
	    else
	    {
		std::cerr << "Session::handle_read error: " << error << '\n';
		delete this;
	    }
	}

	void Session::handle_write(const bs::error_code& error)
	{
	    if (!error)
	    {
		std::cout << "Session::handle_write\n";
		shell_file_buffer.clear();
		socket_.async_read_some(ba::buffer(buffer, max_length),
		    boost::bind(&Session::handle_read, this, ba::placeholders::error, ba::placeholders::bytes_transferred));
	    }
	    else
	    {
		std::cerr << "Session::handle_write error: " << error << '\n';
		delete this;
	    }
	}
}
