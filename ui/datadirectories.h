#ifndef DATADIRECTORIES_H
#define DATADIRECTORIES_H

#include <QDockWidget>
#include <QTableWidget>

#include "../optional_header.h"
#include "sectiontable.h"

class OHInformation;

namespace Ui {
class DataDirectories;
}

class DataDirectories : public QDockWidget
{
    Q_OBJECT

public:
    explicit DataDirectories(QWidget *parent = nullptr);
    ~DataDirectories();
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
    void InfoToTable(datadirs_returndata *returndata, QTableWidget *table);
    void getFile(std::string *rfilename, uint64_t *rlocation);

private:
    Ui::DataDirectories *ui;
    std::string filename;
    std::ifstream file;
    datadirs_returndata returndata;
    OHInformation* rparent;
    uint64_t location;
    SectionTable st;
};

#endif // DATADIRECTORIES_H
