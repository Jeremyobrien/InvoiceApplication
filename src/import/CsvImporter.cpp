#include "CsvImporter.h"

#include <QStringList>

std::optional<ImportResult> CsvImporter::parse(const QString &csvText)
{
    ImportResult result;

    QStringList lines = csvText.split('\n');
    bool invoices = false;
    bool expenses = false;

    for (QString line : lines)
    {
        line = line.trimmed();
        if (line.isEmpty())
            continue;
        
        if (line == "Invoices")
        {
            invoices = true;
            expenses = false;
            continue;
        }
        if (line == "Expenses")
        {
            invoices = false;
            expenses = true;
            continue;
        }

        QStringList parts = line.split(',');

        if (invoices && parts.size() == 3)
        {
            Invoice inv;
            inv.setClient(parts[0].toStdString());
            inv.setAmount(parts[1].toDouble());
            inv.setPaid(parts[2].toLower() == "yes");
            result.invoices.push_back(inv);
        }

        if (expenses && parts.size() == 2)
        {
            Expense exp;
            exp.setDescription(parts[0].toStdString());
            exp.setCost(parts[1].toDouble());
            result.expenses.push_back(exp);
        }
    }

    return result;
}