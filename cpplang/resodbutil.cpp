#include <initializer_list>
#undef _GLIBCXX_HAVE_GETS

#include <string>
#include "resodbutil.hpp"
#include "/home/joe/microjson/microjson-1.3/mjson.h"

namespace mydb {


bool ResoCoreUtil::JsonWrite(
  std::string json,
  struct ResoCore& core) {
    //leverage library to hydrate the ResoCore structure definitions
    //mjson - fast parse of JSON to fixed-extent C structures
    
    return true;
}

}
