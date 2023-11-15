
cmake_minimum_required(VERSION 3.22.1)
project(ecap-esi VERSION 0.0.1
                 DESCRIPTION "eCAP module providing Edge Side Includes (ESI)"
                 LANGUAGES CXX)

## Environment setup
include(GNUInstallDirs)
include_directories(${CMAKE_INSTALL_OLDINCLUDEDIR})
configure_file("src/config.h.in" "src/config.h")

## Shared library module
add_library(ecap-esi MODULE
    src/Service.cc
    src/Xaction.cc
)
set_target_properties(ecap-esi PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_link_libraries(ecap-esi PRIVATE ecap)
install(TARGETS ecap-esi
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

## Squid configuration defaults
configure_file("src/ecap-esi.conf.in" "ecap-esi.conf")
install(FILES ecap-esi.conf
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/squid/conf.d/
)
