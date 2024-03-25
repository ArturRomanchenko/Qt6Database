#ifndef THEMES_H
#define THEMES_H

#include <QObject>
#include <QPalette>
#include <QMenu>
#include <QMenuBar>


class Themes : public QObject {
    Q_OBJECT
public:
    explicit Themes(QObject *parent = nullptr);
    static void applyLightTheme();
    static void applyDarkTheme();
    static QMenu* createThemeMenu();
private:
    static bool isDarkTheme;
};

#endif // THEMES_H
