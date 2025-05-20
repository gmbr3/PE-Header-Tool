#include "convert_value.h"

#include "ui/potentialissues.h"

extern PotentialIssues *potential_issues;

/* Informed by https://en.cppreference.com/w/cpp/string/basic_string/push_back */
void char_array_to_string(std::string *str, char *copy, uint64_t size) {
    for (uint64_t i = 0; i < size; i++) {
        if (copy[i] == 0) {
            break;
        }
        str->push_back(copy[i]);
    }
    std::cout << "l is " << *str << std::endl;
}

void check_machine(uint16_t machine, fh_returndata *returndata) {
    if (machine == 0x8664) { returndata->machine = "X86_64"; }
    if (machine == 0x1c2)  { returndata->machine = "ARM Thumb";}
    if (machine == 0xaa64) { returndata->machine = "ARM64";}
    if (machine == 0x1c4) { returndata->machine = "ARM Thumb 2";}
    if (machine == 0x14c) { returndata->machine = "X86";}
    std::cout << returndata->machine << std::endl;
}

void convert_time(uint32_t time, fh_returndata *returndata) {
    std::tm* tm;
    char buf[100];
    std::time_t tp;
    tp = static_cast<std::time_t>(time);
    tm = std::gmtime(&tp);
    std::strftime(buf, sizeof(buf), "%c", tm);
    char_array_to_string(&(returndata->timedatestamp), buf, sizeof(buf));
}


void deprecated_flag(std::string df) {
    QString df_qstring = QString("Deprecated flag: ") + QString::fromStdString(df);
    QMetaObject::invokeMethod(potential_issues, "NewWarning", Qt::QueuedConnection,
        df_qstring);
    return;
}

void reserved_flag(std::string rf) {
    QString rf_qstring = QString("Reserved flag: ") + QString::fromStdString(rf);
    QMetaObject::invokeMethod(potential_issues, "NewWarning", Qt::QueuedConnection,
        rf_qstring);
    return;
}

std::string deprecated_flag_in_filechars(std::string df) {
    std::string fchars_df = df + " in filechars";
    deprecated_flag(fchars_df);
    return df;
}

std::string reserved_flag_in_filechars(std::string rf) {
    std::string fchars_rf = rf + " in filechars";
    reserved_flag(fchars_rf);
    return rf;
}

std::string string_newline(std::string str) {
    std::string newline = "\n";
    str += newline;
    return str;
}

void convert_filechars(uint16_t chars, fh_returndata *returndata) {
    if (chars & 0x0001) { returndata->chars += string_newline("Relocations stripped"); }
    if (chars & 0x0002) { returndata->chars += string_newline("Executable image"); }
    if (chars & 0x0004) { returndata->chars += string_newline(deprecated_flag_in_filechars("Line numbers stripped")); }
    if (chars & 0x0008) { returndata->chars += string_newline(deprecated_flag_in_filechars("Local symbols stripped")); }
    if (chars & 0x0010) { returndata->chars += string_newline(deprecated_flag_in_filechars("Agressively trim working set")); }
    if (chars & 0x0020) { returndata->chars += string_newline("Large address aware"); }
    if (chars & 0x0040) { returndata->chars += string_newline(reserved_flag_in_filechars("Reserved")); }
    if (chars & 0x0080) { returndata->chars += string_newline(deprecated_flag_in_filechars("Little endian")); }
    if (chars & 0x0100) { returndata->chars += string_newline("32bit Machine"); }
    if (chars & 0x0200) { returndata->chars += string_newline("Debug stripped"); }
    if (chars & 0x0400) { returndata->chars += string_newline("Removable swappable"); }
    if (chars & 0x0800) { returndata->chars += string_newline("Network swappable"); }
    if (chars & 0x1000) { returndata->chars += string_newline("System file"); }
    if (chars & 0x2000) { returndata->chars += string_newline("DLL"); }
    if (chars & 0x4000) { returndata->chars += string_newline("Uniprocessor only"); }
    if (chars & 0x8000) { returndata->chars += string_newline(deprecated_flag_in_filechars("Big endian")); }
    if (returndata->chars == "") {
        returndata->chars = "None";
    }
}

