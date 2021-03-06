#ifndef PATHFINDERAPPLICATION_H
#define PATHFINDERAPPLICATION_H

#include <QApplication>
#include <QFile>
#include <QFontDatabase>

#include "mainwindow.h"
#include "menubar.h"

class PathfinderApplication : public QApplication
{
public:
    PathfinderApplication(int &argc, char **argv);

private:
    MainWindow window_;
    QMenuBar *menuBar_;

    void loadAppFont();
    void loadStylesheet();
    void configureMenuBar();
};

#endif // PATHFINDERAPPLICATION_H
