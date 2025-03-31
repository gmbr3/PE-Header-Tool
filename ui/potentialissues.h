#ifndef POTENTIALISSUES_H
#define POTENTIALISSUES_H

#include <QDockWidget>

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
};

#endif // POTENTIALISSUES_H
