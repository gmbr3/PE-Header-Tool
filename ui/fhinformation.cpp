#include "fhinformation.h"
#include "ui_fhinformation.h"

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
