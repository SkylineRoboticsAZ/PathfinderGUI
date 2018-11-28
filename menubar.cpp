#include "menubar.h"

MenuBar::MenuBar()
{
    setFocusPolicy(Qt::ClickFocus);

    exportMenu_ = new QMenu(QStringLiteral("Export"), this);

    exportBinaryAction_ = new QAction(QStringLiteral("Export to Binary File"), exportMenu_);
    exportCsvAction_ = new QAction(QStringLiteral("Export to CSV File"), exportMenu_);

    exportMenu_->addAction(exportBinaryAction_);
    exportMenu_->addAction(exportCsvAction_);

    addMenu(exportMenu_);
}
