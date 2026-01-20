#include "MainWindow.h"
#include "dialogs/InvoiceDialog.h"
#include "dialogs/ExpenseDialog.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <iostream>
#include "import/ImportMode.h"
#include "import/ImportResult.h"
#include "import/JsonImporter.h"
#include "import/CsvImporter.h"
#include "import/ImportUtils.h"
#include "export/ExportService.h"
#include "ui/EditUtils.h"
#include "ui/CreateUtils.h"
#include "ui/DeleteUtils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      invoices(std::make_shared<std::vector<Invoice>>()),
      expenses(std::make_shared<std::vector<Expense>>())
{
    setupTabs();
}

void MainWindow::setupTabs()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    profitLabel = new QLabel("Profit: $0", this);

    auto *mainLayout = new QVBoxLayout(central);

    // ---- Tabs ----
    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(profitLabel);

    // ---- Import / Export buttons ----
    auto *buttonLayout = new QHBoxLayout();

    auto *importBtn = new QPushButton("Import", this);
    auto *exportBtn = new QPushButton("Export", this);

    buttonLayout->addStretch();
    buttonLayout->addWidget(importBtn);
    buttonLayout->addWidget(exportBtn);

    connect(importBtn, &QPushButton::clicked,
            this, &MainWindow::importData);
    connect(exportBtn, &QPushButton::clicked,
            this, &MainWindow::exportData);

    mainLayout->addLayout(buttonLayout);

    // ---- Invoice tab ----
    auto *invoiceTab = new QWidget(this);
    auto *invoiceLayout = new QVBoxLayout(invoiceTab);

    invoiceModel = new InvoiceTableModel(this);
    invoiceModel->setInvoices(invoices);

    invoiceView = new QTableView(invoiceTab);
    invoiceView->setModel(invoiceModel);
    invoiceView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    invoiceView->setAlternatingRowColors(true);
    invoiceView->setSelectionBehavior(QAbstractItemView::SelectRows);
    invoiceView->setSelectionMode(QAbstractItemView::SingleSelection);

    auto *addInvoiceBtn = new QPushButton("Add Invoice", invoiceTab);
    connect(addInvoiceBtn, &QPushButton::clicked,
            this, &MainWindow::addInvoice);

    QPushButton *deleteInvoiceBtn = new QPushButton("Delete Invoice");
    connect(deleteInvoiceBtn, &QPushButton::clicked,
            this, &MainWindow::deleteInvoice);

    auto *editInvoiceBtn = new QPushButton("Edit Invoice");
    connect(editInvoiceBtn, &QPushButton::clicked,
            this, &MainWindow::editInvoice);

    invoiceLayout->addWidget(invoiceView);
    invoiceLayout->addWidget(addInvoiceBtn);
    invoiceLayout->addWidget(deleteInvoiceBtn);
    invoiceLayout->addWidget(editInvoiceBtn);

    tabWidget->addTab(invoiceTab, "Invoices");

    // ---- Expense tab ----
    auto *expenseTab = new QWidget(this);
    auto *expenseLayout = new QVBoxLayout(expenseTab);

    expenseModel = new ExpenseTableModel(this);
    expenseModel->setExpenses(expenses);

    expenseView = new QTableView(expenseTab);
    expenseView->setModel(expenseModel);
    expenseView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    expenseView->setAlternatingRowColors(true);
    expenseView->setSelectionBehavior(QAbstractItemView::SelectRows);
    expenseView->setSelectionMode(QAbstractItemView::SingleSelection);

    auto *addExpenseBtn = new QPushButton("Add Expense", expenseTab);
    connect(addExpenseBtn, &QPushButton::clicked,
            this, &MainWindow::addExpense);
    QPushButton *deleteExpenseBtn = new QPushButton("Delete Expense");
    connect(deleteExpenseBtn, &QPushButton::clicked,
            this, &MainWindow::deleteExpense);
    auto *editExpenseBtn = new QPushButton("Edit Expense");
    connect(editExpenseBtn, &QPushButton::clicked,
            this, &MainWindow::editExpense);

    expenseLayout->addWidget(expenseView);
    expenseLayout->addWidget(addExpenseBtn);
    expenseLayout->addWidget(deleteExpenseBtn);
    expenseLayout->addWidget(editExpenseBtn);

    tabWidget->addTab(expenseTab, "Expenses");

    // ---- Menu (single entry points) ----
    QMenu *fileMenu = menuBar()->addMenu("&File");

    QAction *importAction = new QAction("Import…", this);
    QAction *exportAction = new QAction("Export…", this);

    connect(importAction, &QAction::triggered,
            this, &MainWindow::importData);
    connect(exportAction, &QAction::triggered,
            this, &MainWindow::exportData);

    fileMenu->addAction(importAction);
    fileMenu->addAction(exportAction);
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
    createItem<Invoice>(
        this,
        invoiceModel,
        [](QWidget* parent) {
            return InvoiceDialog(parent);
        }
    );

    refreshProfit();
}

