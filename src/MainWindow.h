#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void refreshUI();

private slots:
    void addInvoice();
    void addExpense();

public:
    MainWindow(QWidget *parent = nullptr);
};

#endif