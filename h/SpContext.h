#ifndef SP_CONTEXT_H_
#define SP_CONTEXT_H_

#include "SpCommon.h"
#include "SpPayload.h"
#include "SpPropeller.h"
#include "SpParser.h"
#include "PatchMgr.h"
#include "SpEvent.h"
#include "SpSnippet.h"

namespace sp {

class SpContext {
  public:
  static SpContextPtr create(SpPropeller::ptr,
                             string,
                             SpParser::ptr);


    PayloadFunc init_payload() { return init_payload_; }
    SpPropeller::ptr init_propeller() { return init_propeller_; }
    bool propel(int, PayloadFunc);

    void parse();
    void restore();

    SpParser::ptr parser() { return parser_; }
    Dyninst::PatchAPI::PatchFunction* get_first_inst_func();
    Dyninst::PatchAPI::PatchMgrPtr mgr() { return mgr_; }
    void set_old_act(struct sigaction old_act) { old_act_ = old_act; }

    // EIP -> snippet
    typedef std::map<Dyninst::Address, Dyninst::PatchAPI::InstancePtr> InstMap;
    InstMap& inst_map() { return inst_map_; }
    bool is_well_known_lib(string);

    Dyninst::Address setcontext_func() const { return setcontext_func_; }
    Dyninst::Address getcontext_func() const { return getcontext_func_; }

  protected:
    SpPropeller::ptr init_propeller_;
    PayloadFunc init_payload_;
    SpParser::ptr parser_;
    Dyninst::PatchAPI::PatchMgrPtr mgr_;
    std::vector<string> well_known_libs_;

    // Things to be restored
    struct sigaction old_act_;
    InstMap inst_map_;

    Dyninst::Address setcontext_func_;
    Dyninst::Address getcontext_func_;

    SpContext(SpPropeller::ptr,
              SpParser::ptr);
    void init_well_known_libs();
    //bool is_instrumentable_func(Dyninst::PatchAPI::PatchFunction* func);
};


}

#endif /* SP_CONTEXT_H_ */
