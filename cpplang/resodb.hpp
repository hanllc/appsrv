
#ifndef RESODB_H_INCLUDED
#define RESODB_H_INCLUDED

//RESO Data Dictionary 1.4 FINAL
#include <ctime>


struct listing_dates {
  std::time_t ListingContractDate;
  std::time_t ContractStatusChangeDate;
  std::time_t ExpirationDate;
  std::time_t CancelationDate;
  std::time_t ContingentDate;
  std::time_t WithdrawnDate;
  std::time_t PurchaseContractDate;
  std::time_t CloseDate;
  std::time_t OnMarketDate;
  std::time_t OffMarketDate;
  std::time_t ModificationTimestamp;
  std::time_t StatusChangeTimestamp;
  std::time_t OriginalEntryTimestamp;
};

struct media {
  short int PhotosCount;
  std::time_t PhotosChangeTimestamp;
};

struct price {
  double ClosePrice;
  double ListPrice;
  double OriginalListPrice;
};
/*
struct remarks {
  char PublicRemarks[char CHARSIZE_PublicRemarks];
  char SyndicationRemarks[char ]
}
*/
#define CHARSIZE_COMMON1 255
#define CHARSIZE_ListingKey CHARSIZE_COMMON1
#define CHARSIZE_ListingId CHARSIZE_COMMON1
#define CHARSIZE_OriginatingSystemKey CHARSIZE_COMMON1
#define CHARSIZE_OriginatingSystemName CHARSIZE_COMMON1
#define CHARSIZE_ListingService 25
#define CHARSIZE_ListingAgreement 25
#define CHARSIZE_ListAOR 50
#define CHARSIZE_StandardStatus 50
#define CHARSIZE_MlsStatus 50
struct listing {
  char ListingKey[CHARSIZE_ListingKey];
  char ListingId[CHARSIZE_ListingId];
  char OriginatingSystemKey[CHARSIZE_OriginatingSystemKey];
  char OriginatingSystemName[CHARSIZE_OriginatingSystemName];
  char ListingService[CHARSIZE_ListingService];
  char ListingAgreement[CHARSIZE_ListingAgreement];
  //not core //char ListAOR[CHARSIZE_ListAOR];
  char StandardStatus[CHARSIZE_StandardStatus];
  char MlsStatus[CHARSIZE_MlsStatus];
  struct listing_dates ListingDates;
  struct media Media;
  struct price Price;
  //struct remarks Remarks; //ommitted due to size
};

#define CHARSIZE_LotSizeUnits 25
#define CHARSIZE_LeaseTerm 25
struct characteristics {
  double LotSizeArea;
  char LotSizeUnits[CHARSIZE_LotSizeUnits];
  char LeaseTerm[CHARSIZE_LeaseTerm];
  bool LandLeaseYN;
  int NumberOfUnitsTotal;
};

struct finance {
  double GrossScheduledIncome;
  double GrossIncome;
  double OperatingExpense;
  double NetOperatingIncome;
  double CapRate;
};

#define CHARSIZE_StreetNumber 25
#define CHARSIZE_StreetDirPrefix 15
#define CHARSIZE_StreetName 50
#define CHARSIZE_StreetAdditionalInfo 50
#define CHARSIZE_StreetSuffix 25
#define CHARSIZE_StreetSuffixModifier 25
#define CHARSIZE_StreetDirSuffix 15
#define CHARSIZE_UnitNumber 25
#define CHARSIZE_City 50
#define CHARSIZE_StateOrProvince 2
#define CHARSIZE_Country 2
#define CHARSIZE_PostalCode 10
#define CHARSIZE_PostalCodePlus4 4
#define CHARSIZE_UnparsedAddress 255
#define CHARSIZE_PostalCity 50
#define CHARSIZE_CountyOrParish 50
#define CHARSIZE_Township 50
struct address {
  char StreetNumber[CHARSIZE_StreetNumber];
  long int StreetNumberNumeric;
  char StreetDirPrefix[CHARSIZE_StreetDirPrefix];
  char StreetName[CHARSIZE_StreetName];
  char StreetAdditionalInfo[CHARSIZE_StreetAdditionalInfo];
  char StreetSuffix[CHARSIZE_StreetSuffix];
  char StreetSuffixModifier[CHARSIZE_StreetSuffixModifier];
  char StreetDirSuffix[CHARSIZE_StreetDirSuffix];
  char UnitNumber[CHARSIZE_UnitNumber];
  char City[CHARSIZE_City];
  char StateOrProvince[CHARSIZE_StateOrProvince];
  char County[CHARSIZE_Country];
  char PostalCode[CHARSIZE_PostalCode];
  char PostalCodePlus4[CHARSIZE_PostalCodePlus4];
  char UnparsedAddress[CHARSIZE_UnparsedAddress];
  char PostalCity[CHARSIZE_PostalCity];
  char CountyOrParish[CHARSIZE_CountyOrParish];
  char Township[CHARSIZE_Township];
};

#define CHARSIZE_MLSAreaMajor 50
#define CHARSIZE_SubdivisionName 50
struct area {
  char MLSAreaMajor[CHARSIZE_MLSAreaMajor];
  char SubdivisionName[CHARSIZE_SubdivisionName];
};

struct gis {
  double Latitude;
  double Longitude;
};

struct location {
  struct address Address;
  struct area Area;
  struct gis GIS;
};

#define CHARSIZE_LivingAreaUnits 25
#define CHARSIZE_Levels 1024
#define CHARSIZE_Make 50
#define CHARSIZE_Model 50
struct structure {
    short int BedRoomsTotal;
    short int BathroomsTotalInteger;
    short int BathroomsFull;
    short int BathroomsHalf;
    short int BathroomsThreeQuarter;
    short int BathroomsOneQuarter;
    double LivingArea;
    char LivingAreaUnits[CHARSIZE_LivingAreaUnits];
    bool PropertyAttachedYN;
    bool GarageYN;
    double GarageSpaces;
    short int StoriesTotal;
    char Levels[CHARSIZE_Levels];
    int YearBuilt;
    int MobileLength;
    int MobileWidth;
    char Make[CHARSIZE_Make];
    char Model[CHARSIZE_Model];
};

#define CHARSIZE_ParcelNumber 50
struct tax{
    char ParcelNumber[CHARSIZE_ParcelNumber];
};

#define CHARSIZE_PropertyType 50
#define CHARSIZE_PropertySubType 50
struct property {
  char PropertyType[CHARSIZE_PropertyType];
  char PropertySubType[CHARSIZE_PropertySubType];
  struct characteristics Characteristics;
  struct finance Finance;
  struct location Location;//really under listing?
  struct structure Structure;
  struct tax Tax;
};

struct reso_core {
    struct listing Listing;
    struct property Property;
};

#endif
