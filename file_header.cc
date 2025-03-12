#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>


typedef struct _fileheader {
    uint8_t machine[2];
    uint8_t numberofsections[2];
    uint8_t timedatestamp[4];
    uint8_t pointertosymboltable[4];
    uint8_t numberofsymbols[4];
    uint8_t sizeofoptional[2];
    uint8_t chars[2];
} FileHeader;

void get_file_header(std::ifstream &file) {

    

}
