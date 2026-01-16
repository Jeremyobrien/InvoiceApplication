#pragma once

#include <string>
class Invoice
{
private:
    std::string clientName;
    double amount;
    bool paid;

public:
    Invoice() = default;
    Invoice(std::string clientName, double amount, bool paid = false)
        : clientName(std::move(clientName)), amount(amount), paid(paid) {}

    double getAmount() const;
    bool isPaid() const;
    std::string getClient() const;

    void setClient(const std::string& client);
    void setAmount(double amount);
    void setPaid(bool paid);
};