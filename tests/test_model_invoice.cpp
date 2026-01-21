#include <QtTest/QtTest>
#include "../src/models/InvoiceTableModel.h"

class InvoiceTableModelTests : public QObject
{
    Q_OBJECT

private slots:
    void rowCount_empty()
    {
        InvoiceTableModel model;
        QCOMPARE(model.rowCount(), 0);
    }
};

QTEST_MAIN(InvoiceTableModelTests)
#include "test_model_invoice.moc"
