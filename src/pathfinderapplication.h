#ifndef PATHFINDERAPPLICATION_H
#define PATHFINDERAPPLICATION_H

#include <QApplication>
#include <QFile>
#include <QFontDatabase>

#include "main_window/mainwindow.h"
#include "main_window/menubar.h"

class PathfinderApplication : public QApplication
{
public:
    PathfinderApplication(int &argc, char **argv);
    virtual ~PathfinderApplication() {}

private:
    MainWindow window_;
    MenuBar menuBar_;

    void loadAppFont();
    void loadStylesheet();
    void configureMenuBar();
};

#endif // PATHFINDERAPPLICATION_H
