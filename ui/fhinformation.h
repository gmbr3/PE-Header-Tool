#ifndef FHINFORMATION_H
#define FHINFORMATION_H

#include <QDockWidget>
#include "../file_header.h"

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

private:
    Ui::FHInformation *ui;
    std::string* filename;
    std::ifstream file;
    fh_returndata returndata;
    FileSelection* rparent;
};

#endif // FHINFORMATION_H
