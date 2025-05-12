#include "optional_header.h"
#include "convert_value.h"

oh_returndata get_optional_header(std::ifstream &file) {
    oh_returndata returndata;
    PE32PlusOptionalHeader optional_header[1];
    PE32PlusWindowsOptional optional_windows_header[1];
    bool is_pe32plus_file = false;

    uint64_t location = file.tellg();
    file.read(reinterpret_cast<char*>(&optional_header->magic), sizeof(optional_header->magic));
    if (optional_header->magic == 0x20B) {
        is_pe32plus_file = true;
    }
    file.seekg(location);
    if (!is_pe32plus_file) {
        PE32WindowsOptional pe32_optional[1];
        file.read(reinterpret_cast<char*>(&optional_header), sizeof(optional_header));
        file.read(reinterpret_cast<char*>(&pe32_optional), sizeof(pe32_optional));
        pe32_to_pe32plus_optional(optional_windows_header, pe32_optional);
    }
    if (is_pe32plus_file) {
        /* No base of data in PE32+ */
        file.read(reinterpret_cast<char*>(&optional_header), sizeof(optional_header)-sizeof(optional_header->baseofdata));
        file.read(reinterpret_cast<char*>(&optional_windows_header), sizeof(optional_windows_header));
    }
    create_return_data(&returndata, optional_header, optional_windows_header);
    convert_dllchars(optional_windows_header->dllchars, &returndata);
    convert_subsystem(optional_windows_header->subsystem, &returndata);
    convert_magic(optional_header->magic, &returndata);
    return returndata;
}

/* Make PE32 fields the length of PE32+ fields */
void pe32_to_pe32plus_optional(PE32PlusWindowsOptional *pe32plus, PE32WindowsOptional *pe32) {
    pe32plus->imagebase = pe32->imagebase;
    pe32plus->sectionalignment = pe32->sectionalignment;
    pe32plus->filealignment = pe32->filealignment;
    pe32plus->majoroperatingsystemversion = pe32->majoroperatingsystemversion;
    pe32plus->minoroperatingsystemversion = pe32->minoroperatingsystemversion;
    pe32plus->majorimageversion = pe32->majorimageversion;
    pe32plus->minorimageversion = pe32->minorimageversion;
    pe32plus->majorsubsystemversion = pe32->majorsubsystemversion;
    pe32plus->minorsubsystemversion = pe32->minorsubsystemversion;
    pe32plus->win32versionvalue = pe32->win32versionvalue;
    pe32plus->sizeofimage = pe32->sizeofimage;
    pe32plus->sizeofheaders = pe32->sizeofheaders;
    pe32plus->checksum = pe32->checksum;
    pe32plus->subsystem = pe32->subsystem;
    pe32plus->sizeofstackreserve = pe32->sizeofstackreserve;
    pe32plus->sizeofstackcommit = pe32->sizeofstackcommit;
    pe32plus->sizeofheapreserve = pe32->sizeofheapreserve;
    pe32plus->sizeofheapcommit = pe32->sizeofheapcommit;
    pe32plus->loaderflags = pe32->loaderflags;
    pe32plus->numberofrva = pe32->numberofrva;
    return;
}

datadirs_returndata get_data_dirs(std::ifstream &file) {
    datadirs_returndata dd_returndata;
    ListOfDataDirs datadirs[1];
    file.read(reinterpret_cast<char*>(&datadirs), sizeof(datadirs));
    create_datadirs_return_data(&dd_returndata, datadirs);
    return dd_returndata;
}

void get_section_tables(uint64_t numberofsections, std::ifstream &file, st_returndata_vector *returndata) {
    header_section_tables_vector sectiontables;
    for (uint64_t i = 0; i < numberofsections; i++)  {
        HeaderSectionTable temp[1] = {};
        file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
        sectiontables.push_back(temp[0]);
    }
    create_st_return_data(numberofsections, returndata, sectiontables);
    return;
}

void create_return_data(oh_returndata *returndata, PE32PlusOptionalHeader *optional_header, PE32PlusWindowsOptional *optional_windows_header) {
    /* Write filedata to output structure */
    returndata->majorlinkerversion = std::to_string(optional_header->majorlinkerversion);
    returndata->minorlinkerversion = std::to_string(optional_header->minorlinkerversion);
    returndata->sizeofcode = std::to_string(optional_header->sizeofcode);
    returndata->sizeofinitdata = std::to_string(optional_header->sizeofinitdata);
    returndata->sizeofunitdata = std::to_string(optional_header->sizeofunitdata);
    returndata->addressofentrypoint = std::to_string(optional_header->addressofentrypoint);
    returndata->baseofcode = std::to_string(optional_header->baseofcode);
    returndata->baseofdata = std::to_string(optional_header->baseofdata);
    returndata->imagebase = std::to_string(optional_windows_header->imagebase);
    returndata->sectionalignment = std::to_string(optional_windows_header->sectionalignment);
    returndata->filealignment = std::to_string(optional_windows_header->filealignment);
    returndata->majoroperatingsystemversion = std::to_string(optional_windows_header->majoroperatingsystemversion);
    returndata->minoroperatingsystemversion = std::to_string(optional_windows_header->minoroperatingsystemversion);
    returndata->majorimageversion = std::to_string(optional_windows_header->majorimageversion);
    returndata->minorimageversion = std::to_string(optional_windows_header->minorimageversion);
    returndata->majorsubsystemversion = std::to_string(optional_windows_header->majorsubsystemversion);
    returndata->minorsubsystemversion = std::to_string(optional_windows_header->minorsubsystemversion);
    returndata->win32versionvalue = std::to_string(optional_windows_header->win32versionvalue);
    returndata->sizeofimage = std::to_string(optional_windows_header->sizeofimage);
    returndata->sizeofheaders = std::to_string(optional_windows_header->sizeofheaders);
    returndata->checksum = std::to_string(optional_windows_header->checksum);
    returndata->sizeofstackreserve = std::to_string(optional_windows_header->sizeofstackreserve);
    returndata->sizeofstackcommit = std::to_string(optional_windows_header->sizeofstackcommit);
    returndata->sizeofheapreserve = std::to_string(optional_windows_header->sizeofheapreserve);
    returndata->sizeofheapcommit = std::to_string(optional_windows_header->sizeofheapcommit);
    returndata->loaderflags = std::to_string(optional_windows_header->loaderflags);
    returndata->numberofrva = std::to_string(optional_windows_header->numberofrva);
    /* AWAITING RE-DO FOR DATA DIRECTORIES MULTIPLE POINTS */
}

