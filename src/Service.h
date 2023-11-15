
#include <libecap/adapter/service.h>
#include <libecap/host/xaction.h>

#include "config.h"

namespace libesi
{

class Service : public libecap::adapter::Service
{
public:
    virtual ~Service() {}

    /* libecap::adaptor::Service API */
    std::string uri() const override;
    std::string tag() const override;
    void describe(std::ostream &) const override;
    void configure(const libecap::Options &) override {}
    void reconfigure(const libecap::Options &) override {}
    bool wantsUrl(const char *) const override { return true; }
    libecap::adapter::Service::MadeXactionPointer makeXaction(libecap::host::Xaction *) override;
};

} // namespace libesi
