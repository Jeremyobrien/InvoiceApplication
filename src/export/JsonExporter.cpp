#include "JsonExporter.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

bool JsonExporter::exportData(
    const QString& filePath,
    const std::vector<Invoice>& invoices,
    const std::vector<Expense>& expenses,
    QString& error)
{
    QJsonObject root;

    QJsonArray invoiceArray;
    for (const auto& inv : invoices)
    {
        QJsonObject obj;
        obj["client"] = QString::fromStdString(inv.getClient());
        obj["amount"] = inv.getAmount();
        obj["paid"] = inv.isPaid();
        invoiceArray.append(obj);
    }

    QJsonArray expenseArray;
    for (const auto& exp : expenses)
    {
        QJsonObject obj;
        obj["description"] = QString::fromStdString(exp.getDescription());
        obj["cost"] = exp.getCost();
        expenseArray.append(obj);
    }

    root["invoices"] = invoiceArray;
    root["expenses"] = expenseArray;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        error = "Cannot open file";
        return false;
    }

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    return true;
}
