
//copyright 2015 joe wehrli, all rights reserved; commercial licensing only
//RESO Data Dictionary 1.3 FINAL
#include <ctime>

struct ResoCore {
    struct Listing Listing;
    struct Property Property;
}

#define CHARSIZE_COMMON1 255;
#define CHARSIZE_ListingKey CHARSIZE_COMMON1;
#define CHARSIZE_ListingId CHARSIZE_COMMON1;
#define CHARSIZE_ListAOR 50;
#define CHARSIZE_StandardStatus 50;
struct Listing {
  char ListingKey[CHARSIZE_ListingKey];
  char ListingId[CHARSIZE_ListingKey];
  char ListAOR[CHARSIZE_ListAOR];
  char StandardStatus[CHARSIZE_StandardStatus];
  struct ListingDates ListingDates;
  struct Price Price;
}

struct ListingDates {
  std:time_t OnMarketDate;
}

struct Price {
  float ListPrice;
  float OriginalListPrice;
}

#define CHARSIZE_PropertyType 50;
struct Property {
  char PropertyType[CHARSIZE_PropertyType];
  struct Characteristics Characteristics;
}


struct Location {
  struct Address Address;
}

#define CHARSIZE_PostalCode 10
struct Address {
  char PostalCode[CHARSIZE_PostalCode];
}

#define CHARSIZE_LotSizeUnits 25;
struct Characteristics {
  double LotSizeArea;
  char LotSizeUnits[CHARSIZE_LotSizeUnits];
}
