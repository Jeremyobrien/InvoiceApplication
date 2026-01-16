#pragma once

#include <vector>
#include "models/Invoice.h"
#include "models/Expense.h"

struct ImportResult
{
    std::vector<Invoice> invoices;
    std::vector<Expense> expenses;
};