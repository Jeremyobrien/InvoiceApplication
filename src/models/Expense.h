#pragma once

#include <string>

class Expense
{
private:
    std::string description;
    double cost;

public:
    Expense(std::string description, double cost)
        : description(std::move(description)), cost(cost) {}

    double getCost() const { return cost; }
    std::string getDescription() const { return description; }
};