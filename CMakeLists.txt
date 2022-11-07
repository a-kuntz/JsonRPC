cmake_minimum_required(VERSION 3.15)

project(JsonRPC)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type options" FORCE)
endif()

##### options #################################################################

OPTION(BUILD_APP "Build application" ON)
message(STATUS "BUILD_APP: ${BUILD_APP}" )

OPTION(BUILD_EXAMPLE "Build example" ON)
message(STATUS "BUILD_EXAMPLE: ${BUILD_EXAMPLE}" )

OPTION(BUILD_TESTS "Build tests" ON)
message(STATUS "BUILD_TESTS: ${BUILD_TESTS}" )

##### dependencies ############################################################

find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem program_options)
if(BUILD_TESTS)
    find_package(GTest REQUIRED COMPONENTS gtest)
endif()

##### configuration ###########################################################

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
# message(STATUS CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS})

##### subdirectories ##########################################################

add_subdirectory(lib)

if(BUILD_APP)
    add_subdirectory(app)
endif()

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
