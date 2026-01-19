#pragma once

#include <QDialog>
#include <QLineEdit>
#include "models/Expense.h"

class ExpenseDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit *expenseInput;
    QLineEdit *amountInput;

public:
    ExpenseDialog(QWidget *parent = nullptr);
    ExpenseDialog(QWidget* parent, const Expense& expense);
    Expense getResult() const;
    Expense getExpense() const;
    QString description() const;
    double amount() const;
};