##### client ##################################################################

add_executable(client
	src/Client.cpp
)
target_compile_features(client PRIVATE cxx_std_17)

target_link_libraries(client PRIVATE jsonrpc)
target_link_libraries(client PRIVATE Boost::Boost)
