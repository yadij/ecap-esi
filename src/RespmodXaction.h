
#ifndef _SRC_RESPMODXACTION_H_
#define _SRC_RESPMODXACTION_H_

#include <libecap/adapter/xaction.h>
#include <libecap/host/xaction.h>

namespace libesi
{

/*
 * Translate ESI response payload in HTTP Response
 *
 * See ESI Language Specification 1.0
 * https://www.w3.org/TR/esi-lang/
 */
class RespmodXaction: public libecap::adapter::Xaction
{
public:
    RespmodXaction(libecap::host::Xaction *);
    virtual ~RespmodXaction();

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
    bool hasEsiContent = false;
};

} // namespace libesi

#endif // _SRC_RESPMODXACTION_H_
