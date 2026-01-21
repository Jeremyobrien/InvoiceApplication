#include <QtTest/QtTest>
#include "../src/models/Expense.h"

class ExpenseTests : public QObject
{
    Q_OBJECT

private slots:
    void constructor_sets_values()
    {
        Expense exp("Lunch", 13.50);
        QCOMPARE(exp.getDescription(), std::string("Lunch"));
        QCOMPARE(exp.getCost(), 13.50);
    }

    void testSettersAndGetters()
    {
        Expense exp;
        exp.setDescription("Lunch");
        exp.setCost(13.50);

        QCOMPARE(QString::fromStdString(exp.getDescription()), QString("Lunch"));
        QCOMPARE(exp.getCost(), 13.50);
    }
};

QTEST_MAIN(ExpenseTests)
#include "test_expense.moc"
