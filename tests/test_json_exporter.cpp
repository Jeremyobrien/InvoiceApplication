#include <QtTest/QtTest>
#include <QTemporaryFile>
#include "export/JsonExporter.h"

class JsonExporterTests : public QObject
{
    Q_OBJECT

private slots:
    void exports_file_successfully()
    {
        JsonExporter exporter;
        QString error;

        std::vector<Invoice> invoices;
        std::vector<Expense> expenses;

        QTemporaryFile file;
        QVERIFY(file.open());

        bool result = exporter.exportData(
            file.fileName(),
            invoices,
            expenses,
            error
        );

        QVERIFY(result);
        QVERIFY(error.isEmpty());
    }
};

QTEST_MAIN(JsonExporterTests)
#include "test_json_exporter.moc"
