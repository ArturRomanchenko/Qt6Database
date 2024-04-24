#ifndef WINDOW_H
#define WINDOW_H

#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlRecord>
#include <QFile>
#include <QTextStream>


QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE


class Window : public QMainWindow {
    Q_OBJECT


public:
    Window(QWidget *parent = nullptr);
    ~Window();


private slots:
    /* при натисканні знаходить курсор у вікні */
    void on_tableView_clicked(const QModelIndex &index);

    /* кнопки в програмі */
    void on_buttonADD_clicked();
    void on_buttonDELETE_clicked();
    void on_buttonUPDATE_clicked();

    /* функції в меню */
    void on_Sortted_triggered();
    void on_Average_triggered();
    void on_Display_triggered();
    void on_About_triggered();
    void on_Exit_triggered();
    void on_open_triggered();

    void on_Sortted_2_triggered();

private:
    Ui::Window *ui;
    QSqlDatabase database;
    QSqlQuery* database_query;
    QSqlTableModel* database_model;
    /* номер поточної строки */
    int row_database;


public slots:
    void updateDatabase();


public:
    QSqlDatabase getDatabase() const { return database; }
};


#endif // WINDOW_H
