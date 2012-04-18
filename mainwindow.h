#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class MainWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void RecordInteraction(const QString &interaction);
    void RecordNote(const QString &interaction);

private:
    MainWidget *mainWidget;
};
#endif // MAINWINDOW_H
