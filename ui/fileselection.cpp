#include "fileselection.h"
#include "ui_fileselection.h"

#include <iostream>
#include <QFileDialog>

#include "../main.h"

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
    text_filename = QFileDialog::getOpenFileName(this,
        tr("Open PE32 Image"), "/home", tr("UEFI executables (*.efi);;PE32 Files (*.exe *.dll)"));
    if (text_filename.isNull()) {
        std::cout << "No file selected!" << std::endl;
        text_filename = "No file selected!";
    } else {
        filename = text_filename.toStdString();
        std::cout << "Selected file: " << filename << std::endl;
        text_filename = "Selected file: " + text_filename;
        open_file(filename);
    }
    ui->filepath->setText(text_filename);
}
