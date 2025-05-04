#ifndef FILESELECTION_H
#define FILESELECTION_H

#include <QDockWidget>

#include "fhinformation.h"
#include "potentialissues.h"

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
    void handleButton();
    void handleSelection();
    void getFile(std::string *rfilename, uint64_t *rlocation);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::FileSelection *ui;
    FHInformation fhi;
    QString text_filename;
    std::string filename;
    std::ifstream file;
    uint64_t location;
    MainWindow* rparent;
    PotentialIssues pi;
};

#endif // FILESELECTION_H
