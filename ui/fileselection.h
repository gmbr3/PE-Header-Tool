#ifndef FILESELECTION_H
#define FILESELECTION_H

#include <QDockWidget>

#include "fhinformation.h"

namespace Ui {
class FileSelection;
}

class FileSelection : public QDockWidget
{
    Q_OBJECT

public:
    explicit FileSelection(QWidget *parent = nullptr);
    ~FileSelection();
    void handleButton();

private:
    Ui::FileSelection *ui;
    FHInformation fhi;
};

#endif // FILESELECTION_H
