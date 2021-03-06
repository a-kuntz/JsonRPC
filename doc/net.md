## source paths

- lib/include/jsonrpc/net/ClientTransport.h
- lib/include/jsonrpc/net/IDispatcher.h
- lib/include/jsonrpc/net/ITransport.h
- lib/include/jsonrpc/net/ServerTransport.h
- lib/include/jsonrpc/net/ServerTransportSession.h

## class diagram

```puml
set namespaceSeparator ::
class jsonrpc::net::ClientTransport {
  - boost::asio::io_context & _ioc
  - boost::asio::ip::tcp::socket _socket
  + ClientTransport (boost::asio::io_context & ioc) -> void
  + connect (const std::string & host, int port) -> void
  + send (const std::string & data) -> void
  + receive () -> std::string
  + ClientTransport (const jsonrpc::net::ClientTransport & ) -> void
  + ClientTransport (jsonrpc::net::ClientTransport && ) -> void
  + operator= (const jsonrpc::net::ClientTransport & ) -> jsonrpc::net::ClientTransport &
  + operator= (jsonrpc::net::ClientTransport && ) -> jsonrpc::net::ClientTransport &
  + ~ClientTransport () -> void
}
jsonrpc::net::ITransport <|-- jsonrpc::net::ClientTransport
jsonrpc::net::ClientTransport o--> boost::asio::io_context
jsonrpc::net::ClientTransport *--> boost::asio::ip::tcp::socket

class jsonrpc::net::IDispatcher {
  + dispatch (const std::string & data) -> std::string
  + ~IDispatcher () -> void
  + operator= (const jsonrpc::net::IDispatcher & ) -> jsonrpc::net::IDispatcher &
}

class jsonrpc::net::ITransport {
  + send (const std::string & data) -> void
  + receive () -> std::string
  + ~ITransport () -> void
  + operator= (const jsonrpc::net::ITransport & ) -> jsonrpc::net::ITransport &
}

class jsonrpc::net::ServerTransport {
  - boost::asio::ip::tcp::acceptor _acceptor
  - net::IDispatcher & _dispatcher
  + ServerTransport (boost::asio::io_context & io_context, unsigned short port, net::IDispatcher & dispatcher) -> void
  - do_accept () -> void
  + ServerTransport (const jsonrpc::net::ServerTransport & ) -> void
  + ServerTransport (jsonrpc::net::ServerTransport && ) -> void
  + operator= (jsonrpc::net::ServerTransport && ) -> jsonrpc::net::ServerTransport &
  + ~ServerTransport () -> void
}
jsonrpc::net::ServerTransport *--> boost::asio::ip::tcp::acceptor
jsonrpc::net::ServerTransport o--> jsonrpc::net::IDispatcher
jsonrpc::net::ServerTransport -.-> jsonrpc::net::ServerTransportSession : <<usage>>

class jsonrpc::net::ServerTransportSession {
  - boost::asio::ip::tcp::socket _socket
  - std::string _data
  - net::IDispatcher & _dispatcher
  + ServerTransportSession (boost::asio::ip::tcp::socket socket, net::IDispatcher & dispatcher) -> void
  + start () -> void
  - do_read () -> void
  - do_write () -> void
  + ServerTransportSession (const jsonrpc::net::ServerTransportSession & ) -> void
  + ServerTransportSession (jsonrpc::net::ServerTransportSession && ) -> void
  + operator= (const jsonrpc::net::ServerTransportSession & ) -> jsonrpc::net::ServerTransportSession &
  + operator= (jsonrpc::net::ServerTransportSession && ) -> jsonrpc::net::ServerTransportSession &
  + ~ServerTransportSession () -> void
}
jsonrpc::net::ServerTransportSession *--> boost::asio::ip::tcp::socket
jsonrpc::net::ServerTransportSession o--> jsonrpc::net::IDispatcher

```

