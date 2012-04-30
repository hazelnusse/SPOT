#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>

class QString;
class QDialogButtonBox;
class QLineEdit;

class ConfigurationDialog : public QDialog
{
  Q_OBJECT
public:
  ConfigurationDialog(QWidget *parent = 0);
  QString FileName();
  int DesiredRows();
  int DesiredColumns();

public slots:
  virtual void reject();
  virtual void savedata();
  

private:
  void Setup();
  void Connect();
  int rows_, columns_;
  QString *FileName_;
  QDialogButtonBox *bb;

  QLineEdit *rowedit, *columnedit, *filenameedit;
};
#endif // CONFIGURATIONDIALOG_H
