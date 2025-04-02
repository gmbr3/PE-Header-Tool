#include "fileselection.h"
#include "ui_fileselection.h"

#include <iostream>
#include <QFileDialog>

FileSelection::FileSelection(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::FileSelection)
{
    ui->setupUi(this);
    connect(ui->continueButton, &QPushButton::released, this, &FileSelection::handleButton);
    connect(ui->fileButton, &QPushButton::released, this, &FileSelection::handleSelection);
}

FileSelection::~FileSelection()
{
    delete ui;
}

void FileSelection::handleButton() {
    std::cout << "Button clicked!" << std::endl;
    fhi.show();
    return;
}

void FileSelection::handleSelection() {
    filename = QFileDialog::getOpenFileName(this,
        tr("Open PE32 Image"), "/home", tr("UEFI executables (*.efi);;PE32 Files (*.exe *.dll)"));
    if (filename.isNull()) {
        std::cout << "No file selected!" << std::endl;
        filename = "No file selected!";
    } else {
        std::cout << "Selected file: " << filename.toStdString() << std::endl;
        filename = "Selected file: " + filename;
    }
    ui->filepath->setText(filename);
}
