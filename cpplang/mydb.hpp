//mydb copyright 2015 joe wehrli
#include <lmdb.h>

namespace mydb {
  class Context {
    int envCreateReturn;
    int envOpenReturn;
    int putReturn;
    MDB_env *envHandle;
    char* errorMsg;
    void Error(int er);
    MDB_txn *txnHandle;
    MDB_dbi dbiHandle;
  public:
    Context();
    ~Context();
    bool Open(bool setSize=false,size_t dbMegabytes=1,size_t osPageSize=4096);
    bool BeginTxn();
    bool EndTxn(bool commit=true);

    bool Write(size_t ksz, void* key,
	       size_t dsz, void* data);
    bool GetCopy(size_t ksz, void* key,
	      void **data);
    void Iterate();
  };
}
