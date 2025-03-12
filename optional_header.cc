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
    uint32_t baseofdata;
} PE32PlusOptionalHeader;

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

typedef struct _oh_returndata {
    std::string magic[2];
    std::string majorlinkerversion[1];
    std::string minorlinkerversion[1];
    std::string sizeofcode[4];
    std::string sizeofinitdata[4];
    std::string sizeofunitdata[4];
    std::string addressofentrypoint[4];
    std::string baseofcode[4];
    std::string baseofdata[4];
    std::string imagebase[8];
    std::string sectionalignment[4];
    std::string filealignment[4];
    std::string majoroperatingsystemversion[2];
    std::string minoroperatingsystemversion[2];
    std::string majorimageversion[2];
    std::string minorimageversion[2];
    std::string majorsubsystemversion[2];
    std::string minorsubsystemversion[2];
    std::string win32versionvalue[4];
    std::string sizeofimage[4];
    std::string sizeofheaders[4];
    std::string checksum[4];
    std::string subsystem[4];
    std::string dllchars[2];
    std::string sizeofstackreserve[8];
    std::string sizeofstackcommit[8];
    std::string sizeofheapreserve[8];
    std::string sizeofheapcommit[8];
    std::string loaderflags[4];
    std::string numberofrva[4];
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

void get_optional_header(std::ifstream &file) {
    oh_returndata returndata;
    PE32PlusOptionalHeader optional_header[1];
    bool is_pe32plus_file = false;
    uint64_t location = file.tellg();
    file.read(reinterpret_cast<char*>(&optional_header->magic), sizeof(optional_header->magic));
    if (optional_header->magic == 0x20B) {
        is_pe32plus_file = true;
    }
    file.seekg(location);
    if (!is_pe32plus_file) {
        file.read(reinterpret_cast<char*>(&optional_header), sizeof(optional_header));
    }
    if (is_pe32plus_file) {
        file.read(reinterpret_cast<char*>(&optional_header), sizeof(optional_header)-sizeof(optional_header->baseofdata));
    }
    
}
