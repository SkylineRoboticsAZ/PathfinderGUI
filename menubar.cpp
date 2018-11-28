#include "menubar.h"

MenuBar::MenuBar()
{

}

void MenuBar::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Clicked!";
    //QApplication::focusWidget()->clearFocus();
}
