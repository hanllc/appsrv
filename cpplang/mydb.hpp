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
  public:
    Context();
    ~Context();
    void Open();
    void Write(size_t ksz, void* key, 
	       size_t dsz, void* data);
    void GetCopy(size_t ksz, void* key, 
	      void **data);
  };
}
