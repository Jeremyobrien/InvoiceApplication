#include <QtTest/QtTest>
#include "models/ExpenseTableModel.h"
#include <QSignalSpy>
#include <memory>

class TestModelExpense : public QObject
{
    Q_OBJECT

private slots:
    // --- 1. UTILITY METHODS (items, refresh, updateRow) ---
    void test_utility_methods_coverage() {
        ExpenseTableModel model;
        auto data = std::make_shared<std::vector<Expense>>();
        data->push_back(Expense("Original", 10.0));
        model.setExpenses(data);

        // TARGET: items()
        // Accesses the raw pointer return expenses.get()
        QCOMPARE(model.items(), data.get());

        // TARGET: refresh()
        // Accesses beginResetModel/endResetModel
        model.refresh();

        // TARGET: updateRow()
        // Accesses dataChanged signal and the index() logic
        QSignalSpy spy(&model, &ExpenseTableModel::dataChanged);
        Expense updated("Updated", 20.0);
        model.updateRow(0, updated);

        QCOMPARE(spy.count(), 1);
        QCOMPARE(data->at(0).getDescription(), std::string("Updated"));
    }

    // --- 2. ALIGNMENT & FALLTHROUGH (data method) ---
    void test_data_alignment_and_empty_return() {
        ExpenseTableModel model;
        auto data = std::make_shared<std::vector<Expense>>();
        data->push_back(Expense("Test", 1.0));
        model.setExpenses(data);

        // TARGET: role == Qt::TextAlignmentRole
        QVariant align = model.data(model.index(0, 0), Qt::TextAlignmentRole);
        QCOMPARE(align.value<Qt::Alignment>(), Qt::AlignHCenter | Qt::AlignVCenter);

        // TARGET: Final 'return QVariant()' in data()
        // By using a role like 'DecorationRole' which is not handled by IF/Switch
        QVariant empty = model.data(model.index(0, 0), Qt::DecorationRole);
        QVERIFY(!empty.isValid());
    }

    // --- 3. FLAGS & SETDATA (defaults and item flags) ---
    void test_flags_and_setdata_coverage() {
        ExpenseTableModel model;
        auto data = std::make_shared<std::vector<Expense>>();
        data->push_back(Expense("Test", 1.0));
        model.setExpenses(data);

        // TARGET: return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
        Qt::ItemFlags flags = model.flags(model.index(0, 0));
        QVERIFY(flags.testFlag(Qt::ItemIsSelectable));
        QVERIFY(flags.testFlag(Qt::ItemIsEditable));

        // TARGET: setData() switch default: return false;
        // Providing a valid index/role but a column that doesn't exist (e.g. 99)
        bool defaultHit = model.setData(model.index(0, 99), "Fail", Qt::EditRole);
        QVERIFY(defaultHit == false);
    }

    // --- 4. HEADER DATA GAPS ---
    void test_header_alignment_coverage() {
        ExpenseTableModel model;

        // TARGET: Alignment in headerData()
        QVariant align = model.headerData(0, Qt::Horizontal, Qt::TextAlignmentRole);
        QCOMPARE(align.value<Qt::Alignment>(), Qt::AlignHCenter | Qt::AlignVCenter);

        // TARGET: Final 'return QVariant()' in headerData()
        QVariant empty = model.headerData(0, Qt::Horizontal, Qt::InitialSortOrderRole);
        QVERIFY(!empty.isValid());
    }

    // --- 5. GUARD CLAUSES ---
    void test_guards_coverage() {
        ExpenseTableModel model;

        // Hits the !expenses and !index.isValid() guards in data()
        QVERIFY(!model.data(QModelIndex(), Qt::DisplayRole).isValid());

        // Hits the !index.isValid() guard in flags()
        QCOMPARE(model.flags(QModelIndex()), Qt::NoItemFlags);

        // Hits the orientation guard in headerData()
        QVERIFY(!model.headerData(0, Qt::Vertical, Qt::DisplayRole).isValid());
    }

    // --- 6. HAPPY PATH (Case 0/1) ---
    void test_happy_path_switches() {
        ExpenseTableModel model;
        auto data = std::make_shared<std::vector<Expense>>();
        data->push_back(Expense("Coffee", 5.0));
        model.setExpenses(data);

        // Covers cases in data()
        QCOMPARE(model.data(model.index(0, 0), Qt::DisplayRole).toString(), QString("Coffee"));
        QCOMPARE(model.data(model.index(0, 1), Qt::EditRole).toDouble(), 5.0);

        // Covers cases in setData()
        QVERIFY(model.setData(model.index(0, 0), "Tea", Qt::EditRole));
        QVERIFY(model.setData(model.index(0, 1), 3.5, Qt::EditRole));
    }
};

QTEST_MAIN(TestModelExpense)
#include "test_model_expense.moc"