#include <string>
#include "Expense.h"

double Expense::getCost() const { return cost; }
std::string Expense::getDescription() const { return description; }
void Expense::setCost(double cost_)
{
    cost = cost_;
}

void Expense::setDescription(const std::string& description_)
{
    description = description_;
}
