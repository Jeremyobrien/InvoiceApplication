#ifndef EXPENSEDIALOG_H
#define EXPENSEDIALOG_H

#include <QDialog>
#include <QLineEdit>

class ExpenseDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit *expenseInput;
    QLineEdit *amountInput;

public:
    ExpenseDialog(QWidget *parent = nullptr);

    QString description() const;
    double amount() const;
};

#endif