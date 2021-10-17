#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "session.hpp"

#include <stdint.h>
#include <boost/asio.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
namespace bait =  boost::asio::ip::tcp;

namespace hse::Telnet 
{
	class Server
	{
	private:
	    ba::io_service& ios;
	    tcp::acceptor acpt;
	public:
	/***
	* Конструктор класса сервера, принимает на вход два параметра:
	* io_service - ссылку ASIO на службу ввода-вывода ОС;
	* port - номер порта, который будет слушать создаваемый сервер.
	* конструктор инициализирует соотвествующие private члены переданными параметрами
	* и вызывает функцию приема соединений.
	***/
	    Server(ba::io_service& io_service, const uint16_t port);

	private:
	/***
	* Данный метод создает новый экземпляр telnet сессии и переводит акцептор в режим ожидания
	* подключения к сокету в асинхронном режиме, не дожидаясь окончания его работы.
	***/
	    void start_accept();
	/***
	* Данный метод вызывается в случае нового соединения с портом,
	* если подключение произошло без ошибок, метод стартует сессию (вызывает на ней соответствующий метод),
	* в противном случае выводит ошибку в стандартный вывод ошибок и удаляет сессию.
	* После этого сервер переводится в состояние ожидания нового подключения.
	***/
	    void handle_accept(Session* new_session, const bs::error_code& error);
	};
}
#endif

