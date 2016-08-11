
#include <initializer_list>
#undef _GLIBCXX_HAVE_GETS

#include <cstdio>

#include <string>
#include <cstring>

#include "mydb.hpp"
#include "resodb.hpp"
#include "resodbutil.hpp"

void ResoCoreCursor(long unsigned int, bool,bool,bool);

void MakeDB(size_t mb);

int main()
{
  size_t mb=750;
  long unsigned int ops = 200000;
  MakeDB(mb);

  ResoCoreCursor(ops,true,false,false);
  //ResoCoreCursor(ops,false,true,false);
  //ResoCoreCursor(ops,false,false,true);

  return 0;
}


void MakeDB(size_t mb){
    mydb::Context con;
    bool r;
    r= con.Open(true,mb);//set size to xMB
    r= con.BeginTxn();
    r= con.EndTxn(true);
}


void ResoCoreCursor(long unsigned int ops,
    bool write, bool getCopy, bool iterate){

    long unsigned int recCnt=ops;
    long unsigned int ioCnt=ops*0.001;

    size_t recSize = sizeof(struct reso_core);
    size_t dbSize = recSize * recCnt;
    size_t dbMB = dbSize / 10485760;
    mydb::Context con;
    con.Open();
    printf("Test Record: %d Count, %d Byte Size %s\n",recCnt,recSize,"ResoCoreCursor");
    printf("Test: %d Bytes, %d MB Database: %s\n",dbSize,dbMB,"ResoCoreCursor");
    if (write){
      bool trnret = con.BeginTxn();
      struct reso_core rs;
      mydb::ResoCoreUtil rUtil;
      long unsigned int lui;
      for (lui=0; lui<recCnt; lui++) {
        rUtil.Initialize(&rs);
        std::string result = std::to_string(lui);
        bool ret=false;
        if( result.length() < CHARSIZE_ListingKey ){
          char* cstr= (char*) &(rs.Listing.ListingKey);
          std::strcpy (cstr, result.c_str());

          ret = con.Write(
            //sizeof(char)*CHARSIZE_ListingKey,/*bug without clearing memory*/
            result.length()+1,//use actual string length - saves a few bytes
            (void*)&(rs.Listing.ListingKey),
            sizeof(struct reso_core), (void*)&rs);
        }

        if (ret==true) {
          if(((lui+1) % ioCnt)==0)
            printf("Write SUCCESS k=%s\n",rs.Listing.ListingKey);
        }
        else if ((lui+1)%ioCnt==0)printf("Write FAILED k=%s\n",rs.Listing.ListingKey);
      }
      bool trncommit = con.EndTxn();
      if (trncommit==true) printf("COMMIT SUCCESS\n");
      else printf("COMMIT FAIL\n");
    }
    if (getCopy){/*
      long unsigned int *x2;
      long unsigned int lui;
      for (lui=0; lui<recCnt; lui++) {
        bool ret = con.GetCopy(sizeof(long unsigned int), (void*)&lui, (void**) &x2);
        if (ret==true){
          if (((lui+1) % ioCnt)==0)
            printf("GetCopy SUCCESS %lu %lu %lu %lu\n",lui,x2[0],x2[1],x2[colCount-2]);
          delete x2;
        }
        else{
          printf("GetCopy FAILED %lu\n",lui);
        }
      }*/
    }
    if (iterate==true){
      bool trnret = con.BeginTxn();
      if (trnret==true){
        mydb::Cursor cur(con);
        long unsigned int lui=0;
        size_t dsz;
        size_t ksz;
        void *key;
        void *data;
        bool ret=false;
        do {
          if (lui==0)
            ret = cur.First(&ksz, &key, &dsz, &data);
          else
            ret = cur.Next(&ksz, &key, &dsz, &data);

          if (ret==true && (lui+1)%ioCnt==0){
            if (lui==0)
            printf("Cursor.First() SUCCESS i=%lu k=%s d=%s\n",
              lui,
              (char*)key,
              (*((struct reso_core*)data)).Listing.ListingKey
            );
            else
            printf("Cursor.Next() SUCCESS i=%lu k=%s d=%s\n",
            lui,
            (char*)key,
            (*((struct reso_core*)data)).Listing.ListingKey
            );
          }
          else {
            if (ret==false && lui !=0) printf("Cursor.Next() FAILED \n");
            else if (ret==false) printf("Cursor.First() FAILED \n");
          }
          lui++;
        } while(ret==true);
      }
      bool trncommit = con.EndTxn();
    }
    return;
}
