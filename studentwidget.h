#ifndef STUDENTLAYOUT_H
#define STUDENTLAYOUT_H

#include <QWidget>

class QGridLayout;
class QButtonGroup;

class StudentWidget: public QWidget
{
//    Q_OBJECT
public:
    explicit StudentWidget(int rows, int cols, QButtonGroup *group, QWidget *parent = 0);
    void setButtonGroup(QButtonGroup & group);

//signals:
//
//public slots:
private:
    QGridLayout * grid;
};

#endif // STUDENTLAYOUT_H
