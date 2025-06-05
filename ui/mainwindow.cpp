#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileselection.h"

extern bool uefi_mode = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->continueButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(ui->uefiBox, &QCheckBox::clicked, this, &MainWindow::uefiButtonClicked);
    connect(ui->basicBox, &QCheckBox::clicked, this, &MainWindow::basicButtonClicked);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton() {
    fs.show();
    this->close();
}

void MainWindow::uefiButtonClicked() {
    uefi_mode = true;
    ui->basicBox->setChecked(false);
}

void MainWindow::basicButtonClicked() {
    uefi_mode = false;
    ui->uefiBox->setChecked(false);
}

