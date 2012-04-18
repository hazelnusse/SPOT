#include "mainwidget.h"
#include "mainwindow.h"
#include <QDebug>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //LogFile = openLogFile();
    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::RecordInteraction(const QString &interaction)
{
    qDebug() << QTime::currentTime().toString() + " " + interaction;
}

void MainWindow::RecordNote(const QString &interaction)
{
}
