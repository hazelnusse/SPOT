#ifndef STUDENTBUTTON_H
#define STUDENTBUTTON_H

#include <QPushButton>

class StudentButton : public QPushButton
{
public:
    StudentButton(int row, int column, QWidget *parent);
    int Row() const;
    int Column() const;
    enum interaction_t {Idle, Questioning, Contributing, Presenting};
    void IncrementCount(interaction_t t);
    int QuestioningCount() { return numQ; }
    int ContributingCount() { return numC; }
    int PresentingCount() { return numP; }
    interaction_t currentInteraction() const { return currentInteraction_; }
    void SetCurrentInteraction(interaction_t t) { currentInteraction_ = t; }

private:
    interaction_t currentInteraction_;
    int row_, column_;
    int numQ, numC, numP;
};

#endif // STUDENTBUTTON_H
