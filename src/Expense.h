#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>

class Expense
{
private:
    std::string description;
    double cost;

public:
    Expense(std::string description, double cost);
    double getCost() const;
    std::string serialize() const;
};

#endif