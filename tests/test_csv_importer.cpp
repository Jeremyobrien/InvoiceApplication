#include <QtTest/QtTest>
#include "import/CsvImporter.h"

class CsvImporterTests : public QObject
{
    Q_OBJECT

private slots:
    void parse_valid_csv()
    {
        QString csv =
            "Invoices\n"
            "Client,Amount,Paid\n"
            "Acme,100,Yes\n"
            "Expenses\n"
            "Description,Cost\n"
            "Lunch,12.50\n";

        auto result = CsvImporter::parse(csv);
        QVERIFY(result.has_value());
        QVERIFY(!result->invoices.empty());
        QVERIFY(!result->expenses.empty());
    }

    void parse_invalid_csv_returns_nullopt()
    {
        QString invalid = "garbage";
        auto result = CsvImporter::parse(invalid);
        QVERIFY(!result.has_value());
    }
};

QTEST_MAIN(CsvImporterTests)
#include "test_csv_importer.moc"
