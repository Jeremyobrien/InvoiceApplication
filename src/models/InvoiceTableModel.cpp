
#include "InvoiceTableModel.h"
#include <QString>
#include <Qt>
#include <QFlags>
#include <QVariant>

InvoiceTableModel::InvoiceTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void InvoiceTableModel::setInvoices(std::shared_ptr<std::vector<Invoice>> invoices_)
{
    beginResetModel();
    invoices = invoices_;
    endResetModel();
}

int InvoiceTableModel::rowCount(const QModelIndex &) const
{
    return invoices ? static_cast<int>(invoices->size()) : 0;
}

int InvoiceTableModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant InvoiceTableModel::data(const QModelIndex &index, int role) const
{
    if (!invoices || !index.isValid())
        return QVariant();

    const auto &inv = invoices->at(index.row());

    // Display the cell text
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            return QString::fromStdString(inv.getClient());
        case 1:
            return inv.getAmount();
        case 2:
            return inv.isPaid() ? "Yes" : "No";
        default:
            return QVariant();
        }
    }

    // Align text in the center
    if (role == Qt::TextAlignmentRole)
    {
        return QVariant::fromValue(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    return QVariant();
}

QVariant InvoiceTableModel::headerData(int section,
                                       Qt::Orientation orientation,
                                       int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section)
    {
    case 0:
        return "Client";
    case 1:
        return "Amount";
    case 2:
        return "Paid";
    default:
        return QVariant();
    }
}

bool InvoiceTableModel::removeRows(int row, int count, const QModelIndex &)
{
    if (!invoices || row < 0 || row + count > invoices->size())
        return false;
    
    beginRemoveRows(QModelIndex(), row, row + count -1);
    invoices->erase(invoices->begin() + row,
                    invoices->begin() + row + count);
    endRemoveRows();

    return true;
}

std::vector<Invoice>* InvoiceTableModel::items()
{
    return invoices.get();
}

void InvoiceTableModel::updateRow(int row, const Invoice& updated)
{
    (*invoices)[row] = updated;
    emit dataChanged(index(row, 0), index(row, columnCount()-1));
}

void InvoiceTableModel::refresh()
{
    beginResetModel();
    endResetModel();
}