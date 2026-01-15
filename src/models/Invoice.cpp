#include "Invoice.h"

bool Invoice::isPaid() const { return paid; }
double Invoice::getAmount() const { return amount; }
std::string Invoice::getClient() const { return clientName; }
