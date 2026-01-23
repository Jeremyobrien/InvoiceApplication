#include <QtTest/QtTest>
#include "dialogs/InvoiceDialog.h"

class InvoiceDialogTests : public QObject
{
    Q_OBJECT

private slots:
    void default_constructor_initial_state()
    {
        InvoiceDialog dialog;

        QCOMPARE(dialog.client(), QString(""));
        QCOMPARE(dialog.amount(), 0.0);
        QCOMPARE(dialog.isPaid(), false);
    }

    void constructor_with_invoice_populates_fields()
    {
        Invoice invoice("ACME", 100.0, true);
        InvoiceDialog dialog(nullptr, invoice);

        QCOMPARE(dialog.client(), QString("ACME"));
        QCOMPARE(dialog.amount(), 100.0);
        QCOMPARE(dialog.isPaid(), true);
    }

    void getInvoice_returns_expected_model()
    {
        InvoiceDialog dialog;
        dialog.findChild<QLineEdit*>()->setText("Client");

        Invoice result = dialog.getInvoice();

        QCOMPARE(result.getClient(), std::string("Client"));
    }
};

QTEST_MAIN(InvoiceDialogTests)
#include "test_invoice_dialog.moc"
