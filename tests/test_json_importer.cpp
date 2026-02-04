#include <QtTest/QtTest>
#include <optional>
#include "import/JsonImporter.h"

class JsonImporterTests : public QObject
{
    Q_OBJECT

private slots:
    // Exercises: Happy Path - Full data reconstruction
    void parse_valid_full_data()
    {
        QByteArray json = R"({
            "invoices": [
                {"client": "Alice", "amount": 150.0, "paid": true}
            ],
            "expenses": [
                {"description": "Coffee", "cost": 5.25}
            ]
        })";

        auto result = JsonImporter::parse(json);

        QVERIFY(result.has_value());
        QCOMPARE(static_cast<int>(result->invoices.size()), 1);
        QCOMPARE(result->invoices[0].getClient(), std::string("Alice"));
        QCOMPARE(result->invoices[0].getAmount(), 150.0);
        QVERIFY(result->invoices[0].isPaid());

        QCOMPARE(static_cast<int>(result->expenses.size()), 1);
        QCOMPARE(result->expenses[0].getDescription(), std::string("Coffee"));
        QCOMPARE(result->expenses[0].getCost(), 5.25);
    }

    // Exercises: doc.isObject() guard clause
    void parse_json_array_fails()
    {
        // JSON is valid, but it's an array, not an object root
        QByteArray json = "[1, 2, 3]";
        auto result = JsonImporter::parse(json);
        QVERIFY(!result.has_value());
    }

    // Exercises: Invalid JSON formatting
    void parse_invalid_json_returns_nullopt()
    {
        QByteArray invalid = "{ \"unclosed\": ";
        auto result = JsonImporter::parse(invalid);
        QVERIFY(!result.has_value());
    }

    // Exercises: Missing keys (Testing resilience of QJsonObject operator[])
    void parse_missing_keys_gracefully()
    {
        // Missing "amount" and "paid" for invoice
        QByteArray json = R"({
            "invoices": [{"client": "Ghost"}]
        })";

        auto result = JsonImporter::parse(json);
        QVERIFY(result.has_value());

        // Qt returns default values (0.0, false) for missing keys
        QCOMPARE(result->invoices[0].getClient(), std::string("Ghost"));
        QCOMPARE(result->invoices[0].getAmount(), 0.0);
        QVERIFY(!result->invoices[0].isPaid());
    }

    // Exercises: Wrong type handling
    void parse_type_mismatch()
    {
        // "amount" is a string instead of a double
        QByteArray json = R"({
            "invoices": [{"client": "Bob", "amount": "one million"}]
        })";

        auto result = JsonImporter::parse(json);
        QVERIFY(result.has_value());
        // toDouble() on a string returns 0.0
        QCOMPARE(result->invoices[0].getAmount(), 0.0);
    }

    void parse_multiple_expenses_loop_test()
    {
        QByteArray json = R"({
        "expenses": [
            {"description": "Item 1", "cost": 10.0},
            {"description": "Item 2", "cost": 20.0}
        ]
    })";

        auto result = JsonImporter::parse(json);

        QVERIFY(result.has_value());
        // This line ensures the loop body code is executed
        QCOMPARE(static_cast<int>(result->expenses.size()), 2);
        QCOMPARE(result->expenses[1].getDescription(), std::string("Item 2"));
    }

    void parse_only_expenses()
    {
        QByteArray json = R"({
        "expenses": [
            {"description": "Test Loop", "cost": 10.0}
        ]
    })";

        auto result = JsonImporter::parse(json);
        QVERIFY(result.has_value());
        QVERIFY(result->expenses.size() > 0);
        QCOMPARE(result->expenses[0].getDescription(), std::string("Test Loop"));
    }
};

QTEST_MAIN(JsonImporterTests)
#include "test_json_importer.moc"