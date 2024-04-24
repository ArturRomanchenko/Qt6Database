#include "themes.h"
#include <QApplication>
#include <QIcon>


bool Themes::isDarkTheme = false;
Themes::Themes(QObject *parent) : QObject(parent) {}


void Themes::applyLightTheme() {
    if (isDarkTheme) {
        QPalette lightPalette;
        qApp->setPalette(lightPalette);
        isDarkTheme = false;
    }
}


void Themes::applyDarkTheme() {
    if (!isDarkTheme) {
        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);
        qApp->setPalette(darkPalette);
        isDarkTheme = true;
    }
}


QMenu* Themes::createThemeMenu() {
    QMenu* themeMenu = new QMenu("Тема");

    QAction* lightThemeAction = new QAction("Світла", themeMenu);
    lightThemeAction->setIcon(QIcon(":/image/resurces/themes/light-theme.png"));
    themeMenu->addAction(lightThemeAction);

    QAction* darkThemeAction = new QAction("Темна", themeMenu);
    darkThemeAction->setIcon(QIcon(":/image/resurces/themes/dark-theme.png"));
    themeMenu->addAction(darkThemeAction);

    QObject::connect(lightThemeAction, &QAction::triggered, &Themes::applyLightTheme);
    QObject::connect(darkThemeAction, &QAction::triggered, &Themes::applyDarkTheme);

    return themeMenu;
}

