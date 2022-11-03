##### client ##################################################################

add_executable(x-ray-client
	src/Client.cpp
)
target_compile_features(x-ray-client PRIVATE cxx_std_17)

target_link_libraries(x-ray-client PRIVATE jsonrpc)
target_link_libraries(x-ray-client PRIVATE Boost::Boost)

##### server ##################################################################

add_executable(x-ray-server
	src/Server.cpp
	# src/XRayTube.cpp
)
target_compile_features(x-ray-server PRIVATE cxx_std_17)

target_link_libraries(x-ray-server PRIVATE jsonrpc)
target_link_libraries(x-ray-server PRIVATE Boost::Boost)
