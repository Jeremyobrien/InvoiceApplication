#include <string>
#include "Expense.h"

std::string description;
double cost;

double Expense::getCost() const { return cost; }
std::string Expense::getDescription() const { return description; }
