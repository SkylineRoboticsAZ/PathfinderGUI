#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include <QApplication>
#include <QDebug>

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MenuBar();

    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MENUBAR_H
