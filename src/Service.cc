
#define HAVE_CONFIG_H 1 // see https://bugs.launchpad.net/ecap/+bug/1958909

#include <iostream>
#include <libecap/adapter/service.h>
#include <libecap/common/registry.h>
#include <libecap/host/xaction.h>

#include "config.h"
#include "ReqmodXaction.h"
#include "RespmodXaction.h"

namespace libesi
{

// Add HTTP Request header Surrogate-Capability: "ESI/1.0"
class ReqmodService : public libecap::adapter::Service
{
public:
    virtual ~ReqmodService() {}

    /* libecap::adaptor::Service API */
    std::string uri() const override { return "ecap://" PROJECT_NAME "/" PROJECT_VER "/surrogate"; }
    std::string tag() const override { return PROJECT_NAME "/" PROJECT_VER "/surrogate"; }
    void describe(std::ostream &os) const override {
        os << "ESI Request translator " << PROJECT_NAME << " v" << PROJECT_VER;
    }
    void configure(const libecap::Options &) override {}
    void reconfigure(const libecap::Options &) override {}
    bool wantsUrl(const char *) const override { return true; }
    libecap::adapter::Service::MadeXactionPointer makeXaction(libecap::host::Xaction *hostx) override {
        return libecap::adapter::Service::MadeXactionPointer(new libesi::ReqmodXaction(hostx));
    }

};

// Adapt ESI Response content
class RespmodService : public libecap::adapter::Service
{
public:
    virtual ~RespmodService() {}

    /* libecap::adaptor::Service API */
    std::string uri() const override { return "ecap://" PROJECT_NAME "/" PROJECT_VER "/esi"; }
    std::string tag() const override { return PROJECT_NAME "/" PROJECT_VER "/esi"; }
    void describe(std::ostream &os) const override {
        os << "ESI Response translator " << PROJECT_NAME << " v" << PROJECT_VER;
    }
    void configure(const libecap::Options &) override {}
    void reconfigure(const libecap::Options &) override {}
    bool wantsUrl(const char *) const override { return true; }
    libecap::adapter::Service::MadeXactionPointer makeXaction(libecap::host::Xaction *hostx) override {
        return libecap::adapter::Service::MadeXactionPointer(new libesi::RespmodXaction(hostx));
    }
};

} // namespace libesi

static bool
RegisterServices()
{
    return libecap::RegisterVersionedService(new libesi::ReqmodService) &&
           libecap::RegisterVersionedService(new libesi::RespmodService);
}

// create the adapter and register with libecap to reach the host application
static const auto Registered = RegisterServices();
