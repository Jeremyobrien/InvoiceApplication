#include <QtTest/QtTest>
#include <QTemporaryFile>
#include "export/CsvExporter.h"

class CsvExporterTests : public QObject
{
    Q_OBJECT

private slots:
    void exports_file_successfully()
    {
        CsvExporter exporter;
        QString error;

        std::vector<Invoice> invoices = {
            Invoice("Client", 100.0, true)
        };
        std::vector<Expense> expenses = {
            Expense("Coffee", 5.0)
        };

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

QTEST_MAIN(CsvExporterTests)
#include "test_csv_exporter.moc"
