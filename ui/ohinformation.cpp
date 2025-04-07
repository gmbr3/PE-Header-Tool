#include "ohinformation.h"
#include "ui_ohinformation.h"

OHInformation::OHInformation(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::OHInformation)
{
    ui->setupUi(this);
}

OHInformation::~OHInformation()
{
    delete ui;
}
