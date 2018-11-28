#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>

#include "UserInput/userinput.h"
#include "GraphViewport/graphviewport.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    UserInput *input_;
    GraphViewport *graphViewport_;
};

#endif // MAINWINDOW_H
