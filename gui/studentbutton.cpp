#include "studentbutton.h"

StudentButton::StudentButton(int row, int column, QWidget *parent)
    : QPushButton(parent), row_(row), column_(column), numQ(0), numC(0), numP(0), currentInteraction_(Idle)
{
}

int StudentButton::Row() const
{
    return row_;
}

int StudentButton::Column() const
{
    return column_;
}

void StudentButton::IncrementCount(StudentButton::interaction_t t)
{
    if (t == Questioning) {
        ++numQ;
    } else if (t == Contributing) {
        ++numC;
    } else if (t == Presenting) {
        ++numP;
    }
}
