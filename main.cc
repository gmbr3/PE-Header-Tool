#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>

/* Pre defs */
void init_program(void);
void open_file(void);
void check_pe32_file(std::ifstream &file);
void skip_chars(std::ifstream &file, uint64_t skip);
bool compare_binary(char* a, std::string b);

int main(void) {
    init_program();
    return 0;
}

void init_program(void) {
    std::cout << "hello!" << std::endl;
    open_file();
    return;
}

void open_file(void) {
    std::ifstream f("test/t2.efi", std::ios::binary);

    if (!f.is_open()) {
        std::cout << "Error opening the file!" << std::endl;
        return;
    }
    check_pe32_file(f);
    f.close();
    return;
}

void skip_chars(std::ifstream &file, uint64_t skip) {
    uint64_t pos = file.tellg();
    std::cout << pos << std::endl;
    uint64_t new_pos = pos + skip;
    std::cout << new_pos << std::endl;
    file.seekg(new_pos);
    return;
}

bool compare_binary(char* a, std::string b) {
    uint64_t size = b.size();
    for (uint64_t i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

void check_pe32_file(std::ifstream &file) {
    char signature_offset[2];
    uint32_t here[1];
    char peh[2];

    file.read(signature_offset, sizeof(signature_offset));
    if (compare_binary(signature_offset, "MZ")) {
        std::cout << "Got MZ!" << std::endl;
    }
    skip_chars(file, 58);
    file.read(reinterpret_cast<char*>(&here), sizeof(here));
    std::cout << "This is what is here!" << std::endl;
    std::cout << *here << std::endl;
    file.seekg(*here);
    file.read(reinterpret_cast<char*>(&peh), sizeof(peh));
    if (compare_binary(peh, "PE")) {
        std::cout << "Got PE!" << std::endl;
    }

    return;
}
