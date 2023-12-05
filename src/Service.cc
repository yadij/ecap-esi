
#define HAVE_CONFIG_H 1 // see https://bugs.launchpad.net/ecap/+bug/1958909
#include <libecap/common/registry.h>
#include <iostream>

#include "Service.h"
#include "Xaction.h"

// create the adapter and register with libecap to reach the host application
static const bool Registered =
    libecap::RegisterVersionedService(new libesi::Service);

std::string
libesi::Service::uri() const
{
    return "ecap://" PROJECT_NAME "/" PROJECT_VER "/respmod";
}

std::string
libesi::Service::tag() const
{
    return PROJECT_VER;
}

void
libesi::Service::describe(std::ostream &os) const
{
    os << "ESI translator " << PROJECT_NAME << " v" << PROJECT_VER;
}

libecap::adapter::Service::MadeXactionPointer
libesi::Service::makeXaction(libecap::host::Xaction *hostx)
{
    std::cerr << "libesi::Service::makeXaction called" << std::endl;
    return libecap::adapter::Service::MadeXactionPointer(new libesi::Xaction(hostx));
}
