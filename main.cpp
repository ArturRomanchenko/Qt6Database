#include "window.h"
#include "themes.h"
#include <QApplication>

//int main(int argc, char** argv) {
    QApplication application(argc, argv);

    Window w;

    QMenu* themeMenu = Themes::createThemeMenu();
    w.menuBar()->addMenu(themeMenu);

    w.setWindowTitle("База Данных: Автосалон");
    w.show();

    return application.exec();
}
