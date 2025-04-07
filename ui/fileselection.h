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
    void handleSelection();
    std::string* getFile();

private:
    Ui::FileSelection *ui;
    FHInformation fhi;
    QString text_filename;
    std::string filename;
    std::ifstream file;
};

#endif // FILESELECTION_H
