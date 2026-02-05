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
    void rowAndColumnCount() {
        auto model = createPopulatedModel();
        QCOMPARE(model->rowCount(), 2);
        QCOMPARE(model->columnCount(), 3);

        InvoiceTableModel emptyModel;
        QCOMPARE(emptyModel.rowCount(), 0);
    }

    void dataRolesAndColumns() {
        auto model = createPopulatedModel();

        // Edge case: Invalid index or null data
        QVERIFY(!model->data(QModelIndex(), Qt::DisplayRole).isValid());

        // Happy path: Column 0, 1, 2 DisplayRole
        QCOMPARE(model->data(model->index(0, 0), Qt::DisplayRole).toString(), QString("Acme Corp"));
        QCOMPARE(model->data(model->index(0, 1), Qt::DisplayRole).toDouble(), 100.0);
        QCOMPARE(model->data(model->index(0, 2), Qt::DisplayRole).toString(), QString("Yes"));
        QCOMPARE(model->data(model->index(1, 2), Qt::DisplayRole).toString(), QString("No"));

        // Column 2: CheckStateRole
        QCOMPARE(model->data(model->index(0, 2), Qt::CheckStateRole).toInt(), (int)Qt::Checked);

        // Invalid Column / Role
        QVERIFY(!model->data(model->index(0, 99), Qt::DisplayRole).isValid());
        QVERIFY(!model->data(model->index(0, 0), Qt::DecorationRole).isValid());
    }

    void headerData() {
        auto model = createPopulatedModel();
        QCOMPARE(model->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString(), QString("Client"));
        QCOMPARE(model->headerData(1, Qt::Horizontal, Qt::DisplayRole).toString(), QString("Amount"));
        QCOMPARE(model->headerData(2, Qt::Horizontal, Qt::DisplayRole).toString(), QString("Paid"));

        // Edge cases
        QVERIFY(!model->headerData(0, Qt::Vertical, Qt::DisplayRole).isValid());
        QVERIFY(!model->headerData(99, Qt::Horizontal, Qt::DisplayRole).isValid());
        QVERIFY(!model->headerData(0, Qt::Horizontal, Qt::DecorationRole).isValid());
    }

    void flags() {
        auto model = createPopulatedModel();
        // Col 2 should NOT have ItemIsEditable but SHOULD have ItemIsUserCheckable
        Qt::ItemFlags col2Flags = model->flags(model->index(0, 2));
        QVERIFY(col2Flags & Qt::ItemIsUserCheckable);
        QVERIFY(!(col2Flags & Qt::ItemIsEditable));

        // Col 0 should have ItemIsEditable
        QVERIFY(model->flags(model->index(0, 0)) & Qt::ItemIsEditable);
        QVERIFY(model->flags(QModelIndex()) == Qt::NoItemFlags);
    }

    void setDataAndSignals() {
        auto model = createPopulatedModel();
        QSignalSpy spy(model.get(), &InvoiceTableModel::dataChanged);

        // Edit Amount (Col 1)
        QVERIFY(model->setData(model->index(0, 1), 999.9, Qt::EditRole));
        QCOMPARE(model->items()->at(0).getAmount(), 999.9);

        // Toggle Checkbox (Col 2)
        QVERIFY(model->setData(model->index(1, 2), Qt::Checked, Qt::CheckStateRole));
        QVERIFY(model->items()->at(1).isPaid());

        QCOMPARE(spy.count(), 2);

        // Fail cases
        QVERIFY(!model->setData(model->index(0, 99), "fail", Qt::EditRole));
        QVERIFY(!model->setData(model->index(0, 0), "fail", Qt::DecorationRole));
    }

    void removeRows() {
        auto model = createPopulatedModel();
        QVERIFY(model->removeRows(0, 1, QModelIndex()));
        QCOMPARE(model->rowCount(), 1);

        // Edge cases for out of bounds
        QVERIFY(!model->removeRows(-1, 1, QModelIndex()));
        QVERIFY(!model->removeRows(0, 10, QModelIndex()));
    }

    void utilities() {
        auto model = createPopulatedModel();
        Invoice inv; inv.setClient("Updated");
        model->updateRow(0, inv);
        QCOMPARE(model->items()->at(0).getClient(), std::string("Updated"));

        model->refresh(); // Just coverage for reset signals
        QVERIFY(model->items() != nullptr);
    }
};

QTEST_MAIN(InvoiceTableModelTests)
#include "test_model_invoice.moc"