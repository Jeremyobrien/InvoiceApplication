#include "JsonImporter.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

std::optional<ImportResult> JsonImporter::parse(const QByteArray &jsonData)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isObject())
        return std::nullopt;
    
    ImportResult result;
    QJsonObject root = doc.object();

    for (const auto &record : root["invoices"].toArray())
    {
        QJsonObject obj = record.toObject();
        Invoice inv;
        inv.setClient(obj["client"].toString().toStdString());
        inv.setAmount(obj["amount"].toDouble());
        inv.setPaid(obj["paid"].toBool());
        result.invoices.push_back(inv);
    }

    for (const auto &record : root["expenses"].toArray())
    {
        QJsonObject obj = record.toObject();
        Expense exp;
        exp.setDescription(obj["description"].toString().toStdString());
        exp.setCost(obj["cost"].toDouble());
        result.expenses.push_back(exp);
    }

    return result;
}