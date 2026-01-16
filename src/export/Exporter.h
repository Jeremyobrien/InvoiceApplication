#pragma once
#include <vector>
#include <QString>
#include "models/Invoice.h"
#include "models/Expense.h"

class Exporter
{
public:
    virtual ~Exporter() = default;

    virtual bool exportData(
        const QString& filePath,
        const std::vector<Invoice>& invoices,
        const std::vector<Expense>& expenses,
        QString& error) = 0;
};
