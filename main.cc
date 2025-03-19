#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>

/* Qt */
#include "ui/mainwindow.h"
#include <QApplication>


/* Pre defs */
void init_program(int argc, char *argv[]);
void open_file(void);
void check_pe32_file(std::ifstream &file);
void skip_chars(std::ifstream &file, uint64_t skip);
bool compare_char_to_string(char* a, std::string b);
void get_file_header(std::ifstream &file);

int main(int argc, char *argv[]) {
    init_program(argc, argv);
    return 0;
}

void init_program(int argc, char *argv[]) {
    std::cout << "hello!" << std::endl;
    open_file();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();
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

bool compare_char_to_string(char* a, std::string b) {
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
    char peh[4];

    file.read(signature_offset, sizeof(signature_offset));
    if (compare_char_to_string(signature_offset, "MZ")) {
        std::cout << "Got MZ!" << std::endl;
    }
    skip_chars(file, 58);
    file.read(reinterpret_cast<char*>(&here), sizeof(here));
    std::cout << "This is what is here!" << std::endl;
    std::cout << *here << std::endl;
    file.seekg(*here);
    file.read(reinterpret_cast<char*>(&peh), sizeof(peh));
    if (compare_char_to_string(peh, "PE")) {
        std::cout << "Got PE!" << std::endl;
    }

    get_file_header(file);
    return;
}
