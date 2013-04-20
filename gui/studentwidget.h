#ifndef STUDENTLAYOUT_H
#define STUDENTLAYOUT_H

#include <QWidget>

class QGridLayout;
class QButtonGroup;
class StudentButton;
class QPushButton;

class StudentWidget: public QWidget
{
    Q_OBJECT
public:
    explicit StudentWidget(int rows, int cols, QButtonGroup *group, QWidget *parent = 0);
    void setButtonGroup(QButtonGroup & group);

signals:
    void Interaction(const QString &interaction);
    void Note(const QString &note);
    void SelectedStudent(QPushButton *selected);

public slots:
  void UnselectStudent();


private slots:
    void StudentButtonClicked();

private:
    QButtonGroup *group_;
    QGridLayout *grid;
    StudentButton *previousStudent, *currentStudent;
};

#endif // STUDENTLAYOUT_H
