#include <QtTest/QtTest>
#include <memory>
#include <vector>
#include "../src/models/ExpenseTableModel.h"
#include "../src/models/Expense.h"

class ExpenseTableModelTests : public QObject
{
    Q_OBJECT

private slots:
    // Test initial state
    void rowCount_empty()
    {
        ExpenseTableModel model;
        QCOMPARE(model.rowCount(), 0);
        QCOMPARE(model.columnCount(), 2);
    }

    // Test data population
    void setExpenses_updatesModel()
    {
        ExpenseTableModel model;
        auto expenses = std::make_shared<std::vector<Expense>>();
        expenses->push_back(Expense("Coffee", 5.50));
        expenses->push_back(Expense("Internet", 60.00));

        model.setExpenses(expenses);

        QCOMPARE(model.rowCount(), 2);
        // Check first row, first column (Description)
        QCOMPARE(model.data(model.index(0, 0), Qt::DisplayRole).toString(), QString("Coffee"));
        // Check second row, second column (Cost)
        QCOMPARE(model.data(model.index(1, 1), Qt::DisplayRole).toDouble(), 60.00);
    }

    // Test Header data
    void headerData_returnsCorrectLabels()
    {
        ExpenseTableModel model;
        QCOMPARE(model.headerData(0, Qt::Horizontal, Qt::DisplayRole).toString(), QString("Description"));
        QCOMPARE(model.headerData(1, Qt::Horizontal, Qt::DisplayRole).toString(), QString("Amount"));
        // Test invalid section
        QCOMPARE(model.headerData(5, Qt::Horizontal, Qt::DisplayRole), QVariant());
    }

    // Test Edit functionality (Crucial for coverage of setData)
    void setData_updatesValue()
    {
        ExpenseTableModel model;
        auto expenses = std::make_shared<std::vector<Expense>>();
        expenses->push_back(Expense("Old Description", 10.00));
        model.setExpenses(expenses);

        // Update Description
        bool ok = model.setData(model.index(0, 0), "New Description", Qt::EditRole);

        QVERIFY(ok);
        QCOMPARE(expenses->at(0).getDescription(), std::string("New Description"));
        QCOMPARE(model.data(model.index(0, 0), Qt::DisplayRole).toString(), QString("New Description"));
    }

    // Test flags (ensuring items are editable)
    void flags_areCorrect()
    {
        ExpenseTableModel model;
        auto expenses = std::make_shared<std::vector<Expense>>();
        expenses->push_back(Expense("Test", 1.0));
        model.setExpenses(expenses);

        Qt::ItemFlags flags = model.flags(model.index(0, 0));
        QVERIFY(flags.testFlag(Qt::ItemIsEditable));
        QVERIFY(flags.testFlag(Qt::ItemIsEnabled));
    }

    //Test code path for alignment is executed
    void headerData_alignment()
    {
        ExpenseTableModel model;
        QVariant alignment = model.headerData(0, Qt::Horizontal, Qt::TextAlignmentRole);

        QVERIFY(alignment.isValid());
        QCOMPARE(alignment.value<Qt::Alignment>(), Qt::AlignHCenter | Qt::AlignVCenter);
    }
};

QTEST_MAIN(ExpenseTableModelTests)
#include "test_model_expense.moc"
