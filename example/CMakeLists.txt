add_executable(generic_server
	src/generic_server.cpp
)
target_compile_features(generic_server PRIVATE cxx_std_17)

# target_link_libraries(generic_server PRIVATE jsonrpc)
target_link_libraries(generic_server PRIVATE Boost::Boost)

##### async client ############################################################

add_executable(async_client
	src/AsyncClient.cpp
)
target_compile_features(async_client PRIVATE cxx_std_17)

target_link_libraries(async_client PRIVATE jsonrpc)
target_link_libraries(async_client PRIVATE Boost::Boost)

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
