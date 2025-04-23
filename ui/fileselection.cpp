#include "fileselection.h"
#include "ui_fileselection.h"

#include <iostream>
#include <QFileDialog>

#include "../main.h"
#include "mainwindow.h"

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
    if (!text_filename.isNull() && text_filename != "No file selected!") {
        fhi.setParent(this, Qt::Window);
        fhi.show();
        this->hide();
    }
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
        open_file(file,filename);
        location = 0;
        std::cout << "FS loc is " << location << std::endl;
        check_pe32_file(file, &location);
        location = file.tellg();
    }
    ui->filepath->setText(text_filename);
}

void FileSelection::getFile(std::string *rfilename, uint64_t *rlocation) {
    *rfilename = filename;
    *rlocation = location;
}

void FileSelection::hideEvent(QHideEvent *event) {
    if (event) {
        std::cout << "FS Hide event!" << std::endl;
        QWidget::hideEvent(event);
    }
}

void FileSelection::closeEvent(QCloseEvent *event) {
    if (event) {
        std::cout << "FS Close event!" << std::endl;
        QWidget::closeEvent(event);
    }
}

