#ifndef CONVERT_VALUE_H
#define CONVERT_VALUE_H

#include "file_header.h"
#include "optional_header.h"

#include <ctime>


/* Pre defs */
void check_machine(uint16_t machine, fh_returndata *returndata);
void deprecated_flag(std::string df);
void reserved_flag(std::string rf);
std::string deprecated_flag_in_filechars(std::string df);
std::string reserved_flag_in_filechars(std::string rf);
std::string string_newline(std::string str);
void convert_filechars(uint16_t chars, fh_returndata *returndata);
std::string reserved_flag_in_dllchars(std::string rf);
void convert_dllchars(uint16_t dllchars, oh_returndata *returndata);
std::string reserved_flag_in_sectionflags(std::string rf);
std::string convert_sectionflags(uint32_t flags);
void convert_subsystem(uint16_t subsystem, oh_returndata *returndata);
void convert_magic(uint16_t magic, oh_returndata *returndata);
void convert_time(uint32_t time, fh_returndata *returndata);

#endif // CONVERT_VALUE_H

