#include "mainwindow.moc.h"
#include "mainwindow_ui.ui.h"
#include "fileselection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->continueButton, &QPushButton::released, this, &MainWindow::handleButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton() {
    fs.show();
    this->hide();
}

