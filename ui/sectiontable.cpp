#include "sectiontable.h"
#include "ui_sectiontable_ui.h"

SectionTable::SectionTable(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SectionTable)
{
    ui->setupUi(this);
}

SectionTable::~SectionTable()
{
    delete ui;
}
