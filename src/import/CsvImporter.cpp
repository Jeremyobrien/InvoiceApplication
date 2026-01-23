#include "CsvImporter.h"
#include "ImportResult.h"
#include <QStringList>
#include <QString>


std::optional<ImportResult> CsvImporter::parse(const QString &csvText)
{
    if (csvText.trimmed().isEmpty())
        return std::nullopt;
    
    QStringList lines = csvText.split('\n', Qt::SkipEmptyParts);
        if (lines.size() < 2)
        return std::nullopt;

    ImportResult result;
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
        if (parts.isEmpty())
            continue;

        if (invoices && parts[0] == "Client")
            continue;
        if (expenses && parts[0] == "Description")
            continue;

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

    if (result.invoices.empty() && result.expenses.empty())
        return std::nullopt;

    return result;
}