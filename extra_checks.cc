#include "extra_checks.h"

#include "ui/information.h"

extern Information *potential_issues;

/* Some checks are found in convert_value.cc */

void check_valid_section_alignment(uint32_t sectionalignment, uint32_t filealignment) {
    if (sectionalignment < filealignment) {
        QMetaObject::invokeMethod(potential_issues, "NewError", Qt::QueuedConnection, QString("Section Alignment is less than File Alignment"));

    }
}

void check_valid_file_alignment(uint32_t filealignment) {
    if (filealignment < 512 || filealignment > 65536) {
        QMetaObject::invokeMethod(potential_issues, "NewError", Qt::QueuedConnection, QString("File Alignment is not between 512 and 65536"));
    }
}

void check_code_section_non_writeable(uint32_t characteristics) {
    if (characteristics & 0x00000020) {
        if (characteristics & 0x80000000) {
            QMetaObject::invokeMethod(potential_issues, "NewError", Qt::QueuedConnection, QString("Code section is writeable"));
        }
    }
}

void check_data_section_non_executable(uint32_t characteristics) {
    if (characteristics & 0x00000040 || characteristics & 0x00000080) {
        if (characteristics & 0x20000000) {
            QMetaObject::invokeMethod(potential_issues, "NewError", Qt::QueuedConnection, QString("Data section is executable"));
        }
    }
}

