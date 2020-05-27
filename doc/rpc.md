## source paths

- lib/include/jsonrpc/rpc/Client.h
- lib/include/jsonrpc/rpc/Dispatcher.h
- lib/include/jsonrpc/rpc/Error.h
- lib/include/jsonrpc/rpc/IMethod.h
- lib/include/jsonrpc/rpc/Json.h
- lib/include/jsonrpc/rpc/Registry.h
- lib/include/jsonrpc/rpc/Request.h
- lib/include/jsonrpc/rpc/Response.h

## class diagram

```puml
set namespaceSeparator ::
class jsonrpc::rpc::Client {
  - net::ITransport & _transport
  - int _id
  + Client (net::ITransport & transport) -> void
  + call (const std::string name, const jsonrpc::rpc::Json & args) -> jsonrpc::rpc::Json
  + notify (const std::string name, const jsonrpc::rpc::Json & args) -> void
  - call (const jsonrpc::rpc::Request & req) -> jsonrpc::rpc::Response
}
jsonrpc::rpc::Client o--> net::ITransport

class jsonrpc::rpc::Dispatcher {
  - jsonrpc::rpc::Registry _registry
  + dispatch (const std::string & sreq) -> std::string
  - dispatch (const jsonrpc::rpc::Request & req) -> jsonrpc::rpc::Response
  + Dispatcher (const jsonrpc::rpc::Dispatcher & ) -> void
  + Dispatcher (jsonrpc::rpc::Dispatcher && ) -> void
  + operator= (const jsonrpc::rpc::Dispatcher & ) -> jsonrpc::rpc::Dispatcher &
  + operator= (jsonrpc::rpc::Dispatcher && ) -> jsonrpc::rpc::Dispatcher &
  + ~Dispatcher () -> void
}
net::IDispatcher <|-- jsonrpc::rpc::Dispatcher
jsonrpc::rpc::Dispatcher *--> jsonrpc::rpc::Registry
jsonrpc::rpc::Dispatcher -.-> jsonrpc::rpc::Request : <<usage>>
jsonrpc::rpc::Dispatcher -.-> jsonrpc::rpc::Response : <<usage>>

class jsonrpc::rpc::Error {
  + jsonrpc::rpc::ErrorCode code
  + std::string message
  + std::optional<Json> data
  + Error (const jsonrpc::rpc::Error & ) -> void
  + Error (jsonrpc::rpc::Error && ) -> void
  + operator= (jsonrpc::rpc::Error && ) -> jsonrpc::rpc::Error &
  + ~Error () -> void
  + Error () -> void
}
jsonrpc::rpc::Error -.-> jsonrpc::rpc::Json : <<usage>>

class jsonrpc::rpc::IMethod {
  + ~IMethod () -> void
  + call (const jsonrpc::rpc::Json & args) -> jsonrpc::rpc::Json
  + operator= (const jsonrpc::rpc::IMethod & ) -> jsonrpc::rpc::IMethod &
}

class jsonrpc::rpc::Request {
  + std::string jsonrpc
  + std::string method
  + jsonrpc::rpc::Json params
  + jsonrpc::rpc::Json id
  + isNotification () -> bool
  + Request (const jsonrpc::rpc::Request & ) -> void
  + Request (jsonrpc::rpc::Request && ) -> void
  + operator= (jsonrpc::rpc::Request && ) -> jsonrpc::rpc::Request &
  + ~Request () -> void
}
jsonrpc::rpc::Request -.-> jsonrpc::rpc::Json : <<usage>>

class jsonrpc::rpc::Response {
  + std::string jsonrpc
  + std::optional<Json> result
  + std::optional<Error> error
  + jsonrpc::rpc::Json id
  + Response (const jsonrpc::rpc::Response & ) -> void
  + Response (jsonrpc::rpc::Response && ) -> void
  + operator= (jsonrpc::rpc::Response && ) -> jsonrpc::rpc::Response &
  + ~Response () -> void
  + Response () -> void
}
jsonrpc::rpc::Response -.-> jsonrpc::rpc::Json : <<usage>>
jsonrpc::rpc::Response *--> jsonrpc::rpc::Error

```

