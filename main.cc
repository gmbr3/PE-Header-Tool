/* Qt */
#include "ui/mainwindow.h"
#include "ui/fileselection.h"
#include <QApplication>

#include "main.h"

#include <Qt>
#include <QString>
#include <QMetaObject>

#include "ui/information.h"

extern Information *potential_issues;

int main(int argc, char *argv[]) {
    init_program(argc, argv);
    return 0;
}

void init_program(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    std::cout << "hello!" << std::endl;
    w.show();
    a.exec();
    return;
}

void open_file(std::ifstream& file, std::string filename) {
    file = std::ifstream(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Filename: " << filename << std::endl;
        std::cout << "Error opening the file!" << std::endl;
    }
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

void check_pe32_file(std::ifstream &file, uint64_t *location) {
    char signature_offset[2];
    uint32_t here[1];
    char peh[4];

    file.read(signature_offset, sizeof(signature_offset));
    if (compare_char_to_string(signature_offset, "MZ")) {
        std::cout << "Got MZ!" << std::endl;
        QMetaObject::invokeMethod(potential_issues, "NewInformation", Qt::QueuedConnection,
                         QString("Got MZ!"));
    }
    skip_chars(file, 58);
    file.read(reinterpret_cast<char*>(&here), sizeof(here));
    std::cout << "This is what is here!" << std::endl;
    std::cout << *here << std::endl;
    file.seekg(*here);
    file.read(reinterpret_cast<char*>(&peh), sizeof(peh));
    if (compare_char_to_string(peh, "PE")) {
        std::cout << "Got PE!" << std::endl;
        QMetaObject::invokeMethod(potential_issues, "NewInformation", Qt::QueuedConnection,
                         QString("Got PE!"));
    }
    *location = file.tellg();
    
    return;
}
