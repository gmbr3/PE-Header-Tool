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

void PotentialIssues::NewInformation(QString info) {
    information_qbrush.setColor(Qt::darkGray);
    newitem = new QListWidgetItem;
    newitem->setText(info);
    newitem->setForeground(information_qbrush);
    ui->issueList->addItem(newitem);
}

void PotentialIssues::NewWarning(QString info) {
    warning_qbrush.setColor(Qt::yellow);
    newitem = new QListWidgetItem;
    newitem->setText(info);
    newitem->setForeground(warning_qbrush);
    ui->issueList->addItem(newitem);
}

void PotentialIssues::NewError(QString info) {
    error_qbrush.setColor(Qt::red);
    newitem = new QListWidgetItem;
    newitem->setText(info);
    newitem->setForeground(error_qbrush);
    ui->issueList->addItem(newitem);
}