std::string reserved_flag_in_dllchars(std::string rf) {
    std::string dllchars_rf = rf + " in dllchars";
    reserved_flag(dllchars_rf);
    return rf;
}

void convert_dllchars(uint16_t dllchars, oh_returndata *returndata) {
    if (dllchars & 0x0001) { returndata->dllchars += string_newline(reserved_flag_in_dllchars("Reserved")); }
    if (dllchars & 0x0002) { returndata->dllchars += string_newline(reserved_flag_in_dllchars("Reserved")); }
    if (dllchars & 0x0004) { returndata->dllchars += string_newline(reserved_flag_in_dllchars("Reserved")); }
    if (dllchars & 0x0008) { returndata->dllchars += string_newline(reserved_flag_in_dllchars("Reserved")); }
    if (dllchars & 0x0020) { returndata->dllchars += string_newline("Supports high entropy address space"); }
    if (dllchars & 0x0040) { returndata->dllchars += string_newline("Dynamic base"); }
    if (dllchars & 0x0080) { returndata->dllchars += string_newline("Code integrity enforced"); }
    if (dllchars & 0x0100) { returndata->dllchars += string_newline("NX compatible"); }
    if (dllchars & 0x0200) { returndata->dllchars += string_newline("Image isolation disabled"); }
    if (dllchars & 0x0400) { returndata->dllchars += string_newline("SEH disabled"); }
    if (dllchars & 0x0800) { returndata->dllchars += string_newline("No bind"); }
    if (dllchars & 0x1000) { returndata->dllchars += string_newline("Execute in AppContainer"); }
    if (dllchars & 0x2000) { returndata->dllchars += string_newline("WDM driver"); }
    if (dllchars & 0x4000) { returndata->dllchars += string_newline("Control Flow Guard"); }
    if (dllchars & 0x8000) { returndata->dllchars += string_newline("Terminal Server aware"); }
    if (returndata->dllchars == "") {
        returndata->dllchars = "None";
    }
}

std::string reserved_flag_in_sectionflags(std::string rf) {
    std::string sectionflags_rf = rf + " in sectionflags";
    reserved_flag(sectionflags_rf);
    return rf;
}

