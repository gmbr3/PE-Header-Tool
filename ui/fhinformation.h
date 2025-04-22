#ifndef FHINFORMATION_H
#define FHINFORMATION_H

#include <QDockWidget>
#include <QTableWidget>
#include "../file_header.h"
#include "ohinformation.h"

class FileSelection;

namespace Ui {
class FHInformation;
}

class FHInformation : public QDockWidget
{
    Q_OBJECT

public:
    explicit FHInformation(QWidget *parent = nullptr);
    ~FHInformation();
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);
    void InfoToTable(fh_returndata *returndata, QTableWidget *table);
    void getFile(std::string *rfilename, uint64_t *rlocation);

private:
    Ui::FHInformation *ui;
    std::string filename;
    std::ifstream file;
    fh_returndata returndata;
    FileSelection* rparent;
    uint64_t location;
    OHInformation ohi;
};

#endif // FHINFORMATION_H
