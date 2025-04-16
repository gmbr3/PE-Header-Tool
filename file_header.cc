#include "file_header.h"

fh_returndata get_file_header(std::ifstream &file) {
    fh_returndata returndata;
    FileHeader current_fh[1];
    std::cout << current_fh->machine << std::endl;
    file.read(reinterpret_cast<char*>(&current_fh), sizeof(current_fh));
    std::cout << current_fh->machine << std::endl;
    check_machine(current_fh->machine, &returndata);
    /* get_optional_header(file); */
    do_return_data(current_fh, &returndata);
    return returndata;
}

void check_machine(uint16_t machine, fh_returndata *returndata) {
    if (machine == 0x8664) { returndata->machine = "X86_64"; }
    if (machine == 0x1c2)  { returndata->machine = "ARM Thumb";}
    if (machine == 0xaa64) { returndata->machine = "ARM64";}
    if (machine == 0x1c4) { returndata->machine = "ARM Thumb 2";}
    if (machine == 0x14c) { returndata->machine = "X86";}
    std::cout << returndata->machine << std::endl;
}

void do_return_data(FileHeader *current_fh, fh_returndata *returndata) {
    /* Write filedata to output structure */
    /* No machine since that is done in check_machine() */
    returndata->numberofsections = std::to_string(current_fh->numberofsections);
    returndata->timedatestamp = std::to_string(current_fh->timedatestamp);
    returndata->pointertosymboltable = std::to_string(current_fh->pointertosymboltable);
    returndata->numberofsymbols = std::to_string(current_fh->numberofsymbols);
    returndata->sizeofoptional = std::to_string(current_fh->sizeofoptional);
    returndata->chars = std::to_string(current_fh->chars);
}
