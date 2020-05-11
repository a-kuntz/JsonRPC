cmake_minimum_required(VERSION 3.12)

project(JsonRPC)

##### dependencies ############################################################

find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)

##### configuration ###########################################################

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
# message(STATUS CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS})

##### targets #################################################################

add_subdirectory(lib)

enable_testing()
add_subdirectory(test)
