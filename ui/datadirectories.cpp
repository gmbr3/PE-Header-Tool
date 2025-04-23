#include "datadirectories.h"
#include "ui_datadirectories.h"

#include "ohinformation.h"
#include "../main.h"

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

void DataDirectories::showEvent(QShowEvent *event) {
    if (event) {
        std::cout << "Show event!" << std::endl;
        rparent = dynamic_cast<OHInformation*>(parent());
        rparent->getFile(&filename, &location);
        open_file(file,filename);
        skip_chars(file, location);
        std::cout << "DD loc is " << location << std::endl;
        std::cout << "hello!" << std::endl;
        returndata = get_data_dirs(file);
        location = file.tellg();
        std::cout << "bong!" << std::endl;
        InfoToTable(&returndata, ui->DDTable);
        st.setParent(this, Qt::Window);
        st.show();
        QWidget::showEvent(event);
    }
    return;
}

void DataDirectories::getFile(std::string *rfilename, uint64_t *rlocation) {
    *rfilename = filename;
    *rlocation = location;
}

void DataDirectories::closeEvent(QCloseEvent *event) {
    if (event) {
        std::cout << " DD Close event!" << std::endl;
        QWidget::closeEvent(event);
        qApp->quit();
    }
}

void DataDirectories::InfoToTable(datadirs_returndata *returndata, QTableWidget *table) {
    table->setItem(0,0,new QTableWidgetItem(QString::fromStdString(returndata->exporttable_addr)));
    table->setItem(0,1,new QTableWidgetItem(QString::fromStdString(returndata->exporttable_size)));
    table->setItem(1,0,new QTableWidgetItem(QString::fromStdString(returndata->importtable_addr)));
    table->setItem(1,1,new QTableWidgetItem(QString::fromStdString(returndata->importtable_size)));
    table->setItem(2,0,new QTableWidgetItem(QString::fromStdString(returndata->resourcetable_addr)));
    table->setItem(2,1,new QTableWidgetItem(QString::fromStdString(returndata->resourcetable_size)));
    table->setItem(3,0,new QTableWidgetItem(QString::fromStdString(returndata->exceptiontable_addr)));
    table->setItem(3,1,new QTableWidgetItem(QString::fromStdString(returndata->exceptiontable_size)));
    table->setItem(4,0,new QTableWidgetItem(QString::fromStdString(returndata->certificatetable_addr)));
    table->setItem(4,1,new QTableWidgetItem(QString::fromStdString(returndata->certificatetable_size)));
    table->setItem(5,0,new QTableWidgetItem(QString::fromStdString(returndata->basereloctable_addr)));
    table->setItem(5,1,new QTableWidgetItem(QString::fromStdString(returndata->basereloctable_size)));
    table->setItem(6,0,new QTableWidgetItem(QString::fromStdString(returndata->debug_addr)));
    table->setItem(6,1,new QTableWidgetItem(QString::fromStdString(returndata->debug_size)));
    table->setItem(7,0,new QTableWidgetItem(QString::fromStdString(returndata->arch_addr)));
    table->setItem(7,1,new QTableWidgetItem(QString::fromStdString(returndata->arch_size)));
    table->setItem(8,0,new QTableWidgetItem(QString::fromStdString(returndata->globalptr_addr)));
    table->setItem(8,1,new QTableWidgetItem(QString::fromStdString(returndata->globalptr_size)));
    table->setItem(9,0,new QTableWidgetItem(QString::fromStdString(returndata->tlstable_addr)));
    table->setItem(9,1,new QTableWidgetItem(QString::fromStdString(returndata->tlstable_size)));
    table->setItem(10,0,new QTableWidgetItem(QString::fromStdString(returndata->loadconftable_addr)));
    table->setItem(10,1,new QTableWidgetItem(QString::fromStdString(returndata->loadconftable_size)));
    table->setItem(11,0,new QTableWidgetItem(QString::fromStdString(returndata->boundimport_addr)));
    table->setItem(11,1,new QTableWidgetItem(QString::fromStdString(returndata->boundimport_size)));
    table->setItem(12,0,new QTableWidgetItem(QString::fromStdString(returndata->iat_addr)));
    table->setItem(12,1,new QTableWidgetItem(QString::fromStdString(returndata->iat_size)));
    table->setItem(13,0,new QTableWidgetItem(QString::fromStdString(returndata->delayimport_addr)));
    table->setItem(13,1,new QTableWidgetItem(QString::fromStdString(returndata->delayimport_size)));
    table->setItem(14,0,new QTableWidgetItem(QString::fromStdString(returndata->clr_addr)));
    table->setItem(14,1,new QTableWidgetItem(QString::fromStdString(returndata->clr_size)));
    table->setItem(15,0,new QTableWidgetItem(QString::fromStdString(returndata->reserved_addr)));
    table->setItem(15,1,new QTableWidgetItem(QString::fromStdString(returndata->reserved_size)));

}
