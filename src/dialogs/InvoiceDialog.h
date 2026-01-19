#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include "models/Invoice.h"

class InvoiceDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit *clientInput;
    QLineEdit *amountInput;
    QCheckBox *paidCheck;

public:
    explicit InvoiceDialog(QWidget *parent = nullptr);
    InvoiceDialog(QWidget* parent, const Invoice& invoice);
    Invoice getResult() const;
    Invoice getInvoice() const;
    QString client() const;
    double amount() const;
    bool isPaid() const;
};