void MainWindow::addExpense()
{
    createItem<Expense>(
        this,
        expenseModel,
        [](QWidget* parent) {
            return ExpenseDialog(parent);
        }
    );

    refreshProfit();
}

void MainWindow::exportData()
{
    QString filter = "CSV Files (*.csv);;JSON Files (*.json)";
    QString filePath = QFileDialog::getSaveFileName(
        this, "Export Data", "", filter);

    if (filePath.isEmpty())
        return;

    ExportFormat format;
    if (filePath.endsWith(".csv", Qt::CaseInsensitive))
        format = ExportFormat::Csv;
    else if (filePath.endsWith(".json", Qt::CaseInsensitive))
        format = ExportFormat::Json;
    else
    {
        QMessageBox::warning(this, "Error", "Unsupported file format");
        return;
    }

    auto exporter = ExportService::createExporter(format);

    QString error;
    if (!exporter->exportData(filePath, *invoices, *expenses, error))
    {
        QMessageBox::warning(this, "Export Failed", error);
        return;
    }

    QMessageBox::information(this, "Export Complete", "Export successful");
}

void MainWindow::importData()
{
    QString filter = "JSON Files (*.json);;CSV Files (*.csv)";
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Import Data",
        "",
        filter);

    if (filePath.isEmpty())
        return;

    std::optional<ImportMode> modeOpt = askImportMode();
    if (!modeOpt.has_value())
        return;

    ImportMode mode = *modeOpt;
    std::optional<ImportResult> result;

    if (filePath.endsWith(".json", Qt::CaseInsensitive))
    {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this, "Error", "Cannot open JSON file");
            return;
        }

        result = JsonImporter::parse(file.readAll());
    }
    else if (filePath.endsWith(".csv", Qt::CaseInsensitive))
    {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, "Error", "Cannot open CSV file");
            return;
        }

        result = CsvImporter::parse(file.readAll());
    }
    else
    {
        QMessageBox::warning(this, "Error", "Unsupported file format");
    }

    if (!result.has_value())
    {
        QMessageBox::warning(this, "Error", "Faild to parse file");
        return;
    }

    applyImport(*invoices, result->invoices, mode);
    applyImport(*expenses, result->expenses, mode);

    invoiceModel->setInvoices(invoices);
    expenseModel->setExpenses(expenses);
    refreshProfit();

    QMessageBox::information(this, "Import Complete", "Data imported successfully");
}

ImportMode MainWindow::askImportMode()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Import Data");
    msgBox.setText("How would you like to import the data?");
    msgBox.setInformativeText(
        "Replace will delete existing data.\n"
        "Merge will add to existing data.");

    QPushButton *replaceBtn =
        msgBox.addButton("Replace", QMessageBox::DestructiveRole);
    QPushButton *mergeBtn =
        msgBox.addButton("Merge", QMessageBox::AcceptRole);
    msgBox.addButton(QMessageBox::Cancel);

    msgBox.exec();

    if (msgBox.clickedButton() == replaceBtn)
        return ImportMode::Replace;

    if (msgBox.clickedButton() == mergeBtn)
        return ImportMode::Merge;

    throw std::runtime_error("Import canceled");
}

void MainWindow::deleteInvoice()
{
    deleteSelected(
        this,
        invoiceView,
        invoiceModel,
        "Delete Invoice",
        "Are you sure you want to delete this invoice?"
    );

    refreshProfit();
}

void MainWindow::deleteExpense()
{
    deleteSelected(
        this,
        expenseView,
        expenseModel,
        "Delete Expense",
        "Are you sure you want to delete this expense?"
    );

    refreshProfit();
}

void MainWindow::editInvoice()
{
    editSelectedRow<Invoice>(
        this,
        invoiceView,
        invoiceModel,
        [](QWidget *parent, const Invoice &inv)
        {
            return InvoiceDialog(parent, inv);
        });

    refreshProfit();
}

void MainWindow::editExpense()
{
    editSelectedRow<Expense>(
        this,
        expenseView,
        expenseModel,
        [](QWidget *parent, const Expense &exp)
        {
            return ExpenseDialog(parent, exp);
        });

    refreshProfit();
}