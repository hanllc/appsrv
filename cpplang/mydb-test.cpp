
#include <initializer_list>
#undef _GLIBCXX_HAVE_GETS

#include <cstdio>
#include <string>
#include "mydb.hpp"

void LargeRecordCursor(long unsigned int, bool,bool,bool);
void MakeDB(size_t mb);

int main()
{
  size_t mb=100;
  long unsigned int ops = 1000;
  //MakeDB(mb);

  //LargeRecordCursor(ops,true,false,false);

  //LargeRecordCursor(ops,false,true,false);

  LargeRecordCursor(ops,false,false,true);
  return 0;
}


void MakeDB(size_t mb){
    mydb::Context con;
    bool r;
    r= con.Open(true,mb);//set size to xMB
    r= con.BeginTxn();
    r= con.EndTxn(true);
}


void LargeRecordCursor(long unsigned int ops,
    bool write, bool getCopy, bool iterate){

    long unsigned int recCnt=ops;
    long unsigned int ioCnt=ops*0.001;

    int colCount;
    //colCount=4096/sizeof(long unsigned int);
    colCount=20;
    size_t recSize = sizeof(long unsigned int)*colCount;
    size_t dbSize = recSize * recCnt;
    size_t dbMB = dbSize / 10485760;
    mydb::Context con;
    con.Open();
    printf("Test Record: %d Count, %d Byte Size %s\n",recCnt,recSize,"LargeRecordCursor");
    printf("Test: %d Bytes, %d MB Database: %s\n",dbSize,dbMB,"LargeRecordCursor");
    if (write){
      bool trnret = con.BeginTxn();
      long unsigned int x[colCount];
      for (int i=0; i<colCount; i++) x[i]=i;

      long unsigned int lui;
      for (lui=0; lui<recCnt; lui++) {
        x[0]=lui+1;
        bool ret = con.Write(sizeof(long unsigned int), (void*)&lui,
          sizeof(long unsigned int)*colCount, (void*)&x);
        if (ret==true) {
          if(((lui+1) % ioCnt)==0)
            printf("Write SUCCESS k=%lu d[0]=%lu d[last]=%lu\n",lui,x[0],x[colCount-1]);
        }
        else if ((lui+1)%ioCnt==0)printf("Write FAILED k=%lu d[0]=%lu d[last]=%lu\n",lui,x[0],x[colCount-1]);
      }
      bool trncommit = con.EndTxn();
      if (trncommit==true) printf("COMMIT SUCCESS\n");
      else printf("COMMIT FAIL\n");
    }
    if (getCopy){
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
      }
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
        bool ret;
        do {
          if (lui==0)
            ret = cur.First(&ksz, &key, &dsz, &data);
          else
            ret = cur.Next(&ksz, &key, &dsz, &data);

          if (ret==true && (lui+1)%ioCnt==0){
            if (lui==0)
            printf("Cursor.First() SUCCESS i=%lu k=%lu d[0]=%lu\n",
              lui,
              *((unsigned long int*)key),
              ((unsigned long int*)data)[0]
            );
            else
            printf("Cursor.Next() SUCCESS i=%lu k=%lu d[0]=%lu\n",
              lui,
              *((unsigned long int*)key),
              ((unsigned long int*)data)[0]
            );
          }
          else {
            if (ret==false && lui !=0) printf("Cursor.Next() FAILED \n");
            else if(ret==false) printf("Cursor.First() FAILED \n");
          }
          lui++;
        } while(ret==true);
      }
      bool trncommit = con.EndTxn();
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
