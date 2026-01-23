#include <QtTest/QtTest>
#include "import/JsonImporter.h"

class JsonImporterTests : public QObject
{
    Q_OBJECT

private slots:
    void parse_empty_json()
    {
        QByteArray json = "{}";
        auto result = JsonImporter::parse(json);
        QVERIFY(result.has_value());
    }

    void parse_invalid_json_returns_nullopt()
    {
        QByteArray invalid = "{";
        auto result = JsonImporter::parse(invalid);
        QVERIFY(!result.has_value());
    }
};

QTEST_MAIN(JsonImporterTests)
#include "test_json_importer.moc"
