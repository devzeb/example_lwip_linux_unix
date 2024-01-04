add_executable(example_lwip_linux_unix
        main.cpp
        lwip_linux_unix_tap_network_interface.cpp
        lwip_linux_unix_tap_network_interface.h
)

target_link_libraries(example_lwip_linux_unix PRIVATE
        example_lwip_linux_unix::lwip_port
)