//copyright 2015 joe wehrli, all rights reserved; commercial licensing only
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
    friend class Cursor;
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
  };
  class Cursor {
    MDB_cursor *cur;
    int curOpenRet;
    int curGetRet;
    MDB_val kkey;
    MDB_val ddata;
    bool GetOp(size_t *ksz, void **key, size_t *dsz, void **data,
        enum MDB_cursor_op op);
    public:
      Cursor(Context &con);
      ~Cursor();
      bool First(size_t *ksz, void **key, size_t *dsz, void **data);
      bool Next(size_t *ksz, void **key, size_t *dsz, void **data);
      bool Set(size_t *ksz, void **key, size_t *dsz, void **data);
  };
}
