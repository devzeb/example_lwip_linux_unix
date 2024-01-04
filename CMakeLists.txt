cmake_minimum_required(VERSION 3.22)
project(example_lwip_linux_unix C CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/lwip/)

# create the "ported" version of the lwip library, suited for our needs (running on linux / unix)
add_library(lwip_port)
add_library(example_lwip_linux_unix::lwip_port ALIAS lwip_port) # alias target so cmake complains when we link to it and it does not exist
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