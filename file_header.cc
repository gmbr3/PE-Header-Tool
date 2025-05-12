#include "file_header.h"
#include "convert_value.h"

fh_returndata get_file_header(std::ifstream &file) {
    fh_returndata returndata;
    FileHeader current_fh[1];
    file.read(reinterpret_cast<char*>(&current_fh), sizeof(current_fh));
    std::cout << current_fh->machine << std::endl;
    check_machine(current_fh->machine, &returndata);
    convert_filechars(current_fh->chars, &returndata);
    /* get_optional_header(file); */
    do_return_data(current_fh, &returndata);
    return returndata;
}

void do_return_data(FileHeader *current_fh, fh_returndata *returndata) {
    /* Write filedata to output structure */
    /* No machine since that is done in check_machine() */
    returndata->numberofsections = std::to_string(current_fh->numberofsections);
    returndata->timedatestamp = std::to_string(current_fh->timedatestamp);
    returndata->pointertosymboltable = std::to_string(current_fh->pointertosymboltable);
    returndata->numberofsymbols = std::to_string(current_fh->numberofsymbols);
    returndata->sizeofoptional = std::to_string(current_fh->sizeofoptional);
}
