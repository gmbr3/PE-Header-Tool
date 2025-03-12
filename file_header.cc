#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>

typedef struct _fileheader {
    uint16_t machine;
    uint8_t numberofsections[2];
    uint8_t timedatestamp[4];
    uint8_t pointertosymboltable[4];
    uint8_t numberofsymbols[4];
    uint8_t sizeofoptional[2];
    uint8_t chars[2];
} FileHeader;

typedef struct _fh_returndata {
    std::string machine;
    std::string numberofsections[2];
    std::string timedatestamp;
    std::string pointertosymboltable;
    std::string numberofsymbols;
    std::string sizeofoptional;
    std::string chars;
} fh_returndata;

/* Pre defs */
void check_machine(uint16_t machine, fh_returndata *returndata);
void get_optional_header(std::ifstream &file);

void get_file_header(std::ifstream &file) {
    fh_returndata returndata;
    FileHeader current_fh[1];
    file.read(reinterpret_cast<char*>(&current_fh), sizeof(current_fh));
    std::cout << current_fh->machine << std::endl;
    check_machine(current_fh->machine, &returndata);
    get_optional_header(file);

}

void check_machine(uint16_t machine, fh_returndata *returndata) {
    if (machine == 0x8664) { returndata->machine = "X86_64"; }
    if (machine == 0x1c2)  { returndata->machine = "ARM Thumb";}
    if (machine == 0xaa64) { returndata->machine = "ARM64";}
    if (machine == 0x1c4) { returndata->machine = "ARM Thumb 2";}
    if (machine == 0x14c) { returndata->machine = "X86";}
    std::cout << returndata->machine << std::endl;
}

