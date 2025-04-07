
#include "fileselection.h"
#include "fhinformation.h"
#include "ui_fhinformation.h"
#include "../main.h"

FHInformation::FHInformation(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::FHInformation)
{
    ui->setupUi(this);
    ui->FHTable->setItem(0,0,new QTableWidgetItem(QString("Test")));
}

FHInformation::~FHInformation()
{
    delete ui;
}

void FHInformation::showEvent(QShowEvent *event) {
    std::cout << "Show event!" << std::endl;
    rparent = dynamic_cast<FileSelection*>(parent());
    filename = rparent->getFile();
    open_file(file,*filename);
    std::cout << "hello!" << std::endl;
    returndata = get_file_header(file);
    std::cout << "bong!" << std::endl;
    return;
}
