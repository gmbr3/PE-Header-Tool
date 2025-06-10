#include "extra_checks.h"

#include "ui/information.h"

extern Information *potential_issues;
extern bool uefi_mode;

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

void check_valid_uefi_subsystem(uint16_t subsystem) {
    if (uefi_mode) {
        if (subsystem != 0x000A && subsystem != 0x000B && subsystem != 0x000C) {
            QMetaObject::invokeMethod(potential_issues, "NewError", Qt::QueuedConnection, QString("Subsystem is not UEFI"));
        }
    }
}

void check_valid_uefi_machine_type(uint16_t machine) {
    if (uefi_mode) {
        /* Should be 0X1C2 */
        if (machine == 0x1C0 || machine == 0x1C4) {
            QMetaObject::invokeMethod(potential_issues, "NewError", Qt::QueuedConnection, QString("Incorrect ARM machine type for UEFI"));
        }
    }
}   

void check_datadirs_length(uint32_t numberofrva) {
    if (numberofrva > 16) {
        QMetaObject::invokeMethod(potential_issues, "NewError", Qt::QueuedConnection, QString("Number of Data Directories is greater than 16"));
    }
    else if (numberofrva < 16) {
        QMetaObject::invokeMethod(potential_issues, "NewWarning", Qt::QueuedConnection, QString("Number of Data Directories is less than 16"));
    }
}
