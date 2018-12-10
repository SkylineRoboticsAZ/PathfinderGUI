#include "pathfinderapplication.h"

PathfinderApplication::PathfinderApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{
    setStyle(QStringLiteral("Windowsvista"));
    loadAppFont();
    loadStylesheet();

    configureMenuBar();

    window_.setMenuBar(&menuBar_);
    window_.resize(1024, 600);
    window_.show();
}

void PathfinderApplication::loadAppFont()
{
    QFontDatabase database;

    const QString idealFont = QStringLiteral("Cambria");
    if (database.hasFamily(idealFont)) {
        setFont(QFont(idealFont, 12));
    } else {
        const int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/Oswald-Light.ttf"));
        const QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        setFont(QFont(fontFamily, 12));
    }
}

void PathfinderApplication::loadStylesheet()
{
    QFile file(QStringLiteral(":/stylesheet.qss"));
    file.open(QFile::ReadOnly);
    const QString styleSheet = QLatin1String(file.readAll());
    file.close();
    setStyleSheet(styleSheet);
}

void PathfinderApplication::configureMenuBar()
{
}
