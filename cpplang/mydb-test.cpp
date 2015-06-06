//mydb copyright 2015 joe wehrli

#include <initializer_list>
#undef _GLIBCXX_HAVE_GETS

//#include <stdio.h>
#include <cstdio>
//#include <stdlib.h>
#include <string>
#include "mydb.hpp"

void LargeRecordCursor(long unsigned int, bool,bool);

int main()
{
  long unsigned int ops = 2500;
  //LargeRecordCursor(ops,false,false);

  //LargeRecordCursor(ops,true,false);
  LargeRecordCursor(ops,false,true);
  return 0;
}





void LargeRecordCursor(long unsigned int ops, bool write, bool getCopy){

    long unsigned int recCnt=ops;
    long unsigned int ioCnt=ops*0.1;

    int colCount=4096/sizeof(long unsigned int);
    size_t recSize = sizeof(long unsigned int)*colCount;
    size_t dbSize = recSize * recCnt;
    size_t dbMB = dbSize / 10485760;
    mydb::Context con;
    con.Open();
    printf("Test Record: %d Count, %d Byte Size %s\n",recCnt,recSize,"LargeRecordCursor");
    printf("Test: %d Bytes, %d MB Database: %s\n",dbSize,dbMB,"LargeRecordCursor");
    if (write){

      long unsigned int x[colCount];
      for (int i=0; i<colCount; i++) x[i]=colCount-i;

      long unsigned int lui;
      for (lui=0; lui<recCnt; lui++) {
        x[0]=colCount+lui;
        bool ret = con.Write(sizeof(long unsigned int), (void*)&lui,
          sizeof(long unsigned int)*colCount, (void*)&x);
        if (ret==true) {
          if(((lui+1) % ioCnt)==0)
            printf("Write SUCCESS %lu %lu %lu %lu\n",lui,x[0],x[1],x[colCount-2]);
        }
        else printf("Write FAILED %lu %lu %lu %lu\n",lui,x[0],x[1],x[colCount-2]);
      }
    }
    if (getCopy){
      long unsigned int *x2;
      //con.Iterate();
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
      }
    }
    return;
}

void SingleReadWrite(){
    mydb::Context con;

    con.Open();

    printf("Test %d: %s\n",1,"SingleReadWrite");

    std::string strKey="69";
    std::string strData = "abc\0";
    const char* key = strKey.c_str();
    const char* data = strData.c_str();

    printf("KeyLen=%d DataLen=%d Data=%s\n",strKey.length(),strData.length(),data);
    printf("%c %c %c %c\n",data[0],data[1],data[2],data[3]);

    con.Write(strKey.length(), (void*)key, strData.length(), (void*)data);

    char *data2;
    con.GetCopy(strKey.length(), (void*)key, (void**) &data2);


    printf("KeyLen=%d DataLen=%d Data=%s\n",strKey.length(),strData.length(),data2);
    printf("%c %c %c %c\n",data2[0],data2[1],data2[2],data2[3]);


    delete data2;
  return;
}
