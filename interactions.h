#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#pragma once

#include "window.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QUrl>


class Interactions {
public:
    void selectionSortByPrice_increase(QSqlTableModel* database_model) const;
    void selectionSortByPrice_descending(QSqlTableModel* database_model) const;

    void calculateAveragePrice(Window &window) const;

    void convertDbToTxt(const QString& dbFile, const QString& txtFile);
    void openTxtFile(const QString &txtFile);
};


#endif // INTERACTIONS_H
