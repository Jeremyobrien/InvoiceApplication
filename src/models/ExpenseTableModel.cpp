#include "ExpenseTableModel.h"
#include <QString>

ExpenseTableModel::ExpenseTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

void ExpenseTableModel::setExpenses(std::shared_ptr<std::vector<Expense>> expenses_)
{
    beginResetModel();  // 1. Notify view data is changing
    expenses = expenses_;
    endResetModel();    // 2. Notify view data reset is complete
}

int ExpenseTableModel::rowCount(const QModelIndex&) const
{
    return expenses ? static_cast<int>(expenses->size()) : 0;
}

int ExpenseTableModel::columnCount(const QModelIndex&) const
{
    return 2; // Description, Amount
}

QVariant ExpenseTableModel::data(const QModelIndex& index, int role) const
{
    if (!expenses || !index.isValid() || role != Qt::DisplayRole) return QVariant();

    const auto& exp = expenses->at(index.row());
    switch (index.column())
    {
    case 0: return QString::fromStdString(exp.getDescription());
    case 1: return exp.getCost();
    default: return QVariant();
    }
}

QVariant ExpenseTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return QVariant();

    switch (section)
    {
    case 0: return "Description";
    case 1: return "Amount";
    default: return QVariant();
    }
}
