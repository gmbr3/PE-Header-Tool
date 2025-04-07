#include "potentialissues.h"
#include "ui_potentialissues.h"

PotentialIssues::PotentialIssues(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PotentialIssues)
{
    ui->setupUi(this);
}

PotentialIssues::~PotentialIssues()
{
    delete ui;
}
