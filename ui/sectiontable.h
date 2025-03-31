#ifndef SECTIONTABLE_H
#define SECTIONTABLE_H

#include <QDockWidget>

namespace Ui {
class SectionTable;
}

class SectionTable : public QDockWidget
{
    Q_OBJECT

public:
    explicit SectionTable(QWidget *parent = nullptr);
    ~SectionTable();

private:
    Ui::SectionTable *ui;
};

#endif // SECTIONTABLE_H
