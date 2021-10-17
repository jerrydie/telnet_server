#include "server.hpp"

#include <iostream>
#include <stdint.h>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
namespace bai = boost::asio::ip;

namespace hse::Telnet 
{
	Server::Server(ba::io_service& io_service, uint16_t port)
	    : ios(io_service), acpt(io_service, bai::tcp::endpoint(bai::tcp::v4(), port))
	{
	    start_accept();
	}
	
	void Server::start_accept()
	{
	    std::cout << "TelnetServer::start_accept\n"; // вывод для просмотра процесса работы программы
	    Session* new_session = new Session(ios);
	    std::cout << "New session created by the server\n"; // вывод для просмотра процесса работы программы
	    acpt.async_accept(new_session->socket(), boost::bind(&Server::handle_accept, this, new_session, ba::placeholders::error));
	}

	void Server::handle_accept(Session* new_session, const bs::error_code& error)
	{
	    if (!error)
	    {
		std::cout << "TelnetServer::handle_accept starting session\n"; // вывод для просмотра процесса работы программы
		new_session->start();
	    }
	    else
	    {
		std::cerr << "TelnetServer::handle_accept error: " << error << '\n';
		delete new_session;
	    }

	    start_accept();
	}
}
