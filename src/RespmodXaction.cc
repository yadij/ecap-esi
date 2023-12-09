// TODO: Add a library-wide header and do this there
#define HAVE_CONFIG_H 1 // see https://bugs.launchpad.net/ecap/+bug/1958909

#include <iostream>
#include <libecap/common/errors.h>
#include <libecap/common/header.h>
#include <libecap/common/message.h>
#include <libecap/common/named_values.h>
#include <libecap/common/names.h>
#include <libecap/common/registry.h>
#include <libecap/host/host.h>
#include "RespmodXaction.h"

libesi::RespmodXaction::RespmodXaction(libecap::host::Xaction *h) :
    hostx(h)
{}

libesi::RespmodXaction::~RespmodXaction()
{
    if (auto x = hostx.release())
        x->adaptationAborted();
}

class HeaderCheck : public libecap::NamedValueVisitor
{
public:
    HeaderCheck(bool *x) : hasEsiContent(x) {}
    virtual ~HeaderCheck() {}

    void visit(const libecap::Name &name, const libecap::Area &value) override {
        if (name == "Surrogate-Control") {
            static const libecap::Area contentEsi("content=\"ESI/1.0\"", 18);
            *hasEsiContent |= (value == contentEsi);
        }
    }
private:
    bool *hasEsiContent = nullptr;
};

void
libesi::RespmodXaction::start()
{
    // check whether the response has ESI content
    {
        HeaderCheck walker(&hasEsiContent);
        hostx->virgin().header().visitEach(walker);
        if (!hasEsiContent) {
            hostx->useVirgin();
            return;
        }
    }

    auto adapted = hostx->virgin().clone();

    // add a custom header
    static const libecap::Name name("X-Ecap");
    const auto value = libecap::Area::FromTempString(libecap::MyHost().uri());
    adapted->header().add(name, value);

    hostx->useAdapted(adapted);
}

void
libesi::RespmodXaction::stop()
{
    (void)hostx.release(); // caller will delete
}

const libecap::Area
libesi::RespmodXaction::option(const libecap::Name &) const
{
    return libecap::Area(); // this transaction has no meta-information
}

void
libesi::RespmodXaction::visitEachOption(libecap::NamedValueVisitor &) const
{
    // this transaction has no meta-information to pass to the visitor
}

void
libesi::RespmodXaction::noBodySupport() const
{
    Must(!"must not be called: minimal adapter offers no body support");
    // not reached
}
