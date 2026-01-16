#pragma once
#include "Exporter.h"

class CsvExporter : public Exporter
{
public:
    bool exportData(
        const QString& filePath,
        const std::vector<Invoice>& invoices,
        const std::vector<Expense>& expenses,
        QString& error) override;
};
