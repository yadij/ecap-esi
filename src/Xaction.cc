// TODO: Add a library-wide header and do this there
#define HAVE_CONFIG_H 1 // see https://bugs.launchpad.net/ecap/+bug/1958909

#include <iostream>
#include <libecap/common/errors.h>
#include <libecap/common/header.h>
#include <libecap/common/message.h>
#include <libecap/common/names.h>
#include <libecap/common/registry.h>
#include <libecap/host/host.h>
#include "Xaction.h"

libesi::Xaction::Xaction(libecap::host::Xaction *h) :
    hostx(h)
{
    std::cerr << "libesi::Xaction construct this=" << (void*)this << " host=" << (void*)hostx.get() << std::endl;
}

libesi::Xaction::~Xaction()
{
    std::cerr << "libesi::Xaction destruct this=" << (void*)this << std::endl;
    if (auto x = hostx.release())
        x->adaptationAborted();
}

void
libesi::Xaction::start()
{
    std::cerr << "libesi::Xaction start this=" << (void*)this << std::endl;

    auto adapted = hostx->virgin().clone();

    // add a custom header
    static const libecap::Name name("X-Ecap");
    const auto value = libecap::Area::FromTempString(libecap::MyHost().uri());
    adapted->header().add(name, value);

    hostx->useAdapted(adapted);
}

void
libesi::Xaction::stop()
{
    std::cerr << "libesi::Xaction stop this=" << (void*)this << std::endl;
    (void)hostx.release(); // caller will delete
}

const libecap::Area libesi::Xaction::option(const libecap::Name &) const {
    return libecap::Area(); // this transaction has no meta-information
}

void libesi::Xaction::visitEachOption(libecap::NamedValueVisitor &) const {
    // this transaction has no meta-information to pass to the visitor
}

void libesi::Xaction::noBodySupport() const {
    Must(!"must not be called: minimal adapter offers no body support");
    // not reached
}
