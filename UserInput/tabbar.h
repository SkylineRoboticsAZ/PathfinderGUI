#ifndef TABBAR_H
#define TABBAR_H

#include <QTabBar>
#include <QDebug>

class TabBar : public QTabBar
{
public:
    TabBar();

    QSize tabSizeHint(int index) const override;
};

#endif // TABBAR_H
