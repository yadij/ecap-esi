
#ifndef _SRC_REQMODXACTION_H_
#define _SRC_REQMODXACTION_H_

#include <libecap/adapter/xaction.h>
#include <libecap/host/xaction.h>

namespace libesi
{

/*
 * Add Surrogate-Capability header to HTTP Request
 * offering ESI/1.0 support to servers.
 *
 * See Edge Architecture specification
 * https://www.w3.org/TR/edge-arch/
 */
class ReqmodXaction: public libecap::adapter::Xaction
{
public:
    ReqmodXaction(libecap::host::Xaction *);
    virtual ~ReqmodXaction();

    /* libecap::adapter::Xaction API */
    virtual void start() override;
    virtual void stop() override;
    virtual const libecap::Area option(const libecap::Name &) const override;
    virtual void visitEachOption(libecap::NamedValueVisitor &) const override;
    virtual void abDiscard() override { noBodySupport(); }
    virtual void abMake() override { noBodySupport(); }
    virtual void abMakeMore() override { noBodySupport(); }
    virtual void abStopMaking() override { noBodySupport(); }
    virtual libecap::Area abContent(libecap::size_type, libecap::size_type) override { noBodySupport(); return libecap::Area(); }
    virtual void abContentShift(libecap::size_type)  override { noBodySupport(); }
    virtual void noteVbContentDone(bool) override { noBodySupport(); }
    virtual void noteVbContentAvailable() override { noBodySupport(); }

private:
    void noBodySupport() const;

    std::unique_ptr<libecap::host::Xaction> hostx;
};

} // namespace libesi

#endif // _SRC_REQMODXACTION_H_
