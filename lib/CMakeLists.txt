##### lib target ##############################################################

add_library(jsonrpc
	src/net/ClientTransport.cpp
	src/net/ServerTransportSession.cpp
	src/net/ServerTransport.cpp
	src/rpc/Client.cpp
	src/rpc/Dispatcher.cpp
)

target_compile_features(jsonrpc PUBLIC cxx_std_17)

set_target_properties(jsonrpc PROPERTIES OUTPUT_NAME jsonrpc$<$<CONFIG:Debug>:d>)

##### target link libraries ###################################################

target_link_libraries(jsonrpc PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(jsonrpc PUBLIC Boost::boost pthread)

##### generate and include config header ######################################

configure_file(include/jsonrpc/Config.h.in include/jsonrpc/Config.h @ONLY)
target_include_directories(jsonrpc BEFORE PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)

##### target includes #########################################################

target_include_directories(jsonrpc PUBLIC include)


# ToDo: add commands to install the library and the package config file
