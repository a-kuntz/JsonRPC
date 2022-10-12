cmake_minimum_required(VERSION 3.12)

project(JsonRPC)

##### dependencies ############################################################

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem program_options)

find_package(GTest REQUIRED)

##### configuration ###########################################################

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
# message(STATUS CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS})

##### targets #################################################################

add_subdirectory(lib)
add_subdirectory(example)

enable_testing()
add_subdirectory(test)
