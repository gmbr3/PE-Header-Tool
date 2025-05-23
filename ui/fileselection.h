#ifndef FILESELECTION_H
#define FILESELECTION_H

#include <QDockWidget>

#include "fhinformation.h"
#include "information.h"

class MainWindow;

namespace Ui {
class FileSelection;
}

class FileSelection : public QDockWidget
{
    Q_OBJECT

public:
    explicit FileSelection(QWidget *parent = nullptr);
    ~FileSelection();
    FHInformation *fhi;
    Information *pi = nullptr;
    void handleButton();
    void handleSelection();
    void getFile(std::string *rfilename, uint64_t *rlocation);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private:
    Ui::FileSelection *ui;
    QString text_filename;
    std::string filename;
    std::ifstream file;
    uint64_t location;
    MainWindow* rparent;
};

#endif // FILESELECTION_H
