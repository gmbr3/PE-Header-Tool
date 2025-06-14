#ifndef SECTIONTABLE_H
#define SECTIONTABLE_H

#include <QDockWidget>
#include <QTableWidget>

#include "../optional_header.h"
#include "../file_header.h"

class DataDirectories;
class FHInformation;

namespace Ui {
class SectionTable;
}

class SectionTable : public QDockWidget
{
    Q_OBJECT

public:
    explicit SectionTable(QWidget *parent = nullptr);
    ~SectionTable();
    void showEvent(QShowEvent *event);
    void InfoToTable(st_returndata_vector returndata, QTableWidget *table);
    void handleButton();
    void setup();

private:
    Ui::SectionTable *ui;
    std::string filename = "";
    std::ifstream file;
    st_returndata_vector returndata;
    fh_returndata fhreturndata;
    DataDirectories* rparent;
    FHInformation* rparent2;
    uint64_t location;
    uint64_t currentsection;
    uint64_t maxsection;
};

#endif // SECTIONTABLE_H
