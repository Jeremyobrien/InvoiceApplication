#include "ExpenseTableModel.h"
#include <QString>
#include <Qt>
#include <QFlags>
#include <QVariant>

ExpenseTableModel::ExpenseTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void ExpenseTableModel::setExpenses(std::shared_ptr<std::vector<Expense>> expenses_)
{
    beginResetModel(); // 1. Notify view data is changing
    expenses = expenses_;
    endResetModel(); // 2. Notify view data reset is complete
}

int ExpenseTableModel::rowCount(const QModelIndex &) const
{
    return expenses ? static_cast<int>(expenses->size()) : 0;
}

int ExpenseTableModel::columnCount(const QModelIndex &) const
{
    return 2; // Description, Amount
}

QVariant ExpenseTableModel::data(const QModelIndex &index, int role) const
{
    if (!expenses || !index.isValid())
        return QVariant();

    const auto &exp = expenses->at(index.row());

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (index.column())
        {
        case 0:
            return QString::fromStdString(exp.getDescription());
        case 1:
            return exp.getCost();
        default:
            return QVariant();
        }
    }

    if (role == Qt::TextAlignmentRole)
    {
        return QVariant::fromValue(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    return QVariant();
}

QVariant ExpenseTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section)
    {
    case 0:
        return "Description";
    case 1:
        return "Amount";
    default:
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole)
    {
        return QVariant::fromValue(Qt::AlignHCenter | Qt::AlignVCenter);
    }
}

std::vector<Expense>* ExpenseTableModel::items()
{
    return expenses.get();
}

void ExpenseTableModel::updateRow(int row, const Expense& updated)
{
    (*expenses)[row] = updated;
    emit dataChanged(index(row, 0), index(row, columnCount() -1));
}

void ExpenseTableModel::refresh()
{
    beginResetModel();
    endResetModel();
}

Qt::ItemFlags ExpenseTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsSelectable
         | Qt::ItemIsEnabled
         | Qt::ItemIsEditable;
}

bool ExpenseTableModel::setData(
    const QModelIndex &index,
    const QVariant &value,
    int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    Expense &expense = (*expenses)[index.row()];

    switch (index.column())
    {
    case 0:
        expense.setDescription(value.toString().toStdString());
        break;
    case 1:
        expense.setCost(value.toDouble());
        break;
    default:
        return false;
    }

    emit dataChanged(index, index);
    return true;
}


