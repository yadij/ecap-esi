// TODO: Add a library-wide header and do this there
#define HAVE_CONFIG_H 1 // see https://bugs.launchpad.net/ecap/+bug/1958909

#include <iostream>
#include <libecap/common/errors.h>
#include <libecap/common/header.h>
#include <libecap/common/message.h>
#include <libecap/common/names.h>
#include <libecap/common/registry.h>
#include <libecap/host/host.h>

#include "ReqmodXaction.h"

libesi::ReqmodXaction::ReqmodXaction(libecap::host::Xaction *h) :
    hostx(h)
{}

libesi::ReqmodXaction::~ReqmodXaction()
{
    if (auto x = hostx.release())
        x->adaptationAborted();
}

void
libesi::ReqmodXaction::start()
{
    static const libecap::Name name("Surrogate-Capability");
    static const libecap::Area value("\"ESI/1.0\"", 10);

    auto adapted = hostx->virgin().clone();
    adapted->header().add(name, value);
    hostx->useAdapted(adapted);
}

void
libesi::ReqmodXaction::stop()
{
    (void)hostx.release(); // caller will delete
}

const libecap::Area
libesi::ReqmodXaction::option(const libecap::Name &) const
{
    return libecap::Area(); // this transaction has no meta-information
}

void
libesi::ReqmodXaction::visitEachOption(libecap::NamedValueVisitor &) const
{
    // this transaction has no meta-information to pass to the visitor
}

void
libesi::ReqmodXaction::noBodySupport() const
{
    Must(!"must not be called: REQMOD offers no body support");
    // not reached
}
