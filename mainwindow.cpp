// #include "mainwidget.h"
#include "mainwindow.h"
#include "studentwidget.h"
#include "timestampednote.h"
#include "teacherdialog.h"
#include "configurationdialog.h"

#include <QTime>
#include <QFile>
#include <QDebug>
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
#include <QTextStream>
#include <QCloseEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    Setup();
    Populate();
    Connect();
    //LogFile = openLogFile();
    // mainWidget = new MainWidget(this);
    // setCentralWidget(mainWidget);
}

void MainWindow::Connect()
{
  QObject::connect(lineedit, SIGNAL(returnPressed()),
                   this, SLOT(addNoteListItem()));
  QObject::connect(studentWidget, SIGNAL(Interaction(const QString &)),
                   this, SLOT(RecordInteraction(const QString &)));
  QObject::connect(this, SIGNAL(Interaction(QString)),
                   this, SLOT(RecordInteraction(const QString &)));
  QObject::connect(studentWidget, SIGNAL(SelectedStudent(QPushButton*)),
                   this, SLOT(StudentButtonSelected(QPushButton*)));

  QObject::connect(teacherButton, SIGNAL(clicked()), this->studentWidget, SLOT(UnselectStudent()));
  QObject::connect(groupButton, SIGNAL(clicked()), this->studentWidget, SLOT(UnselectStudent()));
  QObject::connect(individualButton, SIGNAL(clicked()), this->studentWidget, SLOT(UnselectStudent()));
}

void MainWindow::Setup()
{
    grid = new QGridLayout;
    currentInteractionButton = NULL;
    interactionFile = new QFile(this);
    notesFile = new QFile(this);
}

void MainWindow::Populate()
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

    // configButton = new QPushButton(tr("&Configuration"), this);

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

    // Pop up the dialog to obtain: rows, columns, filename prefix
    ConfigurationDialog *d = new ConfigurationDialog;
    d->exec();
    interactionFile->setFileName(d->FileName() + "_interactions.txt");
    interactionFile->open(QIODevice::WriteOnly | QIODevice::Text);
    notesFile->setFileName(d->FileName() + "_notes.txt");
    notesFile->open(QIODevice::WriteOnly | QIODevice::Text);

    // Group of buttons representing all students
    studentWidget = new StudentWidget(d->DesiredRows(), d->DesiredColumns(), personButtons, this);

    grid->addWidget(notesListWidget, 0, 0, 2, 2);
    grid->addWidget(noteBox, 2, 0, 1, 2);
    // grid->addWidget(configButton, 2, 0, 1, 2);
    grid->addWidget(studentWidget, 0, 2, 2, 1);
    grid->addWidget(personSelectionBox, 2, 2, 1, 1);

    QWidget *widget = new QWidget(this);
    widget->setLayout(grid);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
  delete notes;
}

void MainWindow::addNoteListItem()
{
    notes->append(TimeStampedNote(QTime::currentTime().toString(),
                                  lineedit->text()));
    notesListWidget->addItem(notes->back().toString());
    RecordNote(notes->back().toString());
    lineedit->clear();
}

void MainWindow::RecordInteraction(const QString &interaction)
{
  QTextStream s(interactionFile);
  s << QTime::currentTime().toString() + " " + interaction << '\n';
}

void MainWindow::RecordNote(const QString &interaction)
{
  QTextStream s(notesFile);
  s << interaction << '\n';
}

void MainWindow::TeacherButtonClicked()
{
    TeacherDialog *d = new TeacherDialog(this);
    int rv = d->exec();
    switch (rv) {
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

void MainWindow::GroupButtonClicked()
{
    emit Interaction("G");
    currentInteractionButton = groupButton;
}

void MainWindow::IndividualButtonClicked()
{
    emit Interaction("I");
    currentInteractionButton = individualButton;
}

void MainWindow::StudentButtonSelected(QPushButton * selected)
{
    currentInteractionButton = selected;
}

QPushButton *MainWindow::currentButton()
{
    return currentInteractionButton;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  QMessageBox box;
  box.setText("Data has been saved to <ul><li>" + notesFile->fileName()
        + "</li><li>" +  interactionFile->fileName() + "</li></ul>");
  box.exec();
  event->accept();
}
