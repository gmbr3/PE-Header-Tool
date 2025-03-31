#include "datadirectories.h"
#include "ui_datadirectories_ui.h"

DataDirectories::DataDirectories(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DataDirectories)
{
    ui->setupUi(this);
}

DataDirectories::~DataDirectories()
{
    delete ui;
}
