#include "Expense.h"

Expense::Expense(std::string description, double cost)
    : description(description), cost(cost) {}

double Expense::getCost() const
{
    return cost;
}

std::string Expense::serialize() const
{
    return description + "," + std::to_string(cost);
}