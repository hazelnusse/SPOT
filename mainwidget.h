#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QWidget>
#include <timestampednote.h>

class QGridLayout;
class QPushButton;
class QButtonGroup;
class QListWidget;
class StudentWidget;
class QLineEdit;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    virtual ~MainWidget();
    QPushButton *currentButton();

signals:
    void Interaction(const QString &);

public slots:
    void addNoteListItem();
    void TeacherButtonClicked();
    void GroupButtonClicked();
    void IndividualButtonClicked();
    void StudentButtonSelected(QPushButton *selected);

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
    QPushButton *groupButton, *individualButton;
    // Group to manage exclusivity of Bottom Right Buttons and Student Buttons
    QButtonGroup *personButtons;
    QPushButton *currentInteractionButton;
    // Top Right Widget full of student buttons
    StudentWidget *studentWidget;
    // Configuration button
    QPushButton *configButton;
    // QList to store all the notes
    QList<TimeStampedNote> *notes;
    // QListWidget to display all the notes and their timestamp
    QListWidget *notesListWidget;
    QLineEdit *lineedit;

};

#endif // MAINLAYOUT_H
