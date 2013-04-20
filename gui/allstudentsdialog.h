#ifndef ALSTUDENTSDIALOG_H
#define ALSTUDENTSDIALOG_H

#include <QDialog>

class QPushButton;

class AllStudentsDialog : public QDialog
{
  Q_OBJECT
public:
  AllStudentsDialog(QWidget *parent = 0);

private slots:
  void Responding();
  void IndividuallyWorking();

public slots:
  virtual void reject();

private:
  QPushButton *RespondingButton, *IndividuallyWorkingButton;
};
#endif // ALLSTUDENTSDIALOG_H
