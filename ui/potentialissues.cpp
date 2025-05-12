#include "potentialissues.h"
#include "ui_potentialissues.h"

#include <QListWidgetItem>
#include <Qt>


extern PotentialIssues *potential_issues;

PotentialIssues::PotentialIssues(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PotentialIssues)
{
    potential_issues = this;
    ui->setupUi(this);
}

PotentialIssues::~PotentialIssues()
{
    delete ui;
}

void PotentialIssues::disableSelection(QListWidgetItem *item) {
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
}

void PotentialIssues::NewInformation(QString info) {
    information_qbrush = new QBrush(Qt::darkGray);
    newitem = new QListWidgetItem(info);
    newitem->setBackground(*information_qbrush);
    disableSelection(newitem);
    ui->issueList->addItem(newitem);
}

void PotentialIssues::NewWarning(QString info) {
    warning_qbrush = new QBrush(Qt::yellow);
    newitem = new QListWidgetItem(info);
    newitem->setBackground(*warning_qbrush);
    disableSelection(newitem);
    ui->issueList->addItem(newitem);
}

void PotentialIssues::NewError(QString info) {
    error_qbrush = new QBrush(Qt::red);
    newitem = new QListWidgetItem(info);
    newitem->setBackground(*error_qbrush);
    disableSelection(newitem);
    ui->issueList->addItem(newitem);
}

