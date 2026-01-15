#include "MainWindow.h"
#include "dialogs/InvoiceDialog.h"
#include "dialogs/ExpenseDialog.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupTabs();
}

void MainWindow::setupTabs()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    profitLabel = new QLabel("Profit: $0");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    central->setLayout(mainLayout);

    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(profitLabel);

    QWidget *invoiceTab = new QWidget();
    QVBoxLayout *invoiceLayout = new QVBoxLayout(invoiceTab);

    invoiceModel = new InvoiceTableModel(this);
    invoices = std::make_shared<std::vector<Invoice>>();
    invoiceModel->setInvoices(invoices);

    invoiceView = new QTableView(invoiceTab);
    invoiceView->setModel(invoiceModel);
    invoiceView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    invoiceView->setAlternatingRowColors(true);
    invoiceView->setSelectionBehavior(QAbstractItemView::SelectRows);
    invoiceLayout->addWidget(invoiceView);
    QPushButton *addInvoiceBtn = new QPushButton("Add Invoice");
    connect(addInvoiceBtn, &QPushButton::clicked, this, &MainWindow::addInvoice);
    invoiceLayout->addWidget(addInvoiceBtn);
    tabWidget->addTab(invoiceTab, "Invoices");

    QWidget *expenseTab = new QWidget();
    QVBoxLayout *expenseLayout = new QVBoxLayout(expenseTab);

    expenseModel = new ExpenseTableModel(this);
    expenses = std::make_shared<std::vector<Expense>>();
    expenseModel->setExpenses(expenses);
    expenseView = new QTableView(expenseTab);
    expenseView->setModel(expenseModel);
    expenseView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    expenseView->setAlternatingRowColors(true);
    expenseView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QPushButton *addExpenseBtn = new QPushButton("Add Expense");
    connect(addExpenseBtn, &QPushButton::clicked, this, &MainWindow::addExpense);

    expenseLayout->addWidget(expenseView);
    expenseLayout->addWidget(addExpenseBtn);
    tabWidget->addTab(expenseTab, "Expenses");
}

void MainWindow::refreshProfit()
{
    double revenue = 0, expensesTotal = 0;
    for (const auto &inv : *invoices)
        if (inv.isPaid())
            revenue += inv.getAmount();

    for (const auto &exp : *expenses)
        expensesTotal += exp.getCost();

    profitLabel->setText("Profit: $" + QString::number(revenue - expensesTotal));
}

void MainWindow::addInvoice()
{
    InvoiceDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        invoices->push_back(dialog.getInvoice());
        invoiceModel->setInvoices(invoices);
        refreshProfit();
    }
}

void MainWindow::addExpense()
{
    ExpenseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        expenses->push_back(dialog.getExpense());
        expenseModel->setExpenses(expenses);
        refreshProfit();
    }
}