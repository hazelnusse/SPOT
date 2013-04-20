#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include <QDialog>

class QPushButton;

class StudentDialog : public QDialog
{
    Q_OBJECT
public:
    StudentDialog(QWidget *parent = 0);

public slots:
    virtual void reject();

private slots:
    void Questioning();
    void Contributing();
    void Presenting();
private:
    QPushButton *QuestioningButton, *ContributingButton, *PresentingButton;
};

#endif // STUDENTDIALOG_H
