#pragma once

#include <QMainWindow>
#include <QTableView>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QLabel>
#include <memory>
#include <QPushButton>
#include "models/Invoice.h"
#include "models/Expense.h"
#include "models/InvoiceTableModel.h"
#include "models/ExpenseTableModel.h"
#include "import/ImportMode.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void addInvoice();
    void addExpense();
    void deleteInvoice();
    void deleteExpense();
    void editInvoice();
    void editExpense();
    void importData();
    void exportData();

private:
    std::shared_ptr<std::vector<Invoice>> invoices;
    std::shared_ptr<std::vector<Expense>> expenses;
    QLineEdit *invoiceSearch;
    QLineEdit *expenseSearch;
    QSortFilterProxyModel *invoiceProxy = nullptr;
    QSortFilterProxyModel *expenseProxy = nullptr;
    QTabWidget *tabWidget;
    InvoiceTableModel *invoiceModel;
    ExpenseTableModel *expenseModel;
    QTableView *invoiceView;
    QTableView *expenseView;
    QLabel *profitLabel;

    void setupTabs();
    void refreshProfit();
    ImportMode askImportMode();
};