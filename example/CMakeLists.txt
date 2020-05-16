##### client ##################################################################

add_executable(client
	src/Client.cpp
)
target_compile_features(client PRIVATE cxx_std_17)

target_link_libraries(client PRIVATE jsonrpc)
target_link_libraries(client PRIVATE Boost::Boost)

##### server ##################################################################

add_executable(server
	src/Server.cpp
)
target_compile_features(server PRIVATE cxx_std_17)

target_link_libraries(server PRIVATE jsonrpc)
target_link_libraries(server PRIVATE Boost::Boost)
