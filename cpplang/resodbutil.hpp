#ifndef RESODBUTIL_H_INCLUDED
#define RESODBUTIL_H_INCLUDED

#include <iostream>
#include <fcgio.h>

#include "resodb.hpp"

using namespace std;

namespace mydb {


class ResoCoreUtil {
  public:
    //bool JsonWrite(std::string json, struct ResoCore& core);

  void ToJson(struct reso_core* core, std::ostream& os);
  //void ToJson(FILE* out, struct reso_core* core);

  void Initialize(struct reso_core* core);
};

class ResoCoreQuery {
  public:
  void GetAll(std::ostream& os, long unsigned int maxRecords=4);
};


}


#endif
