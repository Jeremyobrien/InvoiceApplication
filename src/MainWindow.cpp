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

    profitLabel = new QLabel("Profit: $0");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    central->setLayout(mainLayout);

    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(profitLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *importBtn = new QPushButton("Import");
    QPushButton *exportBtn = new QPushButton("Export");

    buttonLayout->addStretch();
    buttonLayout->addWidget(importBtn);
    buttonLayout->addWidget(exportBtn);
    connect(importBtn, &QPushButton::clicked,
            this, &MainWindow::importData);
    connect(exportBtn, &QPushButton::clicked,
            this, &MainWindow::exportData);

    mainLayout->addLayout(buttonLayout);

    QWidget *invoiceTab = new QWidget();
    QVBoxLayout *invoiceLayout = new QVBoxLayout(invoiceTab);

    invoiceModel = new InvoiceTableModel(this);
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

    // Export Logic
    QMenu *fileMenu = menuBar()->addMenu("&File");

    QAction *importCsvAction = new QAction("Import CSV", this);
    QAction *importJsonAction = new QAction("Import JSON", this);

    fileMenu->addAction(importCsvAction);
    fileMenu->addAction(importJsonAction);

    connect(importCsvAction, &QAction::triggered, this, &MainWindow::importData);
    connect(importJsonAction, &QAction::triggered, this, &MainWindow::importData);

    QAction *exportCsvAction = new QAction("Export CSV", this);
    QAction *exportJsonAction = new QAction("Export JSON", this);

    fileMenu->addAction(exportCsvAction);
    fileMenu->addAction(exportJsonAction);

    connect(exportCsvAction, &QAction::triggered, this, [this]()
            {
        QString filePath = QFileDialog::getSaveFileName(
            this,
            "Export CSV",
            "",
            "CSV Files (*.csv)"
        );
        if (!filePath.isEmpty())
            exportCsv(filePath); });

    connect(exportJsonAction, &QAction::triggered, this, [this]()
            {
        QString filePath = QFileDialog::getSaveFileName(
            this,
            "Export JSON",
            "",
            "JSON Files (*.json)"
        );
        if (!filePath.isEmpty())
            exportJson(filePath); });
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

void MainWindow::exportData()
{
    QString filter = "CSV Files (*.csv);;JSON Files (*.json)";
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Export Data",
        "",
        filter);

    if (filePath.isEmpty())
        return;

    if (filePath.toLower().endsWith(".csv"))
    {
        exportCsv(filePath);
    }
    else if (filePath.toLower().endsWith(".json"))
    {
        exportJson(filePath);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Unsupported file format");
    }
}
void MainWindow::exportCsv(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << "Invoices\n";
    out << "Client, Amount, Paid\n";

    for (const auto &inv : *invoices)
    {
        out << QString::fromStdString(inv.getClient()) << ","
            << inv.getAmount() << ","
            << (inv.isPaid() ? "Yes" : "No") << "\n";
    }

    out << "\n";

    out << "Expenses\n";
    out << "Description, Cost\n";

    for (const auto &exp : *expenses)
    {
        out << QString::fromStdString(exp.getDescription()) << ","
            << exp.getCost() << "\n";
    }

    file.close();

    QMessageBox::information(this, "Export Complete", "CSV export successful");
}

void MainWindow::exportJson(const QString &filePath)
{
    QJsonObject root;

    QJsonArray invoiceArray;
    for (const auto &inv : *invoices)
    {
        QJsonObject obj;
        obj["client"] = QString::fromStdString(inv.getClient());
        obj["amount"] = inv.getAmount();
        obj["paid"] = inv.isPaid();
        invoiceArray.append(obj);
    }
    root["invoices"] = invoiceArray;

    QJsonArray expenseArray;
    for (const auto &exp : *expenses)
    {
        QJsonObject obj;
        obj["description"] = QString::fromStdString(exp.getDescription());
        obj["cost"] = exp.getCost();
        expenseArray.append(obj);
    }
    root["expenses"] = expenseArray;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Error", "Could not open file");
        return;
    }

    QJsonDocument doc(root);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    QMessageBox::information(this, "Export Complete", "JSON export successful");
}

QString MainWindow::chooseFile(const QString &filter)
{
    return QFileDialog::getOpenFileName(
        this,
        "Select File",
        "",
        filter);
}

void MainWindow::importCsv(QString filePath)
{
    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Cannot open file");
        return;
    }

    invoices->clear();
    expenses->clear();

    QTextStream in(&file);
    QString line;
    bool readingInvoices = false;
    bool readingExpenses = false;

    while (!in.atEnd())
    {
        line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        if (line.startsWith("Invoices"))
        {
            readingInvoices = true;
            readingExpenses = false;
            in.readLine();
            continue;
        }
        if (line.startsWith("Expenses"))
        {
            readingExpenses = true;
            readingInvoices = false;
            in.readLine();
            continue;
        }

        QStringList parts = line.split(',');
        if (readingInvoices && parts.size() == 3)
        {
            Invoice inv;
            inv.setClient(parts[0].toStdString());
            inv.setAmount(parts[1].toDouble());
            inv.setPaid(parts[2].trimmed().toLower() == "yes");
            invoices->push_back(inv);
        }
        else if (readingExpenses && parts.size() == 2)
        {
            Expense exp;
            exp.setDescription(parts[0].toStdString());
            exp.setCost(parts[1].toDouble());
            expenses->push_back(exp);
        }
    }

    invoiceModel->setInvoices(invoices);
    expenseModel->setExpenses(expenses);
    refreshProfit();

    QMessageBox::information(this, "Import Complete", "CSV import successful");
}

void MainWindow::importJson(QString filePath)
{
    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Error", "Cannot open file");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject())
    {
        QMessageBox::warning(this, "Error", "Invalid JSON format");
        return;
    }

    QJsonObject root = doc.object();
    invoices->clear();
    expenses->clear();

    QJsonArray invoiceArray = root["invoices"].toArray();
    for (const QJsonValue &val : invoiceArray)
    {
        QJsonObject obj = val.toObject();
        Invoice inv;

        inv.setClient(obj["client"].toString().toStdString());
        inv.setAmount(obj["amount"].toDouble());
        inv.setPaid(obj["paid"].toBool());
        invoices->push_back(inv);
    }

    QJsonArray expenseArray = root["expenses"].toArray();
    for (const QJsonValue &val : expenseArray)
    {
        QJsonObject obj = val.toObject();
        Expense exp;
        exp.setDescription(obj["description"].toString().toStdString());
        exp.setCost(obj["cost"].toDouble());
        expenses->push_back(exp);
    }

    invoiceModel->setInvoices(invoices);
    expenseModel->setExpenses(expenses);
    refreshProfit();

    QMessageBox::information(this, "Import Complete", "JSON import successful");
}

void MainWindow::importData()
{
    QString filter = "JSON File (*.json);;CSV Files (*.csv)";
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Import Data",
        "",
        filter);

    if (filePath.isEmpty())
        return;

    if (filePath.endsWith(".json", Qt::CaseInsensitive))
    {
        importJson(filePath);
    }
    else if (filePath.endsWith(".csv", Qt::CaseInsensitive))
    {
        importCsv(filePath);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Unsupported file format");
    }
}