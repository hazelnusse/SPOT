#include "configurationdialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QIntValidator>
#include <QDialogButtonBox>

ConfigurationDialog::ConfigurationDialog(QWidget *parent)
    : QDialog(parent), rows_(4), columns_(4)
{
    FileName_ = new QString;
    Setup();
    Connect();
}

QString ConfigurationDialog::FileName()
{
    return *FileName_;
}

int ConfigurationDialog::DesiredRows()
{
    return rows_;
}

int ConfigurationDialog::DesiredColumns()
{
    return columns_;
}

void ConfigurationDialog::Setup()
{
    QIntValidator *iv = new QIntValidator(2, 10, this);
    QLabel *rowlabel = new QLabel("Rows");
    rowedit = new QLineEdit(QString::number(rows_));
    rowedit->setValidator(iv);

    QLabel *columnlabel = new QLabel("Columns");
    columnedit = new QLineEdit(QString::number(columns_));
    columnedit->setValidator(iv);

    QLabel *filenamelabel = new QLabel("Filename");
    filenameedit = new QLineEdit("filename");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(rowlabel, 0, 0, Qt::AlignRight);
    layout->addWidget(rowedit, 0, 1, Qt::AlignLeft);

    layout->addWidget(columnlabel, 1, 0, Qt::AlignRight);
    layout->addWidget(columnedit, 1, 1, Qt::AlignLeft);

    layout->addWidget(filenamelabel, 2, 0, Qt::AlignRight);
    layout->addWidget(filenameedit, 2, 1, Qt::AlignLeft);

    bb = new QDialogButtonBox(QDialogButtonBox::Ok,
                              Qt::Vertical);
    layout->addWidget(bb, 0, 2, 1, 2);

    setLayout(layout);
}

// This is called when escape is pressed or cancel is pressed...
void ConfigurationDialog::reject()
{

}

void ConfigurationDialog::savedata()
{
  rows_ = rowedit->text().toInt();
  columns_ = columnedit->text().toInt();
  FileName_->clear();
  FileName_->insert(0, filenameedit->text());
  accept();
}

void ConfigurationDialog::Connect()
{
    connect(bb, SIGNAL(accepted()), this, SLOT(savedata()));
    connect(bb, SIGNAL(rejected()), this, SLOT(reject()));
}
