#ifndef __SESSION_HPP__
#define __SESSION_HPP__

#include <boost/asio.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
namespace bait = boost::asio::ip::tcp;

namespace hse::Telnet 
{
	class Session
	{
	public:
	    Session(ba::io_service& io_service);

	    bait::socket& socket() { return socket_; }

	    void start();

	    auto max_length = 3;

	private:
	    void handle_read(const bs::error_code& error, size_t bytes_transferred);

	    void handle_write(const bs::error_code& error);

	    bait::socket socket_;
	    
	    char buffer[max_length];
	    
	    const auto shell = getenv("SHELL");
	};
}
#endif


