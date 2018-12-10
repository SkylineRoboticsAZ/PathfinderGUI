#include "graphviewport.h"

GraphViewport::GraphViewport(QWidget *parent) : QWidget(parent)
{
    QPalette palette = QPalette();
    palette.setColor(QPalette::Background, QColor(QStringLiteral("#595959")));
    setAutoFillBackground(true);
    setPalette(palette);
}
