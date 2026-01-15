#include "InvoiceDialog.h"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QValidator>

InvoiceDialog::InvoiceDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Add Invoice");

    clientInput = new QLineEdit(this);
    amountInput = new QLineEdit(this);
    paidCheck = new QCheckBox("Paid", this);

    auto *costValidator = new QDoubleValidator(0.0, 1'000'000'000.0, 2, this);
    costValidator->setNotation(QDoubleValidator::StandardNotation);
    amountInput->setValidator(costValidator);

    QFormLayout *layout = new QFormLayout(this);
    layout->addRow("Client Name:", clientInput);
    layout->addRow("Amount ($):", amountInput);
    layout->addRow("", paidCheck);

    QDialogButtonBox *buttons =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttons);
}

Invoice InvoiceDialog::getInvoice() const
{
    return Invoice(
        clientInput->text().toStdString(),
        amountInput->text().toDouble(),
        paidCheck->isChecked());
}

QString InvoiceDialog::client() const
{
    return clientInput->text();
}

double InvoiceDialog::amount() const
{
    return amountInput->text().toDouble();
}

bool InvoiceDialog::isPaid() const
{
    return paidCheck->isChecked();
}