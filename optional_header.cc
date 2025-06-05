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
	convert_to_hex(optional_header->sizeofcode, &(returndata->sizeofcode));
	convert_to_hex(optional_header->sizeofinitdata, &(returndata->sizeofinitdata));
	convert_to_hex(optional_header->sizeofunitdata, &(returndata->sizeofunitdata));
	convert_to_hex(optional_header->addressofentrypoint, &(returndata->addressofentrypoint));   
	convert_to_hex(optional_header->baseofcode, &(returndata->baseofcode));
	convert_to_hex(optional_header->baseofdata, &(returndata->baseofdata));
	convert_to_hex(optional_windows_header->imagebase, &(returndata->imagebase));
	convert_to_hex(optional_windows_header->sectionalignment, &(returndata->sectionalignment));
	convert_to_hex(optional_windows_header->filealignment, &(returndata->filealignment));
	returndata->majoroperatingsystemversion = std::to_string(optional_windows_header->majoroperatingsystemversion);
	returndata->minoroperatingsystemversion = std::to_string(optional_windows_header->minoroperatingsystemversion);
	returndata->majorimageversion = std::to_string(optional_windows_header->majorimageversion);
	returndata->minorimageversion = std::to_string(optional_windows_header->minorimageversion);
	returndata->majorsubsystemversion = std::to_string(optional_windows_header->majorsubsystemversion);
	returndata->minorsubsystemversion = std::to_string(optional_windows_header->minorsubsystemversion);
	returndata->win32versionvalue = std::to_string(optional_windows_header->win32versionvalue);
	convert_to_hex(optional_windows_header->sizeofimage, &(returndata->sizeofimage));
	convert_to_hex(optional_windows_header->sizeofheaders, &(returndata->sizeofheaders));
	convert_to_hex(optional_windows_header->checksum, &(returndata->checksum));
	convert_to_hex(optional_windows_header->sizeofstackreserve, &(returndata->sizeofstackreserve));
	convert_to_hex(optional_windows_header->sizeofstackcommit, &(returndata->sizeofstackcommit));
	convert_to_hex(optional_windows_header->sizeofheapreserve, &(returndata->sizeofheapreserve));
	convert_to_hex(optional_windows_header->sizeofheapcommit, &(returndata->sizeofheapcommit));
	convert_to_hex(optional_windows_header->loaderflags, &(returndata->loaderflags));
	convert_to_hex(optional_windows_header->numberofrva, &(returndata->numberofrva));
    /* AWAITING RE-DO FOR DATA DIRECTORIES MULTIPLE POINTS */
}

void create_datadirs_return_data(datadirs_returndata *dd_returndata, ListOfDataDirs *datadirs) {
    convert_to_hex(datadirs->exporttable.virtualaddress, &(dd_returndata->exporttable_addr));
	convert_to_hex(datadirs->exporttable.size, &(dd_returndata->exporttable_size));
	convert_to_hex(datadirs->importtable.virtualaddress, &(dd_returndata->importtable_addr));
	convert_to_hex(datadirs->importtable.size, &(dd_returndata->importtable_size));
	convert_to_hex(datadirs->resourcetable.virtualaddress, &(dd_returndata->resourcetable_addr));
	convert_to_hex(datadirs->resourcetable.size, &(dd_returndata->resourcetable_size));
	convert_to_hex(datadirs->exceptiontable.virtualaddress, &(dd_returndata->exceptiontable_addr));
	convert_to_hex(datadirs->exceptiontable.size, &(dd_returndata->exceptiontable_size));
	convert_to_hex(datadirs->certificatetable.virtualaddress, &(dd_returndata->certificatetable_addr));
	convert_to_hex(datadirs->certificatetable.size, &(dd_returndata->certificatetable_size));
	convert_to_hex(datadirs->basereloctable.virtualaddress, &(dd_returndata->basereloctable_addr));
	convert_to_hex(datadirs->basereloctable.size, &(dd_returndata->basereloctable_size));
	convert_to_hex(datadirs->debug.virtualaddress, &(dd_returndata->debug_addr));
	convert_to_hex(datadirs->debug.size, &(dd_returndata->debug_size));
	convert_to_hex(datadirs->arch.virtualaddress, &(dd_returndata->arch_addr));
	convert_to_hex(datadirs->arch.size, &(dd_returndata->arch_size));
	convert_to_hex(datadirs->globalptr.virtualaddress, &(dd_returndata->globalptr_addr));
	convert_to_hex(datadirs->globalptr.size, &(dd_returndata->globalptr_size));
	convert_to_hex(datadirs->tlstable.virtualaddress, &(dd_returndata->tlstable_addr));
	convert_to_hex(datadirs->tlstable.size, &(dd_returndata->tlstable_size));
	convert_to_hex(datadirs->loadconftable.virtualaddress, &(dd_returndata->loadconftable_addr));
    convert_to_hex(datadirs->loadconftable.size, &(dd_returndata->loadconftable_size));
	convert_to_hex(datadirs->boundimport.virtualaddress, &(dd_returndata->boundimport_addr));
	convert_to_hex(datadirs->boundimport.size, &(dd_returndata->boundimport_size));
	convert_to_hex(datadirs->iat.virtualaddress, &(dd_returndata->iat_addr));
	convert_to_hex(datadirs->iat.size, &(dd_returndata->iat_size));
	convert_to_hex(datadirs->delayimport.virtualaddress, &(dd_returndata->delayimport_addr));
	convert_to_hex(datadirs->delayimport.size, &(dd_returndata->delayimport_size));
	convert_to_hex(datadirs->clr.virtualaddress, &(dd_returndata->clr_addr));
	convert_to_hex(datadirs->clr.size, &(dd_returndata->clr_size));
	convert_to_hex(datadirs->reserved.virtualaddress, &(dd_returndata->reserved_addr));
	convert_to_hex(datadirs->reserved.size, &(dd_returndata->reserved_size));
}

 /* Informed by https://www.geeksforgeeks.org/cpp-vector-of-structs/ */
void create_st_return_data(uint64_t numberofsections, st_returndata_vector *returndata, header_section_tables_vector sectiontables) {
    st_returndata st_data;
    std::string temp;
    for (uint64_t i = 0; i < numberofsections; i++) {
        char_array_to_string(&temp, sectiontables[i].name, sizeof(sectiontables[i].name));
        st_data.name = temp;
        temp.clear();
        convert_to_hex(sectiontables[i].virtualsize, &temp);
		st_data.virtualsize = temp;
		temp.clear();
		convert_to_hex(sectiontables[i].virtualaddress, &temp);
		st_data.virtualaddress = temp;
		temp.clear();
		convert_to_hex(sectiontables[i].sizeofrawdata, &temp);
		st_data.sizeofrawdata = temp;
		temp.clear();
		convert_to_hex(sectiontables[i].pointertorawdata, &temp);
		st_data.pointertorawdata = temp;
		temp.clear();
		convert_to_hex(sectiontables[i].pointertorelocations, &temp);
		st_data.pointertorelocations = temp;
		temp.clear();
		convert_to_hex(sectiontables[i].pointertolinenumbers, &temp);
		st_data.pointertolinenumbers = temp;
		temp.clear();
		convert_to_hex(sectiontables[i].numberofrelocations, &temp);
		st_data.numberofrelocations = temp;
		temp.clear();
		convert_to_hex(sectiontables[i].numberoflinenumbers, &temp);
		st_data.numberoflinenumbers = temp;
		temp.clear();

        st_data.chars = convert_sectionflags(sectiontables[i].chars);
        std::cout << "chars is " << st_data.chars << std::endl;
        returndata->push_back(st_data);
    }
}
