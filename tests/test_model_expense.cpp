#include <QtTest/QtTest>
#include "../src/models/ExpenseTableModel.h"

class ExpenseTableModelTests : public QObject
{
    Q_OBJECT

private slots:
    void rowCount_empty()
    {
        ExpenseTableModel model;
        QCOMPARE(model.rowCount(), 0);
    }
};

QTEST_MAIN(ExpenseTableModelTests)
#include "test_model_expense.moc"
