#include <QtTest/QtTest>
#include <QTemporaryFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "export/JsonExporter.h"

class JsonExporterTests : public QObject
{
    Q_OBJECT

private slots:
    // Exercises: The "Happy Path" with actual data content verification
    void export_with_data_verifies_content()
    {
        JsonExporter exporter;
        QString error;

        // Setup mock data
        std::vector<Invoice> invoices;
        Invoice inv; inv.setClient("Test Client"); inv.setAmount(500.0); inv.setPaid(true);
        invoices.push_back(inv);

        std::vector<Expense> expenses;
        expenses.push_back(Expense("Server Cost", 20.0));

        QTemporaryFile file;
        QVERIFY(file.open());
        QString path = file.fileName();
        file.close(); // Close so exporter can open it

        bool result = exporter.exportData(path, invoices, expenses, error);

        // 1. Check logical success
        QVERIFY(result);
        QVERIFY(error.isEmpty());

        // 2. Structural Verification: Re-parse the JSON to ensure it's valid
        QFile checkFile(path);
        QVERIFY(checkFile.open(QIODevice::ReadOnly));
        QJsonDocument doc = QJsonDocument::fromJson(checkFile.readAll());
        QVERIFY(!doc.isNull());

        // Verify specific values inside the JSON
        QJsonObject root = doc.object();
        QCOMPARE(root["invoices"].toArray().at(0).toObject()["client"].toString(), QString("Test Client"));
        QCOMPARE(root["expenses"].toArray().at(0).toObject()["description"].toString(), QString("Server Cost"));
    }

    // Exercises: The guard clause if(!file.open(QIODevice::WriteOnly))
    void export_fails_on_invalid_path()
    {
        JsonExporter exporter;
        QString error;

        // Use a path that is guaranteed to be invalid/restricted (root on Unix or empty on Windows)
        bool result = exporter.exportData("/invalid/path/file.json", {}, {}, error);

        QVERIFY(!result);
        QCOMPARE(error, QString("Cannot open file"));
    }

    // Exercises: Empty collection handling
    void export_empty_collections()
    {
        JsonExporter exporter;
        QString error;
        QTemporaryFile file;
        QVERIFY(file.open());

        bool result = exporter.exportData(file.fileName(), {}, {}, error);

        QVERIFY(result);

        // Verify it produced a valid JSON root with empty arrays
        QFile checkFile(file.fileName());
        checkFile.open(QIODevice::ReadOnly);
        QJsonObject root = QJsonDocument::fromJson(checkFile.readAll()).object();
        QVERIFY(root.contains("invoices") && root["invoices"].toArray().isEmpty());
    }
};

QTEST_MAIN(JsonExporterTests)
#include "test_json_exporter.moc"