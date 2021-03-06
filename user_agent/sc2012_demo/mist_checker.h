#ifndef _MISTCHECKER_H_
#define _MISTCHECKER_H_

#include "SpInc.h"
#include "mist_utils.h"

namespace mist {
//-----------------------------------------
// Base classes
//-----------------------------------------
class OneTimeChecker {
  public:
    virtual bool run() = 0;
    virtual ~OneTimeChecker() {}
  protected:
    MistUtils u_;
};

class MistChecker {
  public:
  virtual ~MistChecker() {}
  virtual bool check(sp::SpPoint* pt,
                     sp::SpFunction* callee) = 0;
  virtual bool post_check(sp::SpPoint* pt,
                          sp::SpFunction* callee) = 0;
  protected:
    MistUtils u_;
};

//-----------------------------------------
// Derived classes
//-----------------------------------------

// Check process stat
class ProcInitChecker : public OneTimeChecker {
  public:
    virtual bool run();
    ~ProcInitChecker() {}
  protected:
    // flag, privilege level
    // fork / exec, control flow, discuss w/ karl
    void PrintUserInfo();
    void PrintCurrentProc();
    void PrintParentProc();
    void PrintProc(pid_t pid);
    void PrintEnv();

    void InitTraces();
    MistUtils u_;
};


class ProcFiniChecker : public OneTimeChecker {
  public:
    virtual bool run() {
			return true;
    }
};

#if 0
// File opened
class FileOpenChecker : public MistChecker {
  public:
    virtual bool check(sp::SpPoint* pt,
                       sp::SpFunction* callee);
    virtual bool post_check(sp::SpPoint* pt,
                            sp::SpFunction* callee);
  protected:
    void print_file_info(char* fname);
    char* fname_;
};

// Dynamic loaded library
class LibChecker : public MistChecker {
  public:
    virtual bool check(sp::SpPoint* pt,
                       sp::SpFunction* callee);
    virtual bool post_check(sp::SpPoint* pt,
                            sp::SpFunction* callee) { return false;}
};





// Check mmap
class MmapChecker : public MistChecker {
  public:
    virtual bool check(sp::SpPoint* pt,
                       sp::SpFunction* callee);
    virtual bool post_check(sp::SpPoint* pt,
                            sp::SpFunction* callee);
};

// Check chmod
class ChmodChecker : public MistChecker {
  public:
    virtual bool check(sp::SpPoint* pt,
                       sp::SpFunction* callee);
    virtual bool post_check(sp::SpPoint* pt,
                            sp::SpFunction* callee) { return false; }
};

// Thread
class ThreadChecker : public MistChecker {
  public:
    virtual bool check(sp::SpPoint* pt,
                       sp::SpFunction* callee);
    virtual bool post_check(sp::SpPoint* pt,
                            sp::SpFunction* callee);
  protected:
    // A primitive form of concurrency control
    typedef std::map<long, pthread_t*> CalleeTidMap;
    CalleeTidMap callee_tid_map_;
};

#endif

// IPC
class IpcChecker : public MistChecker {
  public:
  virtual ~IpcChecker() {}
    virtual bool check(sp::SpPoint* pt,
                       sp::SpFunction* callee);
    virtual bool post_check(sp::SpPoint* pt,
                            sp::SpFunction* callee);
  protected:
    string port;
};

// Fork or exec
class Mist;
class ForkChecker : public MistChecker {
  public:
    ForkChecker(Mist* mist);
    virtual bool check(sp::SpPoint* pt,
                       sp::SpFunction* callee);
    virtual bool post_check(sp::SpPoint* pt,
                            sp::SpFunction* callee);
  private:
    Mist* mist_;
};

// Clone
class Mist;
class CloneChecker : public MistChecker {
  public:
    CloneChecker(Mist* mist);
    virtual bool check(sp::SpPoint* pt,
                       sp::SpFunction* callee);
    virtual bool post_check(sp::SpPoint* pt,
                            sp::SpFunction* callee);
  private:
    Mist* mist_;
};

// Check the changes of uid/gid
class ChangeIdChecker : public MistChecker {
  public:
    virtual bool check(sp::SpPoint* pt,
                       sp::SpFunction* callee);
    virtual bool post_check(sp::SpPoint* pt,
                            sp::SpFunction* callee) { return false; }
};

// Check when to exit
class ExitChecker : public MistChecker {
  public:
    virtual bool check(sp::SpPoint* pt,
                       sp::SpFunction* callee);
    virtual bool post_check(sp::SpPoint* pt,
                            sp::SpFunction* callee);
};

}
#endif /* _MISTCHECKER_H_ */
