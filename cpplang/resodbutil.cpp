#include <fcgi_stdio.h>//must be first

#include <string>

//#include "/home/joe/microjson/microjson-1.3/mjson.h"

#include "mydb.hpp"
#include "resodbutil.hpp"

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

//open array and close array
#define OA() printf("[\n")
#define CA() printf("\n]")

//open array and close object
#define OO() printf("{\n")
#define CO() printf("}\n")

//name: and name: string value
#define N(N) printf("\"%s\":" ,N)
#define N_SV(N,SV) printf("\"%s\" : \"%s\"",N,SV)
#define N_DV(N,DV) printf("\"%s\" : \"%f\"",N,DV)

#define M() printf(",\n")

void ResoCoreUtil::ToJson(
  struct reso_core* core) {
    OO();
      N("Listing");
      OO();
        N_SV("ListingKey",(core->Listing).ListingKey),M();
        N_SV("ListingId",(core->Listing).ListingId),M();
        N_SV("OriginatingSystemKey",(core->Listing).OriginatingSystemKey),M();
        N_SV("OriginatingSystemName",(core->Listing).OriginatingSystemName),M();
        N("Price");
        OO();
          N_DV("ListPrice",(core->Listing).Price.ListPrice);
        CO();//Listing.Price
      CO();M();//Listing
      N("Property");
      OO();
        N_SV("PropertyType",(core->Property).PropertyType);M();
        N_SV("PropertySubType",(core->Property).PropertySubType);M();
        N("Characteristics");
        OO();
        CO();M();//Property.Characteristics
        N("Finance");
        OO();
        CO();M();//Property.Finance
        N("Location");
        OO();
        CO();M();//Property.Location
        N("Structure");
        OO();
        CO();M();//Property.Structure
        N("Tax");
        OO();
        CO();//Property.Tax
      CO();//Property
    CO();//unnamed container which is ResoCore
    return;
}

void ResoCoreUtil::Initialize(
  struct reso_core* core) {
    if (core==nullptr) return;
    else {
      (core->Listing).ListingKey[0]='\0';
      (core->Listing).ListingId[0]='\0';
      (core->Listing).OriginatingSystemKey[0]='\0';
      (core->Listing).OriginatingSystemName[0]='\0';

      (core->Listing).Price.ListPrice=0.0;

      (core->Property).PropertyType[0]='\0';
      (core->Property).PropertySubType[0]='\0';
    return;
  }
}



void ResoCoreQuery::GetAll(FILE *out, long unsigned int maxRecords) {
  int i=0;
  mydb::Context con;
  con.Open();
  bool trnret = con.BeginTxn();
  if (trnret==true){
    mydb::Cursor cur(con);
    ResoCoreUtil u;
    size_t dsz; size_t ksz;
    void *key; void *data;
    bool ret=false;
    OA();
    if ( (ret=cur.First(&ksz, &key, &dsz, &data))==true){
      u.ToJson((struct reso_core*)data);
      while(ret==true){
        if(i++>maxRecords) break;
        ret = cur.Next(&ksz, &key, &dsz, &data);
        if (ret==true){
          M();
          u.ToJson((struct reso_core*)data);
        }
      }
    }
    CA();
  }
  bool trncommit = con.EndTxn();
}



}
