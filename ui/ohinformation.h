#ifndef OHINFORMATION_H
#define OHINFORMATION_H

#include <QDockWidget>
#include <QTableWidget>

#include "../optional_header.h"

class FHInformation;

namespace Ui {
class OHInformation;
}

class OHInformation : public QDockWidget
{
    Q_OBJECT

public:
    explicit OHInformation(QWidget *parent = nullptr);
    ~OHInformation();
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
    void InfoToTable(oh_returndata *returndata, QTableWidget *table);

private:
    Ui::OHInformation *ui;
    std::string filename;
    std::ifstream file;
    oh_returndata returndata;
    FHInformation* rparent;
    uint64_t location;
};

#endif // OHINFORMATION_H
