add_executable(testrpc
	src/main.cpp
	src/DispatcherTest.cpp
	src/RequestTest.cpp
	src/ResponseTest.cpp
)

target_compile_features(testrpc PRIVATE cxx_std_17)

target_link_libraries(testrpc jsonrpc)
target_link_libraries(testrpc GTest::GTest)

add_test(NAME testrpc COMMAND testrpc)
