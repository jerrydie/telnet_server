#include "server.hpp"

#include <iostream>
#include <boost/asio.hpp>
#include <charconv>

int main(int argc, char **argv)
{
    try
    {
        if (argc != 2)
          throw std::runtime_error("Correct format: ./filename <port>");
        
        boost::asio::io_service io_service;
        uint16_t port;
        
        std::from_chars<uint16_t>(argv[1],argv[2], port);
        if(port <= 0 || port > 65535){
            throw std::runtime_error("Port should be more then 1 and less then 65535");}
            
        hse::Telnet::Server ts(io_service, static_cast<uint16_t>(port));
        std::cout << "Before io_service.run()\n";
        io_service.run();
        std::cout << "After io_service.run()\n";
    }
    catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << '\n';
    }
    return 0;
}
