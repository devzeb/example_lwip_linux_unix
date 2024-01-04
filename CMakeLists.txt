cmake_minimum_required(VERSION 3.22)
project(untitled10 C CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/lwip/)

add_library(lwip_port)
target_link_libraries(lwip_port PRIVATE
        devzeb::lwip_core
        devzeb::lwip_unix_core
)
target_link_libraries(lwip_port PUBLIC
        devzeb::lwip_api
        devzeb::lwip_unix_core_api
)
target_include_directories(lwip_port PUBLIC port_configuration/lwip/)


add_subdirectory(example_lwip_linux_unix)