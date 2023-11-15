
#ifndef _SRC_XACTION_H_
#define _SRC_XACTION_H_

#include <libecap/adapter/xaction.h>
#include <libecap/host/xaction.h>

namespace libesi
{

class Xaction: public libecap::adapter::Xaction
{
public:
    Xaction(libecap::host::Xaction *);
    virtual ~Xaction();

    /* libecap::adapter::Xaction API */
    virtual void start() override;
    virtual void stop() override;
// adapted body transmission control
//    virtual void abDiscard() { noBodySupport(); }
//    virtual void abMake() { noBodySupport(); }
//    virtual void abMakeMore() { noBodySupport(); }
//    virtual void abStopMaking() { noBodySupport(); }
// adapted body content extraction and consumption
//    virtual libecap::Area abContent(libecap::size_type, libecap::size_type) { noBodySupport(); return libecap::Area(); }
//    virtual void abContentShift(libecap::size_type)  { noBodySupport(); }
// virgin body state notification
//    virtual void noteVbContentDone(bool) { noBodySupport(); }
//    virtual void noteVbContentAvailable() { noBodySupport(); }

private:
    std::unique_ptr<libecap::host::Xaction> hostx;
};

} // namespace libesi

#endif // _SRC_XACTION_H_
