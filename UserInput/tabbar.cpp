#include "tabbar.h"

TabBar::TabBar(QWidget *parent) : QTabBar(parent)
{

}

QSize TabBar::tabSizeHint(int index) const
{
    const int divide = width() % count();
    const int tabWidth = width() / count();

    if (divide == 0) {
        return QSize(tabWidth, height());
    } else if (index == count() - 1) {
        return QSize(tabWidth + divide, height());
    } else {
        return QSize(tabWidth - divide, height());
    }
}

