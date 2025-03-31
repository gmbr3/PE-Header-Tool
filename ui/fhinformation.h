#ifndef FHINFORMATION_H
#define FHINFORMATION_H

#include <QDockWidget>

namespace Ui {
class FHInformation;
}

class FHInformation : public QDockWidget
{
    Q_OBJECT

public:
    explicit FHInformation(QWidget *parent = nullptr);
    ~FHInformation();

private:
    Ui::FHInformation *ui;
};

#endif // FHINFORMATION_H
