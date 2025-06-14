
#include "fileselection.h"
#include "fhinformation.h"
#include "ui_fhinformation.h"
#include "../main.h"

FHInformation::FHInformation(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::FHInformation)
{
    ui->setupUi(this);
}

FHInformation::~FHInformation()
{
    delete ui;
}

void FHInformation::showEvent(QShowEvent *event) {
    if (event) {
        std::cout << "Show event!" << std::endl;
        this->move(400,0);
        QWidget::showEvent(event);
    }
    return;
}

void FHInformation::setup() {
        rparent = dynamic_cast<FileSelection*>(parent());
        rparent->getFile(&filename, &location);
        open_file(file,filename);
        skip_chars(file, location);
        std::cout << "FH loc is " << location << std::endl;
        std::cout << "hello!" << std::endl;
        returndata = get_file_header(file);
        location = file.tellg();
        std::cout << "bong!" << std::endl;
        InfoToTable(&returndata, ui->FHTable);
        ohi = new OHInformation(this);
        ohi->setWindowFlags(Qt::Window);
        ohi->setAttribute(Qt::WA_DeleteOnClose, false);
        ohi->setup();
}

void FHInformation::hideEvent(QHideEvent *event) {
    if (event) {
        std::cout << " FH Hide event!" << std::endl;
        QWidget::hideEvent(event);
    }
}

void FHInformation::getFile(std::string *rfilename, uint64_t *rlocation) {
    *rfilename = filename;
    *rlocation = location;
}

void FHInformation::getReturnData(fh_returndata *rreturndata) {
    *rreturndata = returndata;
}


void FHInformation::InfoToTable(fh_returndata *returndata, QTableWidget *table) {
    table->setItem(0,0,new QTableWidgetItem(QString::fromStdString(returndata->machine)));
    table->setItem(1,0,new QTableWidgetItem(QString::fromStdString(returndata->numberofsections)));
    table->setItem(2,0,new QTableWidgetItem(QString::fromStdString(returndata->timedatestamp)));
    table->resizeRowToContents(2);
    table->setItem(3,0,new QTableWidgetItem(QString::fromStdString(returndata->pointertosymboltable)));
    table->setItem(4,0,new QTableWidgetItem(QString::fromStdString(returndata->numberofsymbols)));
    table->setItem(5,0,new QTableWidgetItem(QString::fromStdString(returndata->sizeofoptional)));
    table->setItem(6,0,new QTableWidgetItem(QString::fromStdString(returndata->chars)));
    table->resizeRowToContents(6);
}


