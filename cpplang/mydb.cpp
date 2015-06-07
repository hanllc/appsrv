//mydb copyright 2015 joe wehrli
#include <errno.h>
#include <string.h>
#include <lmdb.h>
#include "mydb.hpp"

namespace mydb {


Context::Context() {
    envCreateReturn = mdb_env_create (&envHandle);
}
Context::~Context() {
  if (envHandle!=nullptr){
    mdb_env_close (envHandle);
    envHandle=nullptr;
  }
}
bool Context::Open(bool setSize, size_t dbMegabytes,size_t osPageSize){
  size_t mbbytes = 10485760;
  if ((dbMegabytes*mbbytes % osPageSize) != 0){
    return false;
  }
  else if (envCreateReturn!=0){
    return false;
  }
  else {
    MDB_dbi dbs = 1;
    int maxdbsReturn = mdb_env_set_maxdbs(envHandle,dbs);
    if (maxdbsReturn !=0){
      Error(maxdbsReturn);
      return false;
    }
    else{
      int mapsizeReturn=0;
      if (setSize==true){
        size_t bytes = dbMegabytes*mbbytes;
        mapsizeReturn = mdb_env_set_mapsize(envHandle,bytes);
      }
      if(setSize==true && mapsizeReturn!=0){
        Error(mapsizeReturn);
        return false;
      }
      envOpenReturn = mdb_env_open(envHandle,
  			       "/home/joe/mydb",0,0664);
      if (envOpenReturn!=0){
        Error(envOpenReturn);
        mdb_env_close(envHandle);
        envHandle=nullptr;
        return false;
      }
      else return true;
    }
  }
}
bool Context::Write(size_t ksz, void* key,
		    size_t dsz, void* data){
  Error(0);
  if (envHandle==nullptr){
    return false;
  }
  else{
    MDB_txn *txn;
    int txnret = mdb_txn_begin(envHandle,nullptr,0,&txn);
    if (txnret != 0) {
      Error(txnret);
      return false;
    }
    else{
      MDB_dbi dbi;
      int dbiret = mdb_dbi_open(txn,"Entity",MDB_CREATE,&dbi);
      if (dbiret != 0){
        Error(dbiret);
        mdb_txn_abort(txn);
        return false;
      }
      else{
        MDB_val kkey { ksz, key };
        MDB_val ddata { dsz, data};
        putReturn = mdb_put(txn,dbi,&kkey,&ddata,0);
        if (putReturn !=0){
          Error(putReturn);
          mdb_txn_abort(txn);
          return false;
        }
        else{
          int commit = mdb_txn_commit(txn);
          if (commit!=0){
            Error(commit);
            return false;
          }
          else return true;
        }
      }
    }
  }
}
bool Context::GetCopy(size_t ksz, void* key,
		   void** data){
  Error(0);
  if (envHandle==nullptr){
    return false;
  }
  else{
    MDB_txn *txn;
    int txnret = mdb_txn_begin(envHandle,nullptr,0,&txn);
    if (txnret != 0){
      Error(txnret);
      return false;
    }
    else{
      MDB_dbi dbi;
      int dbiret = mdb_dbi_open(txn,"Entity",0,&dbi);
      if (dbiret !=0){
        Error(dbiret);
        mdb_txn_abort(txn);
        return false;
      }
      else{
        MDB_val kkey { ksz, key };
        MDB_val ddata;
        int get = mdb_get(txn,dbi,&kkey,&ddata);
        if (get!=0){
          Error(get);
          mdb_txn_abort(txn);
          return false;
        }
        else {
          //int i=0;
          *data = new char[ddata.mv_size];
          memcpy(*data, (void*)ddata.mv_data, (ddata.mv_size)*sizeof(char));
          int commit = mdb_txn_commit(txn);
          if (commit!=0){
            Error(commit);
            delete (char*)(*data);
            return false;
          }
          else return true;
        }
      }
    }
  }
}
void Context::Iterate(){
    MDB_txn *txn;
    int txnret = mdb_txn_begin(envHandle,nullptr,0,&txn);
    MDB_dbi dbi;
    int dbiret = mdb_dbi_open(txn,"Entity",0,&dbi);
    MDB_cursor *cur;
    int curret = mdb_cursor_open(txn,dbi,&cur);
    MDB_val key;
    MDB_val data;
    int curgetret = mdb_cursor_get(cur,&key,&data,MDB_FIRST);
    while(curgetret==0){
      curgetret = mdb_cursor_get(cur,&key,&data,MDB_NEXT);
    }
    mdb_cursor_close(cur);
    int commit = mdb_txn_commit(txn);
}
void Context::Error(int er){
    errorMsg = mdb_strerror(er);
    switch(er){
    case MDB_SUCCESS:
      break;
    case MDB_MAP_FULL:
      break;
    case MDB_TXN_FULL:
      break;
    case EACCES:
      break;
    case EINVAL:
      break;
    }
}

}
