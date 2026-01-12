#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include "Invoice.h"
#include "Expense.h"

class FileManager
{
public:
    static void save(
        const std::vector<Invoice> &invoices,
        const std::vector<Expense> &expenses);
};

#endif