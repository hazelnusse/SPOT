#include <QGridLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QGroupBox>
#include "mainwidget.h"
#include "studentwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    Setup();
    Populate();
}

void MainWidget::Setup()
{
    grid = new QGridLayout(this);
}

void MainWidget::Populate()
{
    teacherButton = new QPushButton(tr("&Teacher"), this);
    teacherButton->setCheckable(true);
    groupButton = new QPushButton(tr("&Group"), this);
    groupButton->setCheckable(true);
    individualButton = new QPushButton(tr("&Individual"), this);
    individualButton->setCheckable(true);

    QGroupBox *groupBox = new QGroupBox;
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(teacherButton);
    hbox->addWidget(groupButton);
    hbox->addWidget(individualButton);
    groupBox->setLayout(hbox);

    // Add Buttons to ButtonGroup manager to ensure exclusivity.
    personButtons = new QButtonGroup(this);
    personButtons->addButton(teacherButton, 0);
    personButtons->addButton(groupButton, 1);
    personButtons->addButton(individualButton, 2);
    // TODO:  Loop over grid of student buttons and add to PersonButtongs to make them all exclusive
    studentWidget = new StudentWidget(7, 7, personButtons, this);

    grid->addWidget(groupBox, 2, 2, 1, 3);
    grid->addWidget(studentWidget, 0, 2, 2, 3);
}
