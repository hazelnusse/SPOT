#include <QPushButton>
#include <QHBoxLayout>

#include "allstudentsdialog.h"


AllStudentsDialog::AllStudentsDialog(QWidget *parent)
    : QDialog(parent)
{
    RespondingButton = new QPushButton(tr("&Responding"));
    connect(RespondingButton, SIGNAL(clicked()), this, SLOT(Responding()));
    IndividuallyWorkingButton= new QPushButton(tr("&Individually Working"));
    connect(IndividuallyWorkingButton, SIGNAL(clicked()), this, SLOT(IndividuallyWorking()));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(RespondingButton);
    layout->addWidget(IndividuallyWorkingButton);

    setLayout(layout);
}

void AllStudentsDialog::Responding()
{
    done(1);
}

void AllStudentsDialog::IndividuallyWorking()
{
    done(2);
}

void AllStudentsDialog::reject()
{

}
