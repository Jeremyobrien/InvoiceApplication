#pragma once

#include <QMainWindow>
#include <QTableView>

#include <QLabel>
#include <memory>
#include <QPushButton>
#include "models/Invoice.h"
#include "models/Expense.h"
#include "models/InvoiceTableModel.h"
#include "models/ExpenseTableModel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void addInvoice();
    void addExpense();
    QString chooseFile(const QString& filter);
    void importCsv(QString filePath);
    void importJson(QString filePath);
    void importData();
    void exportData();
    void exportCsv(const QString& filePath);
    void exportJson(const QString& filePath);

private:
    std::shared_ptr<std::vector<Invoice>> invoices;
    std::shared_ptr<std::vector<Expense>> expenses;

    QTabWidget *tabWidget;
    InvoiceTableModel* invoiceModel;
    ExpenseTableModel* expenseModel;
    QTableView* invoiceView;
    QTableView* expenseView;
    QLabel* profitLabel;


    void setupTabs();
    void refreshProfit();

public:
    MainWindow(QWidget *parent = nullptr);
};