#include <QButtonGroup>
#include <QPushButton>
#include <QGridLayout>
#include "studentwidget.h"

StudentWidget::StudentWidget(int rows, int cols, QButtonGroup *group, QWidget *parent) :
    QWidget(parent)
{
    grid = new QGridLayout(this);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QPushButton *b = new QPushButton(this);
            b->setCheckable(true);
            grid->addWidget(b, i, j, 1, 1);
            group->addButton(b, 3 + i*cols + j);
        }
    }
}
