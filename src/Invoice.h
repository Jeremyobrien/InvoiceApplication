#ifndef INVOICE_H
#define INVOICE_H

#include <string>
class Invoice
{
private:
    std::string clientName;
    double amount;
    bool paid;

public:
    Invoice(std::string clientName, double amount, bool paid = false);

    void markPaid();
    double getAmount() const;
    bool isPaid() const;
    std::string getClient() const;

    std::string serialize() const;
};

#endif