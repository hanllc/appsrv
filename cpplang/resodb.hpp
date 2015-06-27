
//copyright 2015 joe wehrli, all rights reserved; commercial licensing only
//RESO Data Dictionary 1.3 FINAL
#include <ctime>


struct listing_dates {
  std::time_t OnMarketDate;
};

struct price {
  double ListPrice;
  double OriginalListPrice;
};

#define CHARSIZE_COMMON1 255
#define CHARSIZE_ListingKey CHARSIZE_COMMON1
#define CHARSIZE_ListingId CHARSIZE_COMMON1
#define CHARSIZE_ListAOR 50
#define CHARSIZE_StandardStatus 50
struct listing {
  char ListingKey[CHARSIZE_ListingKey];
  char ListingId[CHARSIZE_ListingId];
  char ListAOR[CHARSIZE_ListAOR];
  char StandardStatus[CHARSIZE_StandardStatus];
  struct listing_dates ListingDates;
  struct price Price;
};

#define CHARSIZE_LotSizeUnits 25
struct characteristics {
  double LotSizeArea;
  char LotSizeUnits[CHARSIZE_LotSizeUnits];
};

#define CHARSIZE_PostalCode 10
struct address {
  char PostalCode[CHARSIZE_PostalCode];
};

struct location {
  struct address Address;
};

#define CHARSIZE_PropertyType 50
struct property {
  char PropertyType[CHARSIZE_PropertyType];
  struct location Location;
  struct characteristics Characteristics;
};

struct reso_core {
    struct listing Listing;
    struct property Property;
};
