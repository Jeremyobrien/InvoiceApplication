#include <QtTest/QtTest>
#include "../src/models/Invoice.h"

class InvoiceTests : public QObject
{
    Q_OBJECT

private slots:
    void testDefaultConstructor()
    {
        Invoice inv;
        QVERIFY(inv.getClient().empty());
        QCOMPARE(inv.getAmount(), 0.0);
        QCOMPARE(inv.isPaid(), false);
    }

    void testSettersAndGetters()
    {
        Invoice inv;
        inv.setClient("Tim");
        inv.setAmount(150.75);
        inv.setPaid(true);

        QCOMPARE(QString::fromStdString(inv.getClient()), QString("Tim"));
        QCOMPARE(inv.getAmount(), 150.75);
        QCOMPARE(inv.isPaid(), true);
    }
};

QTEST_MAIN(InvoiceTests)
#include "test_invoice.moc"
