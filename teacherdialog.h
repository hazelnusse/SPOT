#ifndef TEACHERDIALOG_H
#define TEACHERDIALOG_H

#include <QDialog>

class QPushButton;

class TeacherDialog : public QDialog
{
    Q_OBJECT
public:
    TeacherDialog(QWidget *parent = 0);

private slots:
    void Explaining();
    void Questioning();
    void Waiting();
    void Administrative();

public slots:
  virtual void reject();

private:
    QPushButton *ExplainingButton, *QuestioningButton, *WaitingButton, *AdministrativeButton;
};

#endif // TEACHERDIALOG_H
