#ifndef __SESSION_HPP__
#define __SESSION_HPP__

#include <boost/asio.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
namespace bai = boost::asio::ip;

namespace hse::Telnet 
{
	class Session
	{
	public:
	    Session(ba::io_service& io_service);

	    bai::tcp::socket& socket() { return socket_; }

	    void start();

	    enum { max_length = 3 };

	private:
	    void handle_read(const bs::error_code& error, size_t bytes_transferred);

	    void handle_write(const bs::error_code& error);

	    bai::tcp::socket socket_;
	    
	    char buffer[max_length];
	    
	    const char* shell = getenv("SHELL");
	};
}
#endif


