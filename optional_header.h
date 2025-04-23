#ifndef OPTIONAL_HEADER_H
#define OPTIONAL_HEADER_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <vector>

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
    uint16_t subsystem;
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
    uint16_t subsystem;
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
    char name[8];
    uint32_t virtualsize;
    uint32_t virtualaddress;
    uint32_t sizeofrawdata;
    uint32_t pointertorawdata;
    uint32_t pointertorelocations;
    uint32_t pointertolinenumbers;
    uint16_t numberofrelocations;
    uint16_t numberoflinenumbers;
    uint32_t chars;
} HeaderSectionTables;

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
} oh_returndata;

typedef struct _datadirs_returndata {
    std::string exporttable_addr;
    std::string exporttable_size;
    std::string importtable_addr;
    std::string importtable_size;
    std::string resourcetable_addr;
    std::string resourcetable_size;
    std::string exceptiontable_addr;
    std::string exceptiontable_size;
    std::string certificatetable_addr;
    std::string certificatetable_size;
    std::string basereloctable_addr;
    std::string basereloctable_size;
    std::string debug_addr;
    std::string debug_size;
    std::string arch_addr;
    std::string arch_size;
    std::string globalptr_addr;
    std::string globalptr_size;
    std::string tlstable_addr;
    std::string tlstable_size;
    std::string loadconftable_addr;
    std::string loadconftable_size;
    std::string boundimport_addr;
    std::string boundimport_size;
    std::string iat_addr;
    std::string iat_size;
    std::string delayimport_addr;
    std::string delayimport_size;
    std::string clr_addr;
    std::string clr_size;
    std::string reserved_addr;
    std::string reserved_size;
} datadirs_returndata;

typedef struct _st_returndata {
    std::string name;
    std::string virtualsize;
    std::string virtualaddress;
    std::string sizeofrawdata;
    std::string pointertorawdata;
    std::string pointertorelocations;
    std::string pointertolinenumbers;
    std::string numberofrelocations;
    std::string numberoflinenumbers;
    std::string chars;
} st_returndata;

typedef std::vector<st_returndata> st_returndata_vector;

oh_returndata get_optional_header(std::ifstream &file);
void create_return_data(oh_returndata *returndata, PE32PlusOptionalHeader *optional_header, PE32PlusWindowsOptional *optional_windows_header);
void create_datadirs_return_data(datadirs_returndata *dd_returndata, ListOfDataDirs *datadirs);
datadirs_returndata get_data_dirs(std::ifstream &file);
void get_section_tables(uint64_t numberofsections, std::ifstream &file, st_returndata_vector *returndata);
void create_st_return_data(uint64_t numberofsections, st_returndata_vector *returndata, HeaderSectionTables *sectiontables);
void char_array_to_string(std::string *str, char *copy, uint64_t size);

#endif // OPTIONAL_HEADER_H
