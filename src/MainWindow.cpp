#include "MainWindow.h"
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();

    invoiceTable = new QTableWidget(0, 3);
    invoiceTable->setHorizontalHeaderLabels({"Client", "Amount", "Paid"});

    QPushButton *addInvoiceBtn = new QPushButton("Add Invoice");
    profitLabel = new QLabel("Profit: $0");

    connect(addInvoiceBtn, &QPushButton::clicked,
            this, &MainWindow::addInvoice);

    layout->addWidget(invoiceTable);
    layout->addWidget(addInvoiceBtn);
    layout->addWidget(profitLabel);

    central->setLayout(layout);
    setCentralWidget(central);
}

void MainWindow::refreshUI() {
    invoiceTable->setRowCount(0);

    double revenue = 0;
    double expensesTotal = 0;

    for (const auto& inv : invoices) {
        int row = invoiceTable->rowCount();
        invoiceTable->insertRow(row);

        invoiceTable->setItem(row, 0,
        new QTableWidgetItem(
            QString::fromStdString(inv.getClient())
        ));

        invoiceTable->setItem(row, 1, 
            new QTableWidgetItem(
                QString::number(inv.getAmount())
            ));
        
        invoiceTable->setItem(row, 2,
        new QTableWidgetItem(inv.isPaid() ? "Yes" : "No"));

        if (inv.isPaid())
            revenue += inv.getAmount();
    }

    for (const auto& exp : expenses)
        expensesTotal += exp.getCost();

    profitLabel->setText("Profit: $" + QString::number(revenue - expensesTotal));
}

void MainWindow::addInvoice() {
    InvoiceDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        invoices.emplace_back(
            dialog.client().toStdString(),
            dialog.amount(),
            dialog.isPaid()
        );
        refreshUI();
    }
}

void MainWindow::addExpense() {
    InvoiceDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        invoices.emplace_back(
            dialog.client().toStdString(),
            dialog.amount(),
            dialog.isPaid()
        );
        refreshUI();
    }
}

