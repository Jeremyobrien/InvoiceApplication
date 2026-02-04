#include <QtTest/QtTest>
#include "import/ImportUtils.h"
#include "models/Invoice.h"

class ApplyImportTests : public QObject
{
    Q_OBJECT

private slots:
    // Case 1: ImportMode::Replace
    void replace_mode_overwrites_existing_data()
    {
        std::vector<int> existing = { 1, 2, 3 };
        std::vector<int> incoming = { 4, 5 };

        applyImport(existing, incoming, ImportMode::Replace);

        QCOMPARE(existing.size(), 2ULL);
        QCOMPARE(existing[0], 4);
        QCOMPARE(existing[1], 5);
    }

    // Case 2: ImportMode::Merge
    void merge_mode_appends_data()
    {
        std::vector<int> existing = { 1, 2 };
        std::vector<int> incoming = { 3, 4 };

        applyImport(existing, incoming, ImportMode::Merge);

        QCOMPARE(existing.size(), 4ULL);
        QCOMPARE(existing[0], 1);
        QCOMPARE(existing[3], 4);
    }

    // Case 3: Empty Incoming (Edge Case)
    void merge_empty_incoming_does_nothing()
    {
        std::vector<int> existing = { 1, 2 };
        std::vector<int> incoming = {};

        applyImport(existing, incoming, ImportMode::Merge);

        QCOMPARE(existing.size(), 2ULL);
    }

    // Case 4: Testing with real objects (Ensures template works with Invoice)
    void works_with_invoice_objects()
    {
        std::vector<Invoice> existing;
        Invoice inv1; inv1.setClient("Old Client");
        existing.push_back(inv1);

        std::vector<Invoice> incoming;
        Invoice inv2; inv2.setClient("New Client");
        incoming.push_back(inv2);

        applyImport(existing, incoming, ImportMode::Merge);

        QCOMPARE(existing.size(), 2ULL);
        QCOMPARE(existing[1].getClient(), std::string("New Client"));
    }
};

QTEST_MAIN(ApplyImportTests)
#include "test_apply_import.moc"