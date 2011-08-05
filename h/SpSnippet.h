#ifndef _SPSNIPPET_H_
#define _SPSNIPPET_H_

#include "SpCommon.h"
#include "SpPayload.h"

namespace sp {

class SpSnippet {
  public:
    typedef dyn_detail::boost::shared_ptr<SpSnippet> ptr;
    static ptr create(Dyninst::PatchAPI::PatchFunction* f,
                      SpContextPtr c,
                      PayloadFunc p) {
      return ptr(new SpSnippet(f, c, p));
    }

    SpSnippet(Dyninst::PatchAPI::PatchFunction* f,
              SpContextPtr c,
              PayloadFunc p) : func_(f), context_(c), payload_(p) {
    }

    char* blob();
    SpContextPtr context() { return context_; }
  protected:
    Dyninst::PatchAPI::PatchFunction* func_;
    SpContextPtr context_;
    PayloadFunc payload_;
};

}

#endif /* _SPSNIPPET_H_ */
