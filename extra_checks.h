#ifndef EXTRA_CHECKS_H
#define EXTRA_CHECKS_H

#include <cstdint>
#include <Qt>
#include <QString>
#include <QMetaObject>

void check_valid_section_alignment(uint32_t sectionalignment, uint32_t filealignment);
void check_valid_file_alignment(uint32_t filealignment);
void check_code_section_non_writeable(uint32_t characteristics);
void check_data_section_non_executable(uint32_t characteristics);
void check_valid_uefi_subsystem(uint16_t subsystem);
void check_valid_uefi_machine_type(uint16_t machine);
void check_datadirs_length(uint32_t numberofrva);

#endif // EXTRA_CHECKS_H
