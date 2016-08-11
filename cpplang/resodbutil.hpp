#ifndef RESODBUTIL_H_INCLUDED
#define RESODBUTIL_H_INCLUDED

#include "resodb.hpp"


namespace mydb {


class ResoCoreUtil {
  public:
    //bool JsonWrite(std::string json, struct ResoCore& core);
    void ToJson(struct reso_core* core);
    void Initialize(struct reso_core* core);
};

class ResoCoreQuery {
  public:
    void GetAll(FILE *out, long unsigned int maxRecords=200);
};


}


#endif
