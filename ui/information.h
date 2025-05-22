#ifndef INFORMATION_H
#define INFORMATION_H

#include <QMainWindow>
#include <QBrush>
#include <QListWidgetItem>
#include <QMenuBar>

class FileSelection;

namespace Ui {
class Information;
}

class Information : public QMainWindow
{
    Q_OBJECT

public:
    explicit Information(QWidget *parent = nullptr);
    ~Information();
    void disableSelection(QListWidgetItem *item);
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
    void closeApp();
    void showFHI();
    void showOHI();
    void showDD();
    void showST();

private:
    Ui::Information *ui;
    QBrush *information_qbrush;
    QBrush *warning_qbrush;
    QBrush *error_qbrush;
    QListWidgetItem *newitem;
    FileSelection *fs;


public slots:
    void NewInformation(QString info);
    void NewWarning(QString warning);
    void NewError(QString error);
};

#endif // INFORMATION_H
