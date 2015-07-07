#include <initializer_list>
#undef _GLIBCXX_HAVE_GETS

#include <fcgi_stdio.h>

//#include <string>

#include "resodbutil.hpp"
//#include "/home/joe/microjson/microjson-1.3/mjson.h"
#include "/home/joe/minijson/minijson_writer/minijson_writer.hpp"

#include "mydb.hpp"

namespace mydb {

/*
bool ResoCoreUtil::JsonSave(
  std::string json,
  struct ResoCore& core) {
    //leverage library to hydrate the ResoCore structure definitions
    //mjson - fast parse of JSON to fixed-extent C structures

    return true;
}
*/

void ResoCoreUtil::ToJson(
  struct reso_core* core) {
    printf("Cursor.Next() d=%s\n",
    (core->Listing).ListingKey
    );

    return;
}

void ResoCoreQuery::GetAll(FILE *out) {
  mydb::Context con;
  con.Open();
  bool trnret = con.BeginTxn();
  if (trnret==true){
    mydb::Cursor cur(con);
    ResoCoreUtil u;
    size_t dsz; size_t ksz;
    void *key; void *data;
    bool ret=false;
    if ( (ret=cur.First(&ksz, &key, &dsz, &data))==true){
      u.ToJson((struct reso_core*)data);
      while(ret==true){
        ret = cur.Next(&ksz, &key, &dsz, &data);
        if (ret==true)
          u.ToJson((struct reso_core*)data);
      }
    }
  }
  bool trncommit = con.EndTxn();
}


}
