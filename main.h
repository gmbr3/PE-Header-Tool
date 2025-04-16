#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>

/* Pre defs */
void init_program(int argc, char *argv[]);
void open_file(std::ifstream& file, std::string filename = "test/t2.efi");
void check_pe32_file(std::ifstream &file, uint64_t *location);
void skip_chars(std::ifstream &file, uint64_t skip);
bool compare_char_to_string(char* a, std::string b);

