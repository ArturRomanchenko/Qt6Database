#include "./ui_interface.h"
#include "window.h"
#include "interactions.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QSqlError>
#include <QtSql>
#include <QVBoxLayout>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("./CarDealer.db");

    if (database.open()) {
        qDebug("open database!");
    } else {
        qDebug("Not open database!");
    }


    /* creating a database table */
    database_query = new QSqlQuery(database);
    database_query->exec("CREATE TABLE CarDealer(ID INTEGER PRIMARY KEY AUTOINCREMENT"
                         ", Модель автомобіля TEXT"
                         ", Рік випуску INT"
                         ", Колір TEXT"
                         ", Ціна автомобіля INT"
                         ", Прізвище клієнта TEXT);");

    database_model = new QSqlTableModel(this, database);
    database_model->setTable("CarDealer");
    database_model->select();

    ui->tableView->setModel(database_model);

    /* hide the 'ID' column from the database */
    ui->tableView->hideColumn(database_model->fieldIndex("ID"));

    /* changing the standard output sizes of table columns */
    ui->tableView->setColumnWidth(database_model->fieldIndex("Модель"), 200);
    ui->tableView->setColumnWidth(database_model->fieldIndex("Рік"), 200);
    ui->tableView->setColumnWidth(database_model->fieldIndex("Колір"), 200);
    ui->tableView->setColumnWidth(database_model->fieldIndex("Ціна"), 200);
    ui->tableView->setColumnWidth(database_model->fieldIndex("Прізвище"), 200);

    connect(ui->buttonUPDATE, &QPushButton::clicked, this, &Window::on_buttonUPDATE_clicked);
}


Window::~Window() {
    delete ui;
}


void Window::updateDatabase() {
    database_model->select();
}


void Window::on_buttonADD_clicked() {
    database_model->insertRow(database_model->rowCount());
}


void Window::on_buttonDELETE_clicked() {
    QMessageBox message(QMessageBox::Warning, "Попередження"
                        , "Ви дійсно хочете видалити рядок? Дія не оборотна!"
                        , QMessageBox::Yes | QMessageBox::No
                        , this);

    message.setDefaultButton(QMessageBox::No);

    int answer = message.exec();
    if (answer == QMessageBox::Yes) {
        database_model->removeRow(row_database);
    }
}


void Window::on_tableView_clicked(const QModelIndex &index) {
    row_database = index.row();
}


void Window::on_buttonUPDATE_clicked() {
    database_model->select();
    database_model->setSort(database_model->fieldIndex("ID"), Qt::AscendingOrder);
    database_model->select();

    ui->statusbar->showMessage("Оновлення екрану...", 1000);
}


void Window::on_Sortted_triggered() {
    Interactions sort;
    sort.selectionSortByPrice_increase(database_model);
    ui->tableView->sortByColumn(database_model->fieldIndex("Ціна"), Qt::AscendingOrder);

    ui->statusbar->showMessage("Сортування бази даних...", 2000);
}


void Window::on_Sortted_2_triggered() {
    Interactions sort;
    sort.selectionSortByPrice_descending(database_model);

    ui->tableView->sortByColumn(database_model->fieldIndex("Ціна"), Qt::DescendingOrder);
    ui->statusbar->showMessage("Сортування бази даних...", 2000);
}


void Window::on_Average_triggered() {
    ui->statusbar->showMessage("Відображення середньої ціни машин в автосалоні", 2000);
    Interactions interactions;
    interactions.calculateAveragePrice(*this);
}


void Window::on_Display_triggered() {
    ui->statusbar->showMessage("Пошук моделі...", 4000);

    bool ok;
    QString model = QInputDialog::getText(this, tr("Введіть модель автомобіля")
                                              , tr("Модель:"), QLineEdit::Normal, ""
                                              , &ok);
    if (!ok || model.isEmpty()) {
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM CarDealer WHERE Модель = ?");
    query.addBindValue(model);
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString result = QString("Дані про автомобіль:\n"
                                "Модель: %1\n"
                                "Рік випуску: %2\n"
                                "Колір: %3\n"
                                "Ціна грн: %4\n"
                                "Прізвище клієнта: %5\n")
                                .arg(query.value("Модель").toString())
                                .arg(query.value("Рік").toString())
                                .arg(query.value("Колір").toString())
                                .arg(query.value("Ціна").toString())
                                .arg(query.value("Прізвище").toString());


        QMessageBox::information(this, tr("Інформація про автомобіль"), result);
    } else {
        QMessageBox::information(this, tr("Інформація про автомобіль"), tr("Автомобіль з такою моделлю не знайдено."));
    }
}


void Window::on_About_triggered() {
    ui->statusbar->showMessage("Інформація про розробників", 4000);

    QMessageBox::information(this, "Про розробників:",
                             "Розробник цього ПЗ - Романченко Артур,"
                             "\nСтуден ВСП Павлоградський фаховий коледж НТУ ''ДП''\n Групи KI-2-21");
}


void Window::on_Exit_triggered() {
    QApplication::quit();
}

void Window::on_open_triggered() {
    Interactions convert;

    QString dbFile = "CarDealer.db";
    QString txtFile = "DataBase.txt";

    convert.convertDbToTxt(dbFile, txtFile);

    convert.openTxtFile(txtFile);
    ui->statusbar->showMessage("Відкриття файлу бази даних", 4000);
}
