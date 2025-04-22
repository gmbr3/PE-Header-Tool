#include "optional_header.h"

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
        file.read(reinterpret_cast<char*>(&optional_header), sizeof(optional_header));
    }
    if (is_pe32plus_file) {
        file.read(reinterpret_cast<char*>(&optional_header), sizeof(optional_header)-sizeof(optional_header->baseofdata));
    }
    file.read(reinterpret_cast<char*>(&optional_windows_header), sizeof(optional_windows_header));
    create_return_data(&returndata, optional_header, optional_windows_header);
    return returndata;
}

void create_return_data(oh_returndata *returndata, PE32PlusOptionalHeader *optional_header, PE32PlusWindowsOptional *optional_windows_header) {
    /* Write filedata to output structure */
    returndata->magic = std::to_string(optional_header->magic);
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
    returndata->subsystem = std::to_string(optional_windows_header->subsystem);
    returndata->dllchars = std::to_string(optional_windows_header->dllchars);
    returndata->sizeofstackreserve = std::to_string(optional_windows_header->sizeofstackreserve);
    returndata->sizeofstackcommit = std::to_string(optional_windows_header->sizeofstackcommit);
    returndata->sizeofheapreserve = std::to_string(optional_windows_header->sizeofheapreserve);
    returndata->sizeofheapcommit = std::to_string(optional_windows_header->sizeofheapcommit);
    returndata->loaderflags = std::to_string(optional_windows_header->loaderflags);
    returndata->numberofrva = std::to_string(optional_windows_header->numberofrva);
    /* AWAITING RE-DO FOR DATA DIRECTORIES MULTIPLE POINTS */
}
