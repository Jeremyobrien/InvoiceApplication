#include <QtTest/QtTest>
#include <QSignalSpy>
#include "../src/models/InvoiceTableModel.h"
#include <memory>
#include <vector>

class InvoiceTableModelTests : public QObject
{
    Q_OBJECT

private:
    std::unique_ptr<InvoiceTableModel> createPopulatedModel() {
        auto model = std::make_unique<InvoiceTableModel>();
        auto data = std::make_shared<std::vector<Invoice>>();

        Invoice inv1; inv1.setClient("Acme Corp"); inv1.setAmount(100.0); inv1.setPaid(true);
        Invoice inv2; inv2.setClient("Globex");    inv2.setAmount(250.5); inv2.setPaid(false);

        data->push_back(inv1);
        data->push_back(inv2);

        model->setInvoices(data);
        return model;
    }

private slots:
    // --- 1. UTILITY & DIMENSIONS ---
    void utilityCoverage() {
        auto model = createPopulatedModel();

        // items() coverage
        QVERIFY(model->items() != nullptr);

        // updateRow() coverage
        QSignalSpy spy(model.get(), &InvoiceTableModel::dataChanged);
        Invoice update; update.setClient("Updated");
        model->updateRow(0, update);
        QCOMPARE(spy.count(), 1);

        // refresh() coverage
        QSignalSpy resetSpy(model.get(), &InvoiceTableModel::modelReset);
        model->refresh();
        QCOMPARE(resetSpy.count(), 1);
    }

    // --- 2. DATA() ROLES & BRANCHES ---
    void dataRolesCoverage() {
        auto model = createPopulatedModel();

        // Guard clause: !index.isValid()
        QVERIFY(!model->data(QModelIndex(), Qt::DisplayRole).isValid());

        // data() switch default: Column 99
        QVERIFY(!model->data(model->index(0, 99), Qt::DisplayRole).isValid());

        // AlignmentRole Column 0 (Hits Align block)
        QVERIFY(model->data(model->index(0, 0), Qt::TextAlignmentRole).isValid());
        // AlignmentRole Column 2 (Skips Align block, hits final return QVariant)
        QVERIFY(!model->data(model->index(0, 2), Qt::TextAlignmentRole).isValid());

        // CheckStateRole Column 2
        QCOMPARE(model->data(model->index(0, 2), Qt::CheckStateRole).toInt(), (int)Qt::Checked);
        QCOMPARE(model->data(model->index(1, 2), Qt::CheckStateRole).toInt(), (int)Qt::Unchecked);

        // Final fallthrough: Role not handled
        QVERIFY(!model->data(model->index(0, 0), Qt::ToolTipRole).isValid());
    }

    // --- 3. HEADERDATA() COVERAGE ---
    void headerDataCoverage() {
        auto model = createPopulatedModel();

        // Guard: role != DisplayRole
        QVERIFY(!model->headerData(0, Qt::Horizontal, Qt::ToolTipRole).isValid());
        // Guard: orientation != Horizontal
        QVERIFY(!model->headerData(0, Qt::Vertical, Qt::DisplayRole).isValid());

        // Standard Switch
        QCOMPARE(model->headerData(2, Qt::Horizontal, Qt::DisplayRole).toString(), QString("Paid"));
        // Switch Default: Column 99
        QVERIFY(!model->headerData(99, Qt::Horizontal, Qt::DisplayRole).isValid());
    }

    // --- 4. FLAGS() COVERAGE ---
    void flagsCoverage() {
        auto model = createPopulatedModel();

        // Guard: !index.isValid()
        QCOMPARE(model->flags(QModelIndex()), Qt::NoItemFlags);

        // Column 2 (UserCheckable)
        QVERIFY(model->flags(model->index(0, 2)) & Qt::ItemIsUserCheckable);
        // Column 0 (Standard)
        QVERIFY(!(model->flags(model->index(0, 0)) & Qt::ItemIsUserCheckable));
    }

    // --- 5. SETDATA() COVERAGE ---
    void setDataCoverage() {
        auto model = createPopulatedModel();

        // Guard: !index.isValid()
        QVERIFY(!model->setData(QModelIndex(), "value", Qt::EditRole));

        // Branch: CheckStateRole on Col 2
        QVERIFY(model->setData(model->index(1, 2), Qt::Checked, Qt::CheckStateRole));

        // Branch: role != EditRole (and not checkstate) -> return false
        QVERIFY(!model->setData(model->index(0, 0), "value", Qt::ToolTipRole));

        // Switch cases 0, 1, 2
        QVERIFY(model->setData(model->index(0, 1), 500.0, Qt::EditRole));
        QVERIFY(model->setData(model->index(0, 2), false, Qt::EditRole)); // case 2

        // Switch Default: Column 99
        QVERIFY(!model->setData(model->index(0, 99), "value", Qt::EditRole));
    }

    // --- 6. REMOVEROWS() COVERAGE ---
    void removeRowsCoverage() {
        auto model = createPopulatedModel();

        // Guard: !invoices (test with empty model)
        InvoiceTableModel emptyModel;
        QVERIFY(!emptyModel.removeRows(0, 1, QModelIndex()));

        // Guard: row < 0
        QVERIFY(!model->removeRows(-1, 1, QModelIndex()));
        // Guard: row + count > size
        QVERIFY(!model->removeRows(0, 5, QModelIndex()));

        // Success Path
        QVERIFY(model->removeRows(0, 1, QModelIndex()));
        QCOMPARE(model->rowCount(QModelIndex()), 1);
    }
};

QTEST_MAIN(InvoiceTableModelTests)
#include "test_model_invoice.moc"