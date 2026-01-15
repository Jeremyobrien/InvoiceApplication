#include "ExpenseDialog.h"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QValidator>

ExpenseDialog::ExpenseDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Add Expense");

    expenseInput = new QLineEdit(this);
    amountInput = new QLineEdit(this);

    auto *costValidator = new QDoubleValidator(0.0, 1'000'000'000.0, 2, this);
    costValidator->setNotation(QDoubleValidator::StandardNotation);
    amountInput->setValidator(costValidator);

    QFormLayout *layout = new QFormLayout(this);
    layout->addRow("Expense Description:", expenseInput);
    layout->addRow("Amount ($):", amountInput);

    QDialogButtonBox *buttons =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttons);
}

QString ExpenseDialog::description() const
{
    return expenseInput->text();
}

double ExpenseDialog::amount() const
{

    return amountInput->text().toDouble();
}

Expense ExpenseDialog::getExpense() const
{
    return Expense(
        expenseInput->text().toStdString(),
        amountInput->text().toDouble());
}