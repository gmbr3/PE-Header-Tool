#ifndef FILE_HEADER_H
#define FILE_HEADER_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>

typedef struct _fileheader {
    uint16_t machine;
    uint16_t numberofsections;
    uint32_t timedatestamp;
    uint32_t pointertosymboltable;
    uint32_t numberofsymbols;
    uint16_t sizeofoptional;
    uint16_t chars;
} FileHeader;

typedef struct _fh_returndata {
    std::string machine;
    std::string numberofsections;
    std::string timedatestamp;
    std::string pointertosymboltable;
    std::string numberofsymbols;
    std::string sizeofoptional;
    std::string chars;
} fh_returndata;

/* Pre defs */
fh_returndata get_file_header(std::ifstream &file);
void check_machine(uint16_t machine, fh_returndata *returndata);
void do_return_data(FileHeader *current_fh, fh_returndata *returndata);

#endif // FILE_HEADER_H

