#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>

class QString;

class ConfigurationDialog : public QDialog
{
    Q_OBJECT
public:
    ConfigurationDialog(QWidget *parent = 0);
    QString FileName();
    int DesiredRows();
    int DesiredColumns();
private:
    int rows_, columns_;
    QString *FileName_;


};

#endif // CONFIGURATIONDIALOG_H
