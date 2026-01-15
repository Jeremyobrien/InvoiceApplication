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
    InvoiceDialog(QWidget *parent = nullptr);
    Invoice getInvoice() const;
    QString client() const;
    double amount() const;
    bool isPaid() const;
};