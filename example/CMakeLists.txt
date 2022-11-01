##### client ##################################################################

add_executable(client
	src/Client.cpp
)
target_compile_features(client PRIVATE cxx_std_17)

target_link_libraries(client PRIVATE jsonrpc)
target_link_libraries(client PRIVATE Boost::boost pthread)

##### sample client/server ##################################################################

add_executable(sample_client
	src/SampleClient.cpp
)
target_compile_features(sample_client PRIVATE cxx_std_17)

target_link_libraries(sample_client PRIVATE jsonrpc)
target_link_libraries(sample_client PRIVATE Boost::Boost)

add_executable(sample_server
	src/SampleServer.cpp
)
target_compile_features(sample_server PRIVATE cxx_std_17)

target_link_libraries(sample_server PRIVATE jsonrpc)
target_link_libraries(sample_server PRIVATE Boost::Boost)

##### chat server #############################################################

add_executable(mbox
	src/MessageBoxServer.cpp
)
target_compile_features(mbox PRIVATE cxx_std_17)

target_link_libraries(mbox PRIVATE Boost::Boost)
target_link_libraries(mbox PRIVATE fmt::fmt)
target_link_libraries(mbox PRIVATE jsonrpc)

##### sample mbox client session ##############################################

add_executable(mbox_session
	src/MessageBoxClientSession.cpp
)
target_compile_features(mbox_session PRIVATE cxx_std_17)

target_link_libraries(mbox_session PRIVATE Boost::Boost)
target_link_libraries(mbox_session PRIVATE fmt::fmt)
target_link_libraries(mbox_session PRIVATE jsonrpc)
