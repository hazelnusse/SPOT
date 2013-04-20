#include <QPushButton>
#include <QHBoxLayout>

#include "teacherdialog.h"


TeacherDialog::TeacherDialog(QWidget *parent)
    : QDialog(parent)
{
    ExplainingButton = new QPushButton(tr("&Explaining"));
    connect(ExplainingButton, SIGNAL(clicked()), this, SLOT(Explaining()));
    QuestioningButton = new QPushButton(tr("&Questioning"));
    connect(QuestioningButton, SIGNAL(clicked()), this, SLOT(Questioning()));
    RespondingButton = new QPushButton(tr("&Responding"));
    connect(RespondingButton, SIGNAL(clicked()), this, SLOT(Responding()));
    WaitingButton = new QPushButton(tr("&Waiting"));
    connect(WaitingButton, SIGNAL(clicked()), this, SLOT(Waiting()));
    AdministrativeButton = new QPushButton(tr("&Administrative"));
    connect(AdministrativeButton, SIGNAL(clicked()), this, SLOT(Administrative()));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(ExplainingButton);
    layout->addWidget(QuestioningButton);
    layout->addWidget(RespondingButton);
    layout->addWidget(WaitingButton);
    layout->addWidget(AdministrativeButton);

    setLayout(layout);
}

void TeacherDialog::Explaining()
{
    done(1);
}

void TeacherDialog::Questioning()
{
    done(2);
}

void TeacherDialog::Responding()
{
    done(3);
}

void TeacherDialog::Waiting()
{
    done(4);
}

void TeacherDialog::Administrative()
{
    done(5);
}


void TeacherDialog::reject()
{

}
