#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include <QApplication>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MenuBar();

private:
    QMenu *exportMenu_;
    QAction *exportBinaryAction_,
            *exportCsvAction_;
};

#endif // MENUBAR_H
