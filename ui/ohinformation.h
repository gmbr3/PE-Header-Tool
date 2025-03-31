#ifndef OHINFORMATION_H
#define OHINFORMATION_H

#include <QDockWidget>

namespace Ui {
class OHInformation;
}

class OHInformation : public QDockWidget
{
    Q_OBJECT

public:
    explicit OHInformation(QWidget *parent = nullptr);
    ~OHInformation();

private:
    Ui::OHInformation *ui;
};

#endif // OHINFORMATION_H
