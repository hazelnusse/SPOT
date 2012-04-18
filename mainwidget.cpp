#include <QGridLayout>
#include <QPushButton>
#include <QToolButton>
#include <QAbstractAnimation>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTime>
#include "mainwidget.h"
#include "studentwidget.h"
#include "timestampednote.h"
#include "teacherdialog.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    Setup();
    Populate();
    Connect();
}

void MainWidget::Connect()
{
    QObject::connect(lineedit, SIGNAL(returnPressed()),
            this, SLOT(addNoteListItem()));
    QObject::connect(studentWidget, SIGNAL(Interaction(const QString &)),
                     this->parent(), SLOT(RecordInteraction(const QString &)));
    QObject::connect(this, SIGNAL(Interaction(QString)),
                     this->parent(), SLOT(RecordInteraction(const QString &)));
    QObject::connect(studentWidget, SIGNAL(SelectedStudent(QPushButton*)),
                     this, SLOT(StudentButtonSelected(QPushButton*)));
}

void MainWidget::addNoteListItem()
{
    notes->append(TimeStampedNote(QTime::currentTime().toString(),
                                  lineedit->text()));
    notesListWidget->addItem(notes->back().toString());
    lineedit->clear();
}

void MainWidget::TeacherButtonClicked()
{
    TeacherDialog *d = new TeacherDialog(this);
    int rv = d->exec();
    switch (rv) {
    case 0:  // Dialog cancelled
        personButtons->removeButton(teacherButton);
        teacherButton->setChecked(false);
        personButtons->addButton(teacherButton, 0);
        if (currentInteractionButton)
            currentInteractionButton->setChecked(true);
        break;
    case 1:
        emit Interaction("TE");
        currentInteractionButton = teacherButton;
        break;
    case 2:
        emit Interaction("TQ");
        currentInteractionButton = teacherButton;
        break;
    case 3:
        emit Interaction("TW");
        currentInteractionButton = teacherButton;
        break;
    case 4:
        emit Interaction("TA");
        currentInteractionButton = teacherButton;
        break;
    default:
        break;
    }
}

void MainWidget::GroupButtonClicked()
{
    emit Interaction("G");
    currentInteractionButton = groupButton;
}

void MainWidget::IndividualButtonClicked()
{
    emit Interaction("I");
    currentInteractionButton = individualButton;
}

void MainWidget::StudentButtonSelected(QPushButton * selected)
{
    currentInteractionButton = selected;
}

void MainWidget::Setup()
{
    grid = new QGridLayout(this);
    currentInteractionButton = NULL;
}

void MainWidget::Populate()
{
    notes = new QList<TimeStampedNote>();

    // Add the list widget
    notesListWidget = new QListWidget();
    // add the label and line edit
    lineedit = new QLineEdit;
    QLabel *label = new QLabel(tr("Add &note:"));
    label->setBuddy(lineedit);
    QHBoxLayout *notelayout = new QHBoxLayout;
    notelayout->addWidget(label);
    notelayout->addWidget(lineedit);
    QGroupBox *noteBox = new QGroupBox;
    noteBox->setFlat(true);
    noteBox->setLayout(notelayout);

    configButton = new QPushButton(tr("&Configuration"), this);

    teacherButton = new QPushButton(this);
    teacherButton->setText(tr("&Teacher"));
    teacherButton->setCheckable(true);
    QObject::connect(teacherButton, SIGNAL(clicked()), this, SLOT(TeacherButtonClicked()));

    groupButton = new QPushButton(tr("&Group"), this);
    groupButton->setCheckable(true);
    QObject::connect(groupButton, SIGNAL(clicked()), this, SLOT(GroupButtonClicked()));

    individualButton = new QPushButton(tr("&Individual"), this);
    individualButton->setCheckable(true);
    QObject::connect(individualButton, SIGNAL(clicked()), this, SLOT(IndividualButtonClicked()));

    QGroupBox *personSelectionBox = new QGroupBox;
    personSelectionBox->setFlat(true);
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(teacherButton);
    hbox->addWidget(groupButton);
    hbox->addWidget(individualButton);
    personSelectionBox->setLayout(hbox);

    // Add Buttons to ButtonGroup manager to ensure exclusivity.
    personButtons = new QButtonGroup(this);
    personButtons->addButton(teacherButton, 0);
    personButtons->addButton(groupButton, 1);
    personButtons->addButton(individualButton, 2);

    // Group of buttons representing all students
    studentWidget = new StudentWidget(personButtons, this);

    grid->addWidget(notesListWidget, 0, 0, 1, 2);
    grid->addWidget(noteBox, 1, 0, 1, 2);
    grid->addWidget(configButton, 2, 0, 1, 2);
    grid->addWidget(studentWidget, 0, 2, 2, 1);
    grid->addWidget(personSelectionBox, 2, 2, 1, 1);
}

MainWidget::~MainWidget()
{
    delete notes;
}

QPushButton *MainWidget::currentButton()
{
    return currentInteractionButton;
}
