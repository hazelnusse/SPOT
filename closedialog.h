#ifndef CLOSEDIALOG_H
#define CLOSEDIALOG_H

#include <QDialog>

class QString;
class QLineEdit;

class CloseDialog : public QDialog
{
  Q_OBJECT
public:
  CloseDialog(const QString &notesfile, const QString &interactionsfile,
              QWidget *parent = 0);

public slots:
  virtual void reject();
  virtual void accept();

private:
  QLineEdit *le;
};
#endif // CLOSEDIALOG_H
