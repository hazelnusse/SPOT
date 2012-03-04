#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QWidget>

class QGridLayout;
class QPushButton;
class QButtonGroup;
class StudentWidget;

class MainWidget : public QWidget
{
//    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

//signals:
//
//public slots:

private:

    // Methods
    void Setup();
    void Populate();

    // Data members
    QGridLayout *grid;
    // Bottom Right Buttons
    QPushButton *teacherButton, *groupButton, *individualButton;
    // Group to manage exclusivity of Bottom Right Buttons and Student Buttons
    QButtonGroup *personButtons;
    // Top Right Widget full of studen buttons
    StudentWidget * studentWidget;
};

#endif // MAINLAYOUT_H
