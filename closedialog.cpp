#include "closedialog.h"
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>

CloseDialog::CloseDialog(const QString &notesfile, const QString &interactionsfile,
            QWidget *parent)
    : QDialog(parent)
{
  QLabel *label = new QLabel(this);
  label->setText("Data has been saved to <ul><li>" + notesfile
        + "</li><li>" +  interactionsfile + "</li></ul>");

  QLabel *studentlabel = new QLabel(tr("Number of students:"), this);
  le = new QLineEdit("0", this);
  le->setValidator(new QIntValidator(0, 100, this));
  QHBoxLayout *hl = new QHBoxLayout;
  hl->addWidget(studentlabel);
  hl->addWidget(le);
  
  QPushButton *okbtn = new QPushButton(tr("&Ok"), this);
  QVBoxLayout *layout = new QVBoxLayout;

  layout->addWidget(label);
  layout->addLayout(hl);
  layout->addWidget(okbtn);
  connect(okbtn, SIGNAL(clicked()), this, SLOT(accept()));

  setLayout(layout);
}

void CloseDialog::reject()
{

}

void CloseDialog::accept()
{
  done(le->text().toInt());
}
