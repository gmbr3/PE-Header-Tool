#include "ohinformation.h"
#include "ui_ohinformation.h"

#include "fhinformation.h"
#include "../main.h"

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

void OHInformation::showEvent(QShowEvent *event) {
    if (event) {
        std::cout << "Show event!" << std::endl;
        this->move(900,0);
        QWidget::showEvent(event);
    }
    return;
}

void OHInformation::setup() {
        rparent = dynamic_cast<FHInformation*>(parent());
        rparent->getFile(&filename, &location);
        open_file(file,filename);
        skip_chars(file, location);
        std::cout << "OH loc is " << location << std::endl;
        std::cout << "hello!" << std::endl;
        returndata = get_optional_header(file);
        location = file.tellg();
        std::cout << "bong!" << std::endl;
        InfoToTable(&returndata, ui->OHTable);
        dd = new DataDirectories(this);
        dd->setWindowFlags(Qt::Window);
        dd->setAttribute(Qt::WA_DeleteOnClose, false);
        dd->setup();
}

void OHInformation::getFile(std::string *rfilename, uint64_t *rlocation) {
    *rfilename = filename;
    *rlocation = location;
}

void OHInformation::getReturnData(oh_returndata *rreturndata) {
    *rreturndata = returndata;
}

void OHInformation::InfoToTable(oh_returndata *returndata, QTableWidget *table) {
    table->setItem(0,0,new QTableWidgetItem(QString::fromStdString(returndata->magic)));
    table->setItem(1,0,new QTableWidgetItem(QString::fromStdString(returndata->majorlinkerversion)));
    table->setItem(2,0,new QTableWidgetItem(QString::fromStdString(returndata->minorlinkerversion)));
    table->setItem(3,0,new QTableWidgetItem(QString::fromStdString(returndata->sizeofcode)));
    table->setItem(4,0,new QTableWidgetItem(QString::fromStdString(returndata->sizeofinitdata)));
    table->setItem(5,0,new QTableWidgetItem(QString::fromStdString(returndata->sizeofunitdata)));
    table->setItem(6,0,new QTableWidgetItem(QString::fromStdString(returndata->addressofentrypoint)));
    table->setItem(7,0,new QTableWidgetItem(QString::fromStdString(returndata->baseofcode)));
    table->setItem(8,0,new QTableWidgetItem(QString::fromStdString(returndata->baseofdata)));
    table->setItem(9,0,new QTableWidgetItem(QString::fromStdString(returndata->imagebase)));
    table->setItem(10,0,new QTableWidgetItem(QString::fromStdString(returndata->sectionalignment)));
    table->setItem(11,0,new QTableWidgetItem(QString::fromStdString(returndata->filealignment)));
    table->setItem(12,0,new QTableWidgetItem(QString::fromStdString(returndata->majoroperatingsystemversion)));
    table->setItem(13,0,new QTableWidgetItem(QString::fromStdString(returndata->minoroperatingsystemversion)));
    table->setItem(14,0,new QTableWidgetItem(QString::fromStdString(returndata->majorimageversion)));
    table->setItem(15,0,new QTableWidgetItem(QString::fromStdString(returndata->minorimageversion)));
    table->setItem(16,0,new QTableWidgetItem(QString::fromStdString(returndata->majorsubsystemversion)));
    table->setItem(17,0,new QTableWidgetItem(QString::fromStdString(returndata->minorsubsystemversion)));
    table->setItem(18,0,new QTableWidgetItem(QString::fromStdString(returndata->win32versionvalue)));
    table->setItem(19,0,new QTableWidgetItem(QString::fromStdString(returndata->sizeofimage)));
    table->setItem(20,0,new QTableWidgetItem(QString::fromStdString(returndata->sizeofheaders)));
    table->setItem(21,0,new QTableWidgetItem(QString::fromStdString(returndata->checksum)));
    table->setItem(22,0,new QTableWidgetItem(QString::fromStdString(returndata->subsystem)));
    table->setItem(23,0,new QTableWidgetItem(QString::fromStdString(returndata->dllchars)));
    table->resizeRowToContents(23);
    table->setItem(24,0,new QTableWidgetItem(QString::fromStdString(returndata->sizeofstackreserve)));
    table->setItem(25,0,new QTableWidgetItem(QString::fromStdString(returndata->sizeofstackcommit)));
    table->setItem(26,0,new QTableWidgetItem(QString::fromStdString(returndata->sizeofheapreserve)));
    table->setItem(27,0,new QTableWidgetItem(QString::fromStdString(returndata->sizeofheapcommit)));
    table->setItem(28,0,new QTableWidgetItem(QString::fromStdString(returndata->loaderflags)));
    table->setItem(29,0,new QTableWidgetItem(QString::fromStdString(returndata->numberofrva)));
}


