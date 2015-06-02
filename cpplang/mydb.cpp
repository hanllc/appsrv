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
void Context::Open(){
  if (envCreateReturn!=0) return;
  MDB_dbi dbs = 1;
  int maxdbsReturn = mdb_env_set_maxdbs(envHandle,dbs);

  envOpenReturn = mdb_env_open(envHandle, 
			       "/home/joe/mydb",0,0664);
  if (envOpenReturn!=0){
    mdb_env_close(envHandle);
    envHandle=nullptr;
  }
}
void Context::Write(size_t ksz, void* key, 
		    size_t dsz, void* data){
  if (envHandle!=nullptr){
    MDB_txn *txn;
    int txnret = mdb_txn_begin(envHandle,nullptr,0,&txn);

    MDB_dbi dbi;
    int dbiret = mdb_dbi_open(txn,"Entity",MDB_CREATE,&dbi);
    Error(dbiret);

    MDB_val kkey { ksz, key };
    MDB_val ddata { dsz, data};

    putReturn = mdb_put(txn,dbi,&kkey,&ddata,0);
    Error(dbiret);

    int commit = mdb_txn_commit(txn);
  }
}
void Context::GetCopy(size_t ksz, void* key, 
		   void** data){
  if (envHandle!=nullptr){
    MDB_txn *txn;
    int txnret = mdb_txn_begin(envHandle,nullptr,0,&txn);
    MDB_dbi dbi;
    int dbiret = mdb_dbi_open(txn,"Entity",0,&dbi);
    MDB_val kkey { ksz, key };
    MDB_val ddata;
    int get = mdb_get(txn,dbi,&kkey,&ddata);
    int i=0;
    *data = new char[ddata.mv_size];
    memcpy(*data, (void*)ddata.mv_data, (ddata.mv_size)*sizeof(char));
    int commit = mdb_txn_commit(txn);
  }
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
