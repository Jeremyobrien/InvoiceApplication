#include "Invoice.h"

bool Invoice::isPaid() const { return paid; }
double Invoice::getAmount() const { return amount; }
std::string Invoice::getClient() const { return clientName; }

void Invoice::setClient(const std::string& client_)
{
    clientName = client_;
}

void Invoice::setAmount(double amount_)
{
    amount = amount_;
}

void Invoice::setPaid(bool paid_)
{
    paid = paid_;
}