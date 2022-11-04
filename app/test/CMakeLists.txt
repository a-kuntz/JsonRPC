add_executable(xraytest
	src/main.cpp
	src/XRayServerTest.cpp
)

target_compile_features(xraytest PRIVATE cxx_std_17)

target_link_libraries(xraytest jsonrpc)
target_link_libraries(xraytest GTest::GTest)

add_test(NAME xraytest COMMAND xraytest)

