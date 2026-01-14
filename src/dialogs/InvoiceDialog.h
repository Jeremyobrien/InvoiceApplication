#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>

class InvoiceDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit *clientInput;
    QLineEdit *amountInput;
    QCheckBox *paidCheck;

public:
    InvoiceDialog(QWidget *parent = nullptr);

    QString client() const;
    double amount() const;
    bool isPaid() const;
};