#include <QActionGroup>
#include <QButtonGroup>
#include <QDebug>
#include <QToolButton>
#include <QMenu>
#include <QGridLayout>
#include <QSizePolicy>
#include "studentbutton.h"
#include "studentwidget.h"
#include "studentdialog.h"

QString formText(StudentButton::interaction_t i, int Q, int C, int P);


StudentWidget::StudentWidget(QButtonGroup *group, QWidget *parent) :
    QWidget(parent), group_(group)
{
    int rows(7), cols(5);
    grid = new QGridLayout(this);

    QSizePolicy sizepolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    grid->setSpacing(0);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            StudentButton *b = new StudentButton(i, j, this);
            b->setCheckable(true);
            b->setSizePolicy(sizepolicy);
            connect(b, SIGNAL(clicked()), this, SLOT(StudentButtonClicked()));
            grid->addWidget(b, i, j, 1, 1);
            group_->addButton(b, 3 + i*cols + j);
        }
    }
    previousStudent = currentStudent = NULL;
}

void StudentWidget::StudentButtonClicked()
{
    StudentButton *tmp = previousStudent;  // Save just in case we need to revert
    previousStudent = currentStudent;
    currentStudent = static_cast<StudentButton *>(sender());

    StudentDialog *d = new StudentDialog(this);
    int rv = d->exec();
    switch (rv) {
    case 0: // Dialog cancelled
        // The next three lines are a little hack to allow the button to be unselected from the buttonGroup.
        group_->removeButton(currentStudent);
        currentStudent->setChecked(false);
        group_->addButton(currentStudent, 3 + currentStudent->Row()*5 + currentStudent->Column());

        // Now we want to make sure the previously selected button is checked.
        currentStudent = previousStudent;
        if (previousStudent) {
            previousStudent->setChecked(true);
        }
        previousStudent = tmp;
        break;
    case 1:
        if (currentStudent->currentInteraction() != StudentButton::Questioning) {
            currentStudent->IncrementCount(StudentButton::Questioning);
            currentStudent->SetCurrentInteraction(StudentButton::Questioning);
        }
        currentStudent->setText(formText(StudentButton::Questioning,
                                         currentStudent->QuestioningCount(),
                                         currentStudent->ContributingCount(),
                                         currentStudent->PresentingCount()));
        emit Interaction("SQ" + QString::number(currentStudent->Row()) + QString::number(currentStudent->Column()));
        emit SelectedStudent(currentStudent);
        break;
    case 2:
        if (currentStudent->currentInteraction() != StudentButton::Contributing) {
            currentStudent->IncrementCount(StudentButton::Contributing);
            currentStudent->SetCurrentInteraction(StudentButton::Contributing);
        }
        currentStudent->setText(formText(StudentButton::Contributing,
                                         currentStudent->QuestioningCount(),
                                         currentStudent->ContributingCount(),
                                         currentStudent->PresentingCount()));
        emit Interaction("SC" + QString::number(currentStudent->Row()) + QString::number(currentStudent->Column()));
        emit SelectedStudent(currentStudent);
        break;
    case 3:
        if (currentStudent->currentInteraction() != StudentButton::Presenting) {
            currentStudent->IncrementCount(StudentButton::Presenting);
            currentStudent->SetCurrentInteraction(StudentButton::Presenting);
        }
        currentStudent->setText(formText(StudentButton::Presenting,
                                         currentStudent->QuestioningCount(),
                                         currentStudent->ContributingCount(),
                                         currentStudent->PresentingCount()));
        emit Interaction("SP" + QString::number(currentStudent->Row()) + QString::number(currentStudent->Column()));
        emit SelectedStudent(currentStudent);
        break;
    }

    if (previousStudent && (previousStudent != currentStudent)) {
        previousStudent->setText(formText(StudentButton::Idle,
                                          previousStudent->QuestioningCount(),
                                          previousStudent->ContributingCount(),
                                          previousStudent->PresentingCount()));
    }

}

QString formText(StudentButton::interaction_t i, int Q, int C, int P)
{
    QString text;
    if (i == StudentButton::Idle) {
        text += " \n";
    }
    if (i == StudentButton::Questioning) {
        text += "Q\n";
    }
    if (i == StudentButton::Contributing) {
        text += "C\n";
    }
    if (i == StudentButton::Presenting) {
        text += "P\n";
    }
    //return text + "Q:" + QString::number(Q) + "C:" + QString::number(C) + "P:" + QString::number(P);
    return text + QString::number(Q+C+P);
}
