#include "interactions.h"


void Interactions::selectionSortByPrice_increase(QSqlTableModel* database_model) const {
    int rowCount = database_model->rowCount();

    for (int i = 0; i < rowCount - 1; ++i) {
        int minIndex = i;
        int minPrice = database_model->data(database_model->index(i, database_model->fieldIndex("Ціна"))).toInt();

        for (int j = i + 1; j < rowCount; ++j) {
            int currentPrice = database_model->data(database_model->index(j, database_model->fieldIndex("Ціна"))).toInt();

            if (currentPrice < minPrice) { /* increase */
                minIndex = j;
                minPrice = currentPrice;
            }
        }

        if (minIndex != i) {
            for (int column = 0; column < database_model->columnCount(); ++column) {
                QVariant temp = database_model->data(database_model->index(i, column));
                database_model->setData(database_model->index(i, column), database_model->data(database_model->index(minIndex, column)));
                database_model->setData(database_model->index(minIndex, column), temp);
            }
        }
    }
}


void Interactions::selectionSortByPrice_descending(QSqlTableModel* database_model) const {
    int rowCount = database_model->rowCount();

        for (int i = 0; i < rowCount - 1; ++i) {
            int maxIndex = i;
            int maxPrice = database_model->data(database_model->index(i, database_model->fieldIndex("Ціна"))).toInt();

            for (int j = i + 1; j < rowCount; ++j) {
                int currentPrice = database_model->data(database_model->index(j, database_model->fieldIndex("Ціна"))).toInt();

                if (currentPrice > maxPrice) { /* descending */
                    maxIndex = j;
                    maxPrice = currentPrice;
                }
            }

            if (maxIndex != i) {
                for (int column = 0; column < database_model->columnCount(); ++column) {
                    QVariant temp = database_model->data(database_model->index(i, column));
                    database_model->setData(database_model->index(i, column), database_model->data(database_model->index(maxIndex, column)));
                    database_model->setData(database_model->index(maxIndex, column), temp);
                }
            }
        }
}


void Interactions::calculateAveragePrice(Window &window) const {
    QSqlDatabase database = window.getDatabase();
    QSqlQuery query(database);
    query.exec("SELECT AVG(Ціна) FROM CarDealer");

    if (query.next()) {
        double averagePrice = query.value(0).toDouble();
        QString averagePriceString = QString::number(averagePrice, 'f', 2) + " грн";
        QMessageBox::information(nullptr, "Середня вартість", "Середня вартість автомобілів: " + averagePriceString);
    } else {
        QMessageBox::warning(nullptr, "Помилка", "Не вдалося отримати середню вартість автомобілів");
    }
}

void Interactions::convertDbToTxt(const QString &dbFile, const QString &txtFile) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbFile);

    if (!db.open()) {
        qDebug() << "Помилка під час відкриття файлу:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.exec("SELECT * FROM CarDealer");

    QStringList columns;
    for (int i = 0; i < query.record().count(); ++i) {
        columns << query.record().fieldName(i);
    }

    QVector<int> max_lengths(query.record().count(), 0);
    while (query.next()) {
        for (int i = 0; i < query.record().count(); ++i) {
            max_lengths[i] = qMax(max_lengths[i], query.value(i).toString().length());
        }
    }

    QFile file(txtFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Помилка під час відкриття файлу:" << file.errorString();
        return;
    }

    QTextStream out(&file);

    out << '+';
    for (int length : max_lengths) {
        out << '-' << QString(length + 2, '-') << '+';
    }
    out << '\n';

    for (int i = 0; i < columns.size(); ++i) {
        out << "| " << columns.at(i).leftJustified(max_lengths.at(i)) << ' ';
    }
    out << "|\n";

    out << '+';
    for (int length : max_lengths) {
        out << '-' << QString(length + 2, '-') << '+';
    }
    out << '\n';

    query.exec("SELECT * FROM CarDealer");
    while (query.next()) {
        for (int i = 0; i < query.record().count(); ++i) {
            out << "| " << query.value(i).toString().leftJustified(max_lengths.at(i)) << ' ';
        }
        out << "|\n";
    }

    out << '+';
    for (int length : max_lengths) {
        out << '-' << QString(length + 2, '-') << '+';
    }
    out << '\n';

    qDebug() << "Конвертацію успішно завершено!";
}

void Interactions::openTxtFile(const QString &txtFile) {
    QUrl fileUrl = QUrl::fromLocalFile(txtFile);
    if (!QDesktopServices::openUrl(fileUrl)) {
        qDebug() << "Помилка під час відкриття файлу";
    }
}
