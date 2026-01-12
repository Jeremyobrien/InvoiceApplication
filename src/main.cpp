#include <iostream>
#include <vector>
#include "Invoice.h"
#include "Expense.h"

int main()
{
    std::vector<Invoice> invoices;
    std::vector<Expense> expenses;

    invoices.emplace_back("Walmart", 1234.00);
    invoices.emplace_back("CoreLogic", 2221.34, true);

    expenses.emplace_back("Azure PaaS", 450.00);
    expenses.emplace_back("Payroll", 1000.00);

    double revenue = 0;
    double costs = 0;

    for (const auto &inv : invoices)
    {
        if (inv.isPaid())
        {
            revenue += inv.getAmount();
        }
    }

    for (const auto &exp : expenses)
    {
        costs += exp.getCost();
    }

    std::cout << "Revenue: $" << revenue << "\n";
    std::cout << "Expenses: $" << costs << "\n";
    std::cout << "Profit: $" << revenue - costs << "\n";

    return 0;
}