#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <vector>
#include "Invoice.h"
#include "Expense.h"
#include "InvoiceDialog.h"
#include "ExpenseDialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    std::vector<Invoice> invoices;
    std::vector<Expense> expenses;

    QTableWidget *invoiceTable;
    QTableWidget *expenseTable;
    QLabel *profitLabel;

    void refreshInvoices();
    void refreshExpenses();
    void refreshProfit();

private slots:
    void addInvoice();
    void addExpense();

public:
    MainWindow(QWidget *parent = nullptr);
};