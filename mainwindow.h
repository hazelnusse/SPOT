#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <timestampednote.h>

class QGridLayout;
class QPushButton;
class QButtonGroup;
class QListWidget;
class StudentWidget;
class QLineEdit;
class QFile;
class QCloseEvent;
class QTime;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton *currentButton();

signals:
    void Interaction(const QString &);

public slots:
  void addNoteListItem();
  void TeacherButtonClicked();
  void GroupButtonClicked();
  void AllStudentsButtonClicked();
  void StudentButtonSelected(QPushButton *selected);
  void RecordInteraction(const QString &interaction);
  void RecordNote(const QString &interaction);

protected slots:
  virtual void closeEvent(QCloseEvent *event);

private:
  // Methods
  void Connect();
  void Setup();
  void Populate();
  // Data members
  QGridLayout *grid;
  // Teacher button
  QPushButton *teacherButton;
  // Bottom Right Buttons
  QPushButton *groupButton, *allstudentsButton;
  // Group to manage exclusivity of Bottom Right Buttons and Student Buttons
  QButtonGroup *personButtons;
  QPushButton *currentInteractionButton;
  // Top Right Widget full of student buttons
  StudentWidget *studentWidget;
  // Configuration button
  // QPushButton *configButton;
  // QList to store all the notes
  QList<TimeStampedNote> *notes;
  // QListWidget to display all the notes and their timestamp
  QListWidget *notesListWidget;
  QLineEdit *lineedit;

  QFile *interactionFile, *notesFile;

  // To store the time
  bool initialInteraction;
  QTime *t;
};
#endif // MAINWINDOW_H
