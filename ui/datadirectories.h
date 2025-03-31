#ifndef DATADIRECTORIES_H
#define DATADIRECTORIES_H

#include <QDockWidget>

namespace Ui {
class DataDirectories;
}

class DataDirectories : public QDockWidget
{
    Q_OBJECT

public:
    explicit DataDirectories(QWidget *parent = nullptr);
    ~DataDirectories();

private:
    Ui::DataDirectories *ui;
};

#endif // DATADIRECTORIES_H
