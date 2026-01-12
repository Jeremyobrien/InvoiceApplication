#include "Invoice.h"
using namespace std;

Invoice::Invoice(string clientName, double amount, bool paid)
    : clientName(clientName), amount(amount), paid(paid) {}

void Invoice::markPaid()
{
    paid = true;
}

double Invoice::getAmount() const
{
    return amount;
}

bool Invoice::isPaid() const
{
    return paid;
}

string Invoice::getClient() const
{
    return clientName;
}

string Invoice::serialize() const
{
    return clientName + "," + to_string(amount) + "," + (paid ? "1" : "0");
}