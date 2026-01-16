#include "CsvExporter.h"
#include <QFile>
#include <QTextStream>

bool CsvExporter::exportData(
    const QString& filePath,
    const std::vector<Invoice>& invoices,
    const std::vector<Expense>& expenses,
    QString& error)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        error = "Cannot open file";
        return false;
    }

    QTextStream out(&file);

    out << "Invoices\n";
    out << "Client,Amount,Paid\n";

    for (const auto& inv : invoices)
    {
        out << QString::fromStdString(inv.getClient()) << ","
            << inv.getAmount() << ","
            << (inv.isPaid() ? "Yes" : "No") << "\n";
    }

    out << "\nExpenses\n";
    out << "Description,Cost\n";

    for (const auto& exp : expenses)
    {
        out << QString::fromStdString(exp.getDescription()) << ","
            << exp.getCost() << "\n";
    }

    return true;
}
