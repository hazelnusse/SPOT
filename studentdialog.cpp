#include "studentdialog.h"
#include <QHBoxLayout>
#include <QPushButton>
StudentDialog::StudentDialog(QWidget *parent)
    : QDialog(parent)
{
    QuestioningButton = new QPushButton(tr("&Questioning"));
    connect(QuestioningButton, SIGNAL(clicked()), this, SLOT(Questioning()));
    ContributingButton = new QPushButton(tr("&Contributing"));
    connect(ContributingButton, SIGNAL(clicked()), this, SLOT(Contributing()));
    PresentingButton = new QPushButton(tr("&Presenting"));
    connect(PresentingButton, SIGNAL(clicked()), this, SLOT(Presenting()));


    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(QuestioningButton);
    layout->addWidget(ContributingButton);
    layout->addWidget(PresentingButton);

    setLayout(layout);

}

void StudentDialog::Questioning()
{
    done(1);
}

void StudentDialog::Contributing()
{
    done(2);
}

void StudentDialog::Presenting()
{
    done(3);
}
