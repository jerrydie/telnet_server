# telnet_server
Сборка и запуск: `mkdir build && cd build && cmake .. && make && ./hse-telnet 34877`

Со стороны клиента: `socat tcp-connect:127.0.0.2:34877 stdin`

Вводим имя скрипта: `small-test.sh`

Вывод со стороны сервера:
```
Server::start_accept
New session created by the server
Before io_service.run()
Server::handle_accept starting session
Telnet session started
Server::start_accept
New session created by the server
Session::handle_read 3 bytes
Session::handle_read 3 bytes
Session::handle_read 3 bytes
Session::handle_read 3 bytes
Session::handle_read 2 bytes
Session::handle_write
```

Вывод со стороны клиента:
```
/home/polina/Prog/telnet_server
polina
```
