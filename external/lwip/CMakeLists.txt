# add a interface target because lwip_core is not ready to be compiled yet
# it needs a "lwipopts.h" file to be compiled properly
# therefore, a port can be added using by:
#
# add_library(lwip_port)
# target_link_libraries(lwip_port PRIVATE devzeb::lwip_core)
# target_link_libraries(lwip_port PUBLIC devzeb::lwip_api)
# target_include_directories(lwip_port PUBLIC <directory that includes lwipopts.h>)
# # optionally, add contrib sources and api to your port, like this:
# # target_link_libraries(lwip_port PRIVATE devzeb::lwip_unix_core)
# # target_link_libraries(lwip_port PUBLIC devzeb::lwip_unix_core_api)

set(LWIP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lwip/)
set(LWIP_CONTRIB_DIR ${LWIP_DIR}/contrib/)


# lwip core api
add_library(lwip_api INTERFACE)
add_library(devzeb::lwip_api ALIAS lwip_api)
target_include_directories(lwip_api INTERFACE ${LWIP_DIR}/src/include)


# lwip core source files
add_library(lwip_core INTERFACE)
add_library(devzeb::lwip_core ALIAS lwip_core)

include(lwip/src/Filelists.cmake)

target_sources(lwip_core INTERFACE ${lwipnoapps_SRCS})
target_link_libraries(lwip_core INTERFACE lwip_api) # all targets that use lwip source files must include the header files (lwip_api)


# lwip contrib unix core api
add_library(lwip_unix_core_api INTERFACE)
add_library(devzeb::lwip_unix_core_api ALIAS lwip_unix_core_api)
target_include_directories(lwip_unix_core_api INTERFACE lwip/contrib/ports/unix/port/include)


# lwip contrib unix core source files
add_library(lwip_unix_core INTERFACE)
add_library(devzeb::lwip_unix_core ALIAS lwip_unix_core)

target_link_libraries(lwip_unix_core INTERFACE lwip_unix_core_api)
include(lwip/contrib/ports/unix/Filelists.cmake)
target_sources(lwip_unix_core INTERFACE ${lwipcontribportunix_SRCS})
target_sources(lwip_unix_core INTERFACE ${lwipcontribportunixnetifs_SRCS})

get_target_property(LWIP_UNIX_CORE_LINK_LIBRARIES lwipcontribportunix LINK_LIBRARIES)
target_link_libraries(lwip_unix_core INTERFACE ${LWIP_UNIX_CORE_LINK_LIBRARIES})

