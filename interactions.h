#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#pragma once

#include "window.h"


class Interactions {
public:
    void selectionSortByPrice(QSqlTableModel* database_model) const;
    void calculateAveragePrice(Window &window) const;
};


#endif // INTERACTIONS_H
