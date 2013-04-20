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
#include "mainwindow.h"

QString formText(StudentButton::interaction_t i, int Q, int C, int P);


StudentWidget::StudentWidget(int rows, int cols, QButtonGroup *group, QWidget *parent) :
    QWidget(parent), group_(group)
{
    grid = new QGridLayout(this);

    QSizePolicy sizepolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    grid->setSpacing(0);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            StudentButton *b = new StudentButton(i, j, this);
            b->setCheckable(true);
            b->setSizePolicy(sizepolicy);
            b->SetCurrentInteraction(StudentButton::Idle);
            connect(b, SIGNAL(clicked()), this, SLOT(StudentButtonClicked()));
            grid->addWidget(b, i, j, 1, 1);
            group_->addButton(b, 3 + i*cols + j);
        }
    }
    previousStudent = currentStudent = NULL;
}

void StudentWidget::StudentButtonClicked()
{
  previousStudent = currentStudent;
  currentStudent = static_cast<StudentButton *>(sender());
  MainWindow *mw = static_cast<MainWindow *>(parent());

  StudentDialog *d = new StudentDialog(this);
  int rv = d->exec();
  switch (rv) {
  case 1:
      if (mw->currentButton() != currentStudent) {
          currentStudent->IncrementCount(StudentButton::Questioning);
          emit Interaction("SQ" + QString::number(currentStudent->Row()) + QString::number(currentStudent->Column()));
      }
      currentStudent->SetCurrentInteraction(StudentButton::Questioning);
      currentStudent->setText(formText(StudentButton::Questioning,
                                       currentStudent->QuestioningCount(),
                                       currentStudent->ContributingCount(),
                                       currentStudent->PresentingCount()));
      emit SelectedStudent(currentStudent);
      break;
  case 2:
      if (mw->currentButton() != currentStudent) {
          currentStudent->IncrementCount(StudentButton::Contributing);
          emit Interaction("SC" + QString::number(currentStudent->Row()) + QString::number(currentStudent->Column()));
      }
      currentStudent->SetCurrentInteraction(StudentButton::Contributing);
      currentStudent->setText(formText(StudentButton::Contributing,
                                       currentStudent->QuestioningCount(),
                                       currentStudent->ContributingCount(),
                                       currentStudent->PresentingCount()));
      emit SelectedStudent(currentStudent);
      break;
  case 3:
      if (mw->currentButton() != currentStudent) {
          currentStudent->IncrementCount(StudentButton::Presenting);
          emit Interaction("SP" + QString::number(currentStudent->Row()) + QString::number(currentStudent->Column()));
      }
      currentStudent->SetCurrentInteraction(StudentButton::Presenting);
      currentStudent->setText(formText(StudentButton::Presenting,
                                       currentStudent->QuestioningCount(),
                                       currentStudent->ContributingCount(),
                                       currentStudent->PresentingCount()));
      emit SelectedStudent(currentStudent);
      break;
  }

  if (previousStudent && (previousStudent != currentStudent)) {
      previousStudent->setText(formText(StudentButton::Idle,
                                        previousStudent->QuestioningCount(),
                                        previousStudent->ContributingCount(),
                                        previousStudent->PresentingCount()));
      previousStudent->SetCurrentInteraction(StudentButton::Idle);
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


void StudentWidget::UnselectStudent()
{
  if (currentStudent) {
    currentStudent->setText(formText(StudentButton::Idle,
                                      currentStudent->QuestioningCount(),
                                      currentStudent->ContributingCount(),
                                      currentStudent->PresentingCount()));
  }
  currentStudent = NULL;
}
