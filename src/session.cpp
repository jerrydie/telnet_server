#include "session.hpp"
#include "server.hpp"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
namespace bait = boost::asio::ip::tcp;

namespace hse::Telnet
{
	Session::Session(ba::io_service& io_service)
	    : socket_(io_service) {}

	void Session::start()
	{
	    std::cout << "Telnet session started\n"; // вывод для просмотра процесса работы программы
	    mSocket.async_read_some(boost::asio::buffer(buffer, max_length),
		boost::bind(&Session::handle_read, this,
		    ba::placeholders::error, ba::placeholders::bytes_transferred));
	}

	void Session::handle_read(const bs::error_code& error, size_t bytes_transferred)
	{
	    if (!error)
	    {
		std::cout << "Session::handle_read " << (int) bytes_transferred << " bytes\n";
		ba::async_write(socket_, ba::buffer(buffer, bytes_transferred), 
		                boost::bind(&Session::handle_write, this, ba::placeholders::error));
	    }
	    else
	    {
		std::cerr << "Session::handle_read error: " << error << std::endl;
		delete this;
	    }
	}

	void Session::handle_write(const bs::error_code& error)
	{
	    if (!error)
	    {
		std::cout << "Session::handle_write\n";
		socket_.async_read_some(ba::buffer(buffer, max_length),
		    boost::bind(&Session::handle_read, this, ba::placeholders::error, ba::placeholders::bytes_transferred));
	    }
	    else
	    {
		std::cerr << "Session::handle_write error: " << error << std::endl;
		delete this;
	    }
	}
}
