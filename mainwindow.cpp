#include "mainwidget.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new MainWidget;
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{

}
