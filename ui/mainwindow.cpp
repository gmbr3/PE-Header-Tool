#include "mainwindow.h"
#include "ui_mainwindow.h"
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