void create_datadirs_return_data(datadirs_returndata *dd_returndata, ListOfDataDirs *datadirs) {
    dd_returndata->exporttable_addr = std::to_string(datadirs->exporttable.virtualaddress);
    dd_returndata->exporttable_size = std::to_string(datadirs->exporttable.size);
    dd_returndata->importtable_addr = std::to_string(datadirs->importtable.virtualaddress);
    dd_returndata->importtable_size = std::to_string(datadirs->importtable.size);
    dd_returndata->resourcetable_addr = std::to_string(datadirs->resourcetable.virtualaddress);
    dd_returndata->resourcetable_size = std::to_string(datadirs->resourcetable.size);
    dd_returndata->exceptiontable_addr = std::to_string(datadirs->exceptiontable.virtualaddress);
    dd_returndata->exceptiontable_size = std::to_string(datadirs->exceptiontable.size);
    dd_returndata->certificatetable_addr = std::to_string(datadirs->certificatetable.virtualaddress);
    dd_returndata->certificatetable_size = std::to_string(datadirs->certificatetable.size);
    dd_returndata->basereloctable_addr = std::to_string(datadirs->basereloctable.virtualaddress);
    dd_returndata->basereloctable_size = std::to_string(datadirs->basereloctable.size);
    dd_returndata->debug_addr = std::to_string(datadirs->debug.virtualaddress);
    dd_returndata->debug_size = std::to_string(datadirs->debug.size);
    dd_returndata->arch_addr = std::to_string(datadirs->arch.virtualaddress);
    dd_returndata->arch_size = std::to_string(datadirs->arch.size);
    dd_returndata->globalptr_addr = std::to_string(datadirs->globalptr.virtualaddress);
    dd_returndata->globalptr_size = std::to_string(datadirs->globalptr.size);
    dd_returndata->tlstable_addr = std::to_string(datadirs->tlstable.virtualaddress);
    dd_returndata->tlstable_size = std::to_string(datadirs->tlstable.size);
    dd_returndata->loadconftable_addr = std::to_string(datadirs->loadconftable.virtualaddress);
    dd_returndata->loadconftable_size = std::to_string(datadirs->loadconftable.size);
    dd_returndata->boundimport_addr = std::to_string(datadirs->boundimport.virtualaddress);
    dd_returndata->boundimport_size = std::to_string(datadirs->boundimport.size);
    dd_returndata->iat_addr = std::to_string(datadirs->iat.virtualaddress);
    dd_returndata->iat_size = std::to_string(datadirs->iat.size);
    dd_returndata->delayimport_addr = std::to_string(datadirs->delayimport.virtualaddress);
    dd_returndata->delayimport_size = std::to_string(datadirs->delayimport.size);
    dd_returndata->clr_addr = std::to_string(datadirs->clr.virtualaddress);
    dd_returndata->clr_size = std::to_string(datadirs->clr.size);
    dd_returndata->reserved_addr = std::to_string(datadirs->reserved.virtualaddress);
    dd_returndata->reserved_size = std::to_string(datadirs->reserved.size);
    
}

/* Informed by https://en.cppreference.com/w/cpp/string/basic_string/push_back */
void char_array_to_string(std::string *str, char *copy, uint64_t size) {
    for (uint64_t i = 0; i < size; i++) {
        if (copy[i] == 0) {
            break;
        }
        str->push_back(copy[i]);
    }
    std::cout << "l is " << *str << std::endl;
}
 /* Informed by https://www.geeksforgeeks.org/cpp-vector-of-structs/ */
void create_st_return_data(uint64_t numberofsections, st_returndata_vector *returndata, header_section_tables_vector sectiontables) {
    st_returndata st_data;
    std::string temp;
    for (uint64_t i = 0; i < numberofsections; i++) {
        char_array_to_string(&temp, sectiontables[i].name, sizeof(sectiontables[i].name));
        st_data.name = temp;
        temp.clear();
        st_data.virtualsize = std::to_string(sectiontables[i].virtualsize);
        st_data.virtualaddress = std::to_string(sectiontables[i].virtualaddress);
        st_data.sizeofrawdata = std::to_string(sectiontables[i].sizeofrawdata);
        st_data.pointertorawdata = std::to_string(sectiontables[i].pointertorawdata);
        st_data.pointertorelocations = std::to_string(sectiontables[i].pointertorelocations);
        st_data.pointertolinenumbers = std::to_string(sectiontables[i].pointertolinenumbers);
        st_data.numberofrelocations = std::to_string(sectiontables[i].numberofrelocations);
        st_data.numberoflinenumbers = std::to_string(sectiontables[i].numberoflinenumbers);
        st_data.chars = convert_sectionflags(sectiontables[i].chars);
        std::cout << "chars is " << st_data.chars << std::endl;
        returndata->push_back(st_data);
    }
}
