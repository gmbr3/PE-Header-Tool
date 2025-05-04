#ifndef POTENTIALISSUES_H
#define POTENTIALISSUES_H

#include <QDockWidget>
#include <QBrush>
#include <QListWidgetItem>

#include "../main.h"

namespace Ui {
class PotentialIssues;
}

class PotentialIssues : public QDockWidget
{
    Q_OBJECT

public:
    explicit PotentialIssues(QWidget *parent = nullptr);
    ~PotentialIssues();

private:
    Ui::PotentialIssues *ui;
    QBrush information_qbrush;
    QBrush warning_qbrush;
    QBrush error_qbrush;
    QListWidgetItem *newitem;

public slots:
    void NewInformation(QString info);
    void NewWarning(QString warning);
    void NewError(QString error);
};

#endif // POTENTIALISSUES_H
