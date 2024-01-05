#include <array>
#include <future>
#include <iostream>
#include <thread>
#include <lwip/tcpip.h>

#include "lwip_linux_unix_tap_network_interface.h"


int main()
{
    // initialize lwip
    // use lcpip_init instead of lwip_init because we are not using lwip's NO_SYS mode
    tcpip_init(nullptr, nullptr);

    // host = your computer
    // application = this application

    // ip address of this application using a TAP interface
    // use this ip address to talk to this application from the host
    // (e.g. ping this address to check if lwip is alive)
    static constexpr std::array<uint8_t, 4> ip_address_data = {192, 168, 115, 2};

    // gateway address of the TAP interface, which is created by calling init_default_netif()
    static constexpr std::array<uint8_t, 4> default_gateway_data = {192, 168, 115, 1};

    // netmask of the TAP interface, which is created by calling init_default_netif()
    static constexpr std::array<uint8_t, 4> netmask_data = {255, 255, 255, 0};


    ip4_addr_t ipaddr;
    ip4_addr_set_u32(
        &ipaddr,
        ip_address_data[0] << 0u | ip_address_data[1] << 8u | ip_address_data[2] << 16u | ip_address_data[3] << 24u);

    ip4_addr_t gw;
    ip4_addr_set_u32(
        &gw, default_gateway_data[0] << 0u | default_gateway_data[1] << 8u | default_gateway_data[2] << 16u |
        default_gateway_data[3] << 24u);

    ip4_addr_t netmask;
    ip4_addr_set_u32(
        &netmask, netmask_data[0] << 0u | netmask_data[1] << 8u | netmask_data[2] << 16u | netmask_data[3] << 24u);


    {
        struct LwipCoreLockRaii
        {
            LwipCoreLockRaii()
            {
                LOCK_TCPIP_CORE();
            }

            ~LwipCoreLockRaii()
            {
                UNLOCK_TCPIP_CORE();
            }

            LwipCoreLockRaii(const LwipCoreLockRaii&) = delete;
            LwipCoreLockRaii& operator=(const LwipCoreLockRaii&) = delete;
            LwipCoreLockRaii(LwipCoreLockRaii&&) = delete;
            LwipCoreLockRaii& operator=(LwipCoreLockRaii&&) = delete;
        };

        // lock the lwip core until the end of this scope ( } ) (RAII)
        LwipCoreLockRaii lockLwipCore{};

        // create the TAP interface on the unix host
        init_default_netif(&ipaddr, &netmask, &gw);

        // start operation on this network interface
        netif_set_up(&get_default_netif());

        // end of scope: unlock the lwip core (RAII)
    }


    while (true)
    {
        // let this thread of execution wait forever (from https://stackoverflow.com/a/42644441 )
        // the "lwip thread" will continue working in the background
        std::promise<void>().get_future().wait();
    }

    return 0;
}
