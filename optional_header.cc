#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>

typedef struct _optionalheader {
    uint8_t magic[2];
    uint8_t majorlinkerversion[1];
    uint8_t minorlinkerversion[1];
    uint8_t sizeofcode[4];
    uint8_t sizeofinitdata[4];
    uint8_t sizeofunitdata[4];
    uint8_t addressofentrypoint[4];
    uint8_t baseofcode[4];
} PE32PlusOptionalHeader;

typedef struct _pe32optionalheader {
    struct _optionalheader;
    uint8_t baseofdata[4];
} PE32OptionalHeader;

typedef struct _optionalwindows {
    uint8_t imagebase[8];
    uint8_t sectionalignment[4];
    uint8_t filealignment[4];
    uint8_t majoroperatingsystemversion[2];
    uint8_t minoroperatingsystemversion[2];
    uint8_t majorimageversion[2];
    uint8_t minorimageversion[2];
    uint8_t majorsubsystemversion[2];
    uint8_t minorsubsystemversion[2];
    uint8_t win32versionvalue[4];
    uint8_t sizeofimage[4];
    uint8_t sizeofheaders[4];
    uint8_t checksum[4];
    uint8_t subsystem[4];
    uint8_t dllchars[2];
    uint8_t sizeofstackreserve[8];
    uint8_t sizeofstackcommit[8];
    uint8_t sizeofheapreserve[8];
    uint8_t sizeofheapcommit[8];
    uint8_t loaderflags[4];
    uint8_t numberofrva[4];
} PE32PlusWindowsOptional;

typedef struct _optionalpe32windows {
    uint8_t imagebase[4];
    uint8_t sectionalignment[4];
    uint8_t filealignment[4];
    uint8_t majoroperatingsystemversion[2];
    uint8_t minoroperatingsystemversion[2];
    uint8_t majorimageversion[2];
    uint8_t minorimageversion[2];
    uint8_t majorsubsystemversion[2];
    uint8_t minorsubsystemversion[2];
    uint8_t win32versionvalue[4];
    uint8_t sizeofimage[4];
    uint8_t sizeofheaders[4];
    uint8_t checksum[4];
    uint8_t subsystem[4];
    uint8_t dllchars[2];
    uint8_t sizeofstackreserve[4];
    uint8_t sizeofstackcommit[4];
    uint8_t sizeofheapreserve[4];
    uint8_t sizeofheapcommit[4];
    uint8_t loaderflags[4];
    uint8_t numberofrva[4];
} PE32WindowsOptional;

typedef struct _datadir {
    uint8_t virtualaddress[4];
    uint8_t size[4];
} DataDirectory;

typedef struct _optionalldatadirs {
    DataDirectory exporttable;
    DataDirectory importtable;
    DataDirectory resourcetable;
    DataDirectory exceptiontable;
    DataDirectory certificatetable;
    DataDirectory basereloctable;
    DataDirectory debug;
    DataDirectory arch;
    DataDirectory globalptr;
    DataDirectory tlstable;
    DataDirectory loadconftable;
    DataDirectory boundimport;
    DataDirectory iat;
    DataDirectory delayimport;
    DataDirectory clr;
    DataDirectory reserved;
} ListOfDataDirs;

typedef struct _sectiontable {
    char name;
    uint8_t virtualsize[4];
    uint8_t virtualaddress[4];
    uint8_t sizeofrawdata[4];
    uint8_t pointertorawdata[4];
    uint8_t pointertorelocations[4];
    uint8_t pointertolinenumbers[4];
    uint8_t numberofrelocations[2];
    uint8_t numberoflinenumbers[2];
    uint8_t chars[4];
} SectionTable;