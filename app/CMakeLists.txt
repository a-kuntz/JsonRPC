##### libxray #################################################################

add_library(xray
	src/XRayServer.cpp
)
target_link_libraries(xray PRIVATE jsonrpc)

##### client ##################################################################

add_executable(xrayclient
	src/Client.cpp
)
target_compile_features(xrayclient PRIVATE cxx_std_17)

target_link_libraries(xrayclient PRIVATE jsonrpc)
target_link_libraries(xrayclient PRIVATE Boost::Boost)

##### server ##################################################################

add_executable(xrayserver
	src/Server.cpp
)
target_compile_features(xrayserver PRIVATE cxx_std_17)

target_link_libraries(xrayserver PRIVATE xray)
target_link_libraries(xrayserver PRIVATE jsonrpc)
target_link_libraries(xrayserver PRIVATE Boost::Boost)

##### test ##################################################################

add_executable(xraytest
	src/testmain.cpp
	src/XRayServerTest.cpp
)

target_compile_features(xraytest PRIVATE cxx_std_17)

target_link_libraries(xraytest jsonrpc)
target_link_libraries(xraytest GTest::GTest)

add_test(NAME xraytest COMMAND xraytest)
