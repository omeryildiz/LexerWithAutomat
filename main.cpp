#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("LexerWithAutomat"));
    QCoreApplication::setApplicationVersion(QStringLiteral("2.0.0"));
    QCoreApplication::setOrganizationName(QStringLiteral("LexerWithAutomat"));

    MainWindow window;
    window.show();

    return app.exec();
}
