#ifndef __SESSION_HPP__
#define __SESSION_HPP__

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <boost/process.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
namespace bp = boost::process;
namespace bai = boost::asio::ip;

namespace hse::Telnet 
{
	class Session
	{
	private:
// Сокет сессии.
	    bai::tcp::socket socket_;
// Большой буфер сессии (для записи результата команды).
	    std::vector<char> result_buffer;
// Среда сессии.	    
	    char* shell;
// Буфер имени файла SHELL.
	    std::vector<char> shell_file_buffer;	
// Асинхронный пайп, в который записывается результат выполнения команды, переданной на вход сессии.
	    bp::async_pipe ap;
	public:
/***
* Конструктор класса сессии подключения к серверу, принимает на вход один параметр - 
* io_service - ссылку ASIO на службу ввода-вывода ОС.
* Инициализирует private член класса данным параметром.
***/
	    Session(ba::io_service& io_service);
/***
* Данный метод предоставляет доступ к сокету сессии.
***/
	    bai::tcp::socket& socket() { return socket_; }
/***
* Данный метод начинает сессию подключения к серверу,
* вызывает асинхронное чтение в буфер заданного размера.
***/
	    void start();
// Максимальный размер буфера чтения/записи (enum используется для задния размера буфера).
	    enum { max_length = 3 };

	private:
// Малый буфер сессии.	    
	    char buffer[max_length];
/***
* Данный метод указывает, что происходит после чтения текущего подключения:
* Данные записываются в сокет из буфера сессии, в случае ошибки чтения ее значение
* записывается в стандартный вывод ошибок и сессия удаляется.
***/
	    void handle_read(const bs::error_code& error, size_t bytes_transferred);
/***
* Данный метод указывает, что происходит после записи текущего подключения:
* Данные считываются с сокета и записываются в буффер сессии заданного размера, в случае ошибки записи ее значение
* записывается в стандартный вывод ошибок и сессия удаляется.
***/
	    void handle_write(const bs::error_code& error);
	};
}
#endif


