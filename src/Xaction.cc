
#include <iostream>
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
    if (auto x = hostx.release())
        x->useVirgin();
}

void
libesi::Xaction::stop()
{
    std::cerr << "libesi::Xaction stop this=" << (void*)this << std::endl;
    (void)hostx.release(); // caller will delete
}
