#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#pragma once

#include "window.h"


class Interactions {
public:
    void selectionSortByPrice(QSqlTableModel* database_model);
    void calculateAveragePrice(Window &window);
};


#endif // INTERACTIONS_H
