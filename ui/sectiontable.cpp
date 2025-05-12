#include "sectiontable.h"
#include "ui_sectiontable.h"

#include "../main.h"
#include "datadirectories.h"
#include "fhinformation.h"

SectionTable::SectionTable(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SectionTable)
{
    ui->setupUi(this);
    connect(ui->nextButton, &QPushButton::released, this, &SectionTable::handleButton);
}

SectionTable::~SectionTable()
{
    delete ui;
}

void SectionTable::showEvent(QShowEvent *event) {
    if (event) {
        std::cout << "Show event!" << std::endl;
        rparent = dynamic_cast<DataDirectories*>(parent());
        rparent->getFile(&filename, &location);
        open_file(file,filename);
        skip_chars(file, location);
        std::cout << "ST loc is " << location << std::endl;
        rparent2 = dynamic_cast<FHInformation*>(rparent->parent()->parent());
        rparent2->getReturnData(&fhreturndata);
        std::cout << "hello!" << std::endl;
        maxsection = std::stoull(fhreturndata.numberofsections);
        get_section_tables(maxsection, file, &returndata);
        location = file.tellg();
        std::cout << "bong!" << std::endl;
        currentsection = 0;
        InfoToTable(returndata, ui->STTable);
        QWidget::showEvent(event);
    }
    return;
}

void SectionTable::closeEvent(QCloseEvent *event) {
    if (event) {
        std::cout << " ST Close event!" << std::endl;
        QWidget::closeEvent(event);
        qApp->quit();
    }
}

void SectionTable::InfoToTable(st_returndata_vector returndata, QTableWidget *table) {
    table->setItem(0,0,new QTableWidgetItem(QString::fromStdString(returndata[currentsection].name)));
    table->setItem(1,0,new QTableWidgetItem(QString::fromStdString(returndata[currentsection].virtualsize)));
    table->setItem(2,0,new QTableWidgetItem(QString::fromStdString(returndata[currentsection].virtualaddress)));
    table->setItem(3,0,new QTableWidgetItem(QString::fromStdString(returndata[currentsection].sizeofrawdata)));
    table->setItem(4,0,new QTableWidgetItem(QString::fromStdString(returndata[currentsection].pointertorawdata)));
    table->setItem(5,0,new QTableWidgetItem(QString::fromStdString(returndata[currentsection].pointertorelocations)));
    table->setItem(6,0,new QTableWidgetItem(QString::fromStdString(returndata[currentsection].pointertolinenumbers)));
    table->setItem(7,0,new QTableWidgetItem(QString::fromStdString(returndata[currentsection].numberofrelocations)));
    table->setItem(8,0,new QTableWidgetItem(QString::fromStdString(returndata[currentsection].numberoflinenumbers)));
    table->setItem(9,0,new QTableWidgetItem(QString::fromStdString(returndata[currentsection].chars)));
}

void SectionTable::handleButton() {
    std::cout << "Next button pressed!" << std::endl;
    if (currentsection < maxsection-1) {
        currentsection++;
    } else {
        std::cout << "No more sections!" << std::endl;
        currentsection = 0;
    }
    InfoToTable(returndata, ui->STTable);
}
