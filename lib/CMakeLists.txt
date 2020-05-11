##### lib target ##############################################################

add_library(jsonrpc
	INTERFACE
)

target_compile_features(jsonrpc INTERFACE cxx_std_17)

##### target link libraries ###################################################

target_link_libraries(jsonrpc INTERFACE nlohmann_json::nlohmann_json)

##### generate and include config header ######################################

configure_file(include/jsonrpc/Config.h.in include/jsonrpc/Config.h @ONLY)
target_include_directories(jsonrpc BEFORE INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/include)

##### target includes #########################################################

target_include_directories(jsonrpc INTERFACE include)