std::string convert_sectionflags(uint32_t flags) {
    std::string chars;
    if (flags & 0x00000001) { chars += string_newline(reserved_flag_in_sectionflags("Reserved")); }
    if (flags & 0x00000002) { chars += string_newline(reserved_flag_in_sectionflags("Reserved")); }
    if (flags & 0x00000004) { chars += string_newline(reserved_flag_in_sectionflags("Reserved")); }
    if (flags & 0x00000008) { chars += string_newline(reserved_flag_in_sectionflags("Don't Pad")); }
    if (flags & 0x00000010) { chars += string_newline(reserved_flag_in_sectionflags("Reserved")); }
    if (flags & 0x00000020) { chars += string_newline("Contains code"); }
    if (flags & 0x00000040) { chars += string_newline("Contains initialized data"); }
    if (flags & 0x00000080) { chars += string_newline("Contains uninitialized data"); }
    if (flags & 0x00000100) { chars += string_newline(reserved_flag_in_sectionflags("Other section")); }
    if (flags & 0x00000200) { chars += string_newline(reserved_flag_in_sectionflags("Info section")); }
    if (flags & 0x00000400) { chars += string_newline(reserved_flag_in_sectionflags("Reserved")); }
    if (flags & 0x00000800) { chars += string_newline(reserved_flag_in_sectionflags("Remove section")); }
    if (flags & 0x00001000) { chars += string_newline(reserved_flag_in_sectionflags("COMDAT section")); }
    if (flags & 0x00008000) { chars += string_newline("GP relative"); }
    if (flags & 0x00010000) { chars += string_newline(reserved_flag_in_sectionflags("Purge memory")); }
    if (flags & 0x00020000) { chars += string_newline(reserved_flag_in_sectionflags("16bit memory")); }
    if (flags & 0x00040000) { chars += string_newline(reserved_flag_in_sectionflags("Locked Memory")); }
    if (flags & 0x00080000) { chars += string_newline(reserved_flag_in_sectionflags("Preload Memory")); }
    if (flags & 0x00100000) { chars += string_newline(reserved_flag_in_sectionflags("Align 1 Bytes")); }
    if (flags & 0x00200000) { chars += string_newline(reserved_flag_in_sectionflags("Align 2 Bytes")); }
    if (flags & 0x00300000) { chars += string_newline(reserved_flag_in_sectionflags("Align 4 Bytes")); }
    if (flags & 0x00400000) { chars += string_newline(reserved_flag_in_sectionflags("Align 8 Bytes")); }
    if (flags & 0x00500000) { chars += string_newline(reserved_flag_in_sectionflags("Align 16 Bytes")); }
    if (flags & 0x00600000) { chars += string_newline(reserved_flag_in_sectionflags("Align 32 Bytes")); }
    if (flags & 0x00700000) { chars += string_newline(reserved_flag_in_sectionflags("Align 64 Bytes")); }
    if (flags & 0x00800000) { chars += string_newline(reserved_flag_in_sectionflags("Align 128 Bytes")); }
    if (flags & 0x00900000) { chars += string_newline(reserved_flag_in_sectionflags("Align 256 Bytes")); }
    if (flags & 0x00A00000) { chars += string_newline(reserved_flag_in_sectionflags("Align 512 Bytes")); }
    if (flags & 0x00B00000) { chars += string_newline(reserved_flag_in_sectionflags("Align 1024 Bytes")); }
    if (flags & 0x00C00000) { chars += string_newline(reserved_flag_in_sectionflags("Align 2048 Bytes")); }
    if (flags & 0x00D00000) { chars += string_newline(reserved_flag_in_sectionflags("Align 4096 Bytes")); }
    if (flags & 0x00E00000) { chars += string_newline(reserved_flag_in_sectionflags("Align 8192 Bytes")); }
    if (flags & 0x01000000) { chars += string_newline("Extended relocations"); }
    if (flags & 0x02000000) { chars += string_newline("Section discardable"); }
    if (flags & 0x04000000) { chars += string_newline("Section not cacheable"); }
    if (flags & 0x08000000) { chars += string_newline("Section not paged"); }
    if (flags & 0x10000000) { chars += string_newline("Section shared"); }
    if (flags & 0x20000000) { chars += string_newline("Section executable"); }
    if (flags & 0x40000000) { chars += string_newline("Section readable"); }
    if (flags & 0x80000000) { chars += string_newline("Section writable"); }
    if (chars == "") {
        chars = "None";
    }
    return chars;
}

void convert_subsystem(uint16_t subsystem, oh_returndata *returndata) {
    if (subsystem == 0x0000) { returndata->subsystem = "None"; }
    if (subsystem == 0x0001) { returndata->subsystem = "Native Windows"; }
    if (subsystem == 0x0002) { returndata->subsystem = "Windows GUI"; }
    if (subsystem == 0x0003) { returndata->subsystem = "Windows Console"; }
    if (subsystem == 0x0005) { returndata->subsystem = "OS/2 Console"; }
    if (subsystem == 0x0007) { returndata->subsystem = "POSIX Console"; }
    if (subsystem == 0x0008) { returndata->subsystem = "Windows 9X Driver"; }
    if (subsystem == 0x0009) { returndata->subsystem = "Windows CE GUI"; }
    if (subsystem == 0x000A) { returndata->subsystem = "EFI Application"; }
    if (subsystem == 0x000B) { returndata->subsystem = "EFI Boot Service Driver"; }
    if (subsystem == 0x000C) { returndata->subsystem = "EFI Runtime Driver"; }
    if (subsystem == 0x000D) { returndata->subsystem = "EFI ROM Image"; }
    if (subsystem == 0x000E) { returndata->subsystem = "XBOX"; }
    if (subsystem == 0x0010) { returndata->subsystem = "Windows Boot Application"; }
}

void convert_magic(uint16_t magic, oh_returndata *returndata) {
    if (magic == 0x010B) { returndata->magic = "PE32"; }
    if (magic == 0x020B) { returndata->magic = "PE32+"; }
}
