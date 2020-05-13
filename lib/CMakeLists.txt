##### lib target ##############################################################

add_library(jsonrpc
	src/ClientTransport.cpp
	src/TcpSession.cpp
	src/ServerTransport.cpp
)

target_compile_features(jsonrpc PUBLIC cxx_std_17)

##### target link libraries ###################################################

target_link_libraries(jsonrpc PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(jsonrpc PUBLIC Boost::Boost)

##### generate and include config header ######################################

configure_file(include/jsonrpc/Config.h.in include/jsonrpc/Config.h @ONLY)
target_include_directories(jsonrpc BEFORE PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)

##### target includes #########################################################

target_include_directories(jsonrpc PUBLIC include)
