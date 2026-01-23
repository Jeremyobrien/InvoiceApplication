#include <QtTest/QtTest>
#include "dialogs/ExpenseDialog.h"

class ExpenseDialogTests : public QObject
{
    Q_OBJECT

private slots:
    void default_constructor_initial_state()
    {
        ExpenseDialog dialog;

        QCOMPARE(dialog.description(), QString(""));
        QCOMPARE(dialog.amount(), 0.0);
    }

    void constructor_with_expense_populates_fields()
    {
        Expense expense("Lunch", 12.50);
        ExpenseDialog dialog(nullptr, expense);

        QCOMPARE(dialog.description(), QString("Lunch"));
        QCOMPARE(dialog.amount(), 12.50);
    }

    void getExpense_returns_expected_model()
    {
        ExpenseDialog dialog;
        dialog.findChild<QLineEdit*>()->setText("Coffee");

        Expense result = dialog.getExpense();

        QCOMPARE(result.getDescription(), std::string("Coffee"));
    }
};

QTEST_MAIN(ExpenseDialogTests)
#include "test_expense_dialog.moc"