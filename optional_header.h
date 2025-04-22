#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>

typedef struct _optionalheader {
    uint16_t magic;
    uint8_t majorlinkerversion;
    uint8_t minorlinkerversion;
    uint32_t sizeofcode;
    uint32_t sizeofinitdata;
    uint32_t sizeofunitdata;
    uint32_t addressofentrypoint;
    uint32_t baseofcode;
    uint32_t baseofdata = 0;
} PE32PlusOptionalHeader;

typedef struct _optionalwindows {
    uint64_t imagebase;
    uint32_t sectionalignment;
    uint32_t filealignment;
    uint16_t majoroperatingsystemversion;
    uint16_t minoroperatingsystemversion;
    uint16_t majorimageversion;
    uint16_t minorimageversion;
    uint16_t majorsubsystemversion;
    uint16_t minorsubsystemversion;
    uint32_t win32versionvalue;
    uint32_t sizeofimage;
    uint32_t sizeofheaders;
    uint32_t checksum;
    uint32_t subsystem;
    uint16_t dllchars;
    uint64_t sizeofstackreserve;
    uint64_t sizeofstackcommit;
    uint64_t sizeofheapreserve;
    uint64_t sizeofheapcommit;
    uint32_t loaderflags;
    uint32_t numberofrva;
} PE32PlusWindowsOptional;

typedef struct _optionalpe32windows {
    uint32_t imagebase;
    uint32_t sectionalignment;
    uint32_t filealignment;
    uint16_t majoroperatingsystemversion;
    uint16_t minoroperatingsystemversion;
    uint16_t majorimageversion;
    uint16_t minorimageversion;
    uint16_t majorsubsystemversion;
    uint16_t minorsubsystemversion;
    uint32_t win32versionvalue;
    uint32_t sizeofimage;
    uint32_t sizeofheaders;
    uint32_t checksum;
    uint32_t subsystem;
    uint16_t dllchars;
    uint32_t sizeofstackreserve;
    uint32_t sizeofstackcommit;
    uint32_t sizeofheapreserve;
    uint32_t sizeofheapcommit;
    uint32_t loaderflags;
    uint32_t numberofrva;
} PE32WindowsOptional;

typedef struct _datadir {
    uint32_t virtualaddress;
    uint32_t size;
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
    uint32_t virtualsize;
    uint32_t virtualaddress;
    uint32_t sizeofrawdata;
    uint32_t pointertorawdata;
    uint32_t pointertorelocations;
    uint32_t pointertolinenumbers;
    uint16_t numberofrelocations;
    uint16_t numberoflinenumbers;
    uint32_t chars;
} SectionTable;

typedef struct _oh_returndata {
    std::string magic;
    std::string majorlinkerversion;
    std::string minorlinkerversion;
    std::string sizeofcode;
    std::string sizeofinitdata;
    std::string sizeofunitdata;
    std::string addressofentrypoint;
    std::string baseofcode;
    std::string baseofdata;
    std::string imagebase;
    std::string sectionalignment;
    std::string filealignment;
    std::string majoroperatingsystemversion;
    std::string minoroperatingsystemversion;
    std::string majorimageversion;
    std::string minorimageversion;
    std::string majorsubsystemversion;
    std::string minorsubsystemversion;
    std::string win32versionvalue;
    std::string sizeofimage;
    std::string sizeofheaders;
    std::string checksum;
    std::string subsystem;
    std::string dllchars;
    std::string sizeofstackreserve;
    std::string sizeofstackcommit;
    std::string sizeofheapreserve;
    std::string sizeofheapcommit;
    std::string loaderflags;
    std::string numberofrva;
    std::string exporttable;
    std::string importtable;
    std::string resourcetable;
    std::string exceptiontable;
    std::string certificatetable;
    std::string basereloctable;
    std::string debug;
    std::string arch;
    std::string globalptr;
    std::string tlstable;
    std::string loadconftable;
    std::string boundimport;
    std::string iat;
    std::string delayimport;
    std::string clr;
    std::string reserved;
} oh_returndata;

oh_returndata get_optional_header(std::ifstream &file);
void create_return_data(oh_returndata *returndata, PE32PlusOptionalHeader *optional_header, PE32PlusWindowsOptional *optional_windows_header);
