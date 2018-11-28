#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget();
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);
    centralLayout->setMargin(0);
    centralLayout->setSpacing(0);

    input_ = new UserInput();
    graphViewport_ = new GraphViewport();

    centralLayout->addWidget(input_);
    centralLayout->addWidget(graphViewport_, 1);

    input_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    graphViewport_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setCentralWidget(centralWidget);
}
