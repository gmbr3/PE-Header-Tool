#include "information.h"
#include "ui_information.h"

#include <iostream>

#include <QListWidgetItem>
#include <Qt>

#include "fileselection.h"
#include "fhinformation.h"
#include "ohinformation.h"
#include "datadirectories.h"
#include "sectiontable.h"


extern Information *potential_issues = nullptr;

Information::Information(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Information)
{
    potential_issues = this;
    ui->setupUi(this);
    fs = dynamic_cast<FileSelection*>(parent);
    connect(ui->actionNew_File, &QAction::triggered, this, &Information::newFile, Qt::QueuedConnection);
    connect(ui->actionClose, &QAction::triggered, this, &Information::closeApp, Qt::QueuedConnection);
    connect(ui->actionFile_Header_Information, &QAction::triggered, this, &Information::showFHI, Qt::QueuedConnection);
    connect(ui->actionOptional_Header, &QAction::triggered, this, &Information::showOHI, Qt::QueuedConnection);
    connect(ui->actionData_Directories, &QAction::triggered, this, &Information::showDD, Qt::QueuedConnection);
    connect(ui->actionSection_Tables, &QAction::triggered, this, &Information::showST, Qt::QueuedConnection);
}

Information::~Information()
{
    delete ui;
}

void Information::disableSelection(QListWidgetItem *item) {
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
}

void Information::NewInformation(QString info) {
    information_qbrush = new QBrush(Qt::darkGray);
    newitem = new QListWidgetItem(info);
    newitem->setBackground(*information_qbrush);
    disableSelection(newitem);
    ui->issueList->addItem(newitem);
}

void Information::NewWarning(QString info) {
    warning_qbrush = new QBrush(Qt::yellow);
    newitem = new QListWidgetItem(info);
    newitem->setBackground(*warning_qbrush);
    disableSelection(newitem);
    ui->issueList->addItem(newitem);
}

void Information::NewError(QString info) {
    error_qbrush = new QBrush(Qt::red);
    newitem = new QListWidgetItem(info);
    newitem->setBackground(*error_qbrush);
    disableSelection(newitem);
    ui->issueList->addItem(newitem);
}

void Information::showEvent(QShowEvent *event) {
    if (event) {
        std::cout << "Show event!" << std::endl;
        this->move(0,0);
        QWidget::showEvent(event);
    }
}

void Information::closeEvent(QCloseEvent *event) {
    if (event) {
        qApp->quit();
    }
}

void Information::newFile() {
    if (fs->fhi) {
        fs->fhi->ohi->dd->st->setAttribute(Qt::WA_DeleteOnClose, true);
        fs->fhi->ohi->dd->st->close();
        fs->fhi->ohi->dd->setAttribute(Qt::WA_DeleteOnClose, true);
        fs->fhi->ohi->dd->close();
        fs->fhi->ohi->setAttribute(Qt::WA_DeleteOnClose, true);
        fs->fhi->ohi->close();
        fs->fhi->setAttribute(Qt::WA_DeleteOnClose, true);
        fs->fhi->close();
    }
    fs->show();
}

void Information::closeApp() {
    qApp->quit();
}

void Information::showFHI() {
    fs->fhi->show();
}

void Information::showOHI() {
    fs->fhi->ohi->show();
}

void Information::showDD() {
    fs->fhi->ohi->dd->show();
}

void Information::showST() {
    fs->fhi->ohi->dd->st->show();
}

void Information::setup() {
    ui->issueList->clear();
}
