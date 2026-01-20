
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
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (index.column())
        {
        case 0:
            return QString::fromStdString(inv.getClient());
        case 1:
            return inv.getAmount();
        case 2:
            return inv.isPaid() ? QVariant("Yes"): QVariant("No");
        default:
            return QVariant();
        }
    }

    // Align text in the center
    if (role == Qt::TextAlignmentRole && index.column() != 2)
    {
        return QVariant::fromValue(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    if (role == Qt::CheckStateRole && index.column() == 2)
        return inv.isPaid() ? Qt::Checked : Qt::Unchecked;

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

Qt::ItemFlags InvoiceTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    
    if (index.column() == 2) // Paid checkbox override
        return Qt::ItemIsSelectable
             | Qt::ItemIsEnabled
             | Qt::ItemIsEditable
             | Qt::ItemIsUserCheckable;

    return Qt::ItemIsSelectable
        |  Qt::ItemIsEnabled
        |  Qt::ItemIsEditable;
}

bool InvoiceTableModel::setData(
    const QModelIndex &index,
    const QVariant &value,
    int role)
{
    if (!index.isValid())
        return false;
    
    Invoice &invoice = (*invoices)[index.row()];

    if (role == Qt::CheckStateRole && index.column() == 2)
    {
        invoice.setPaid(value.toInt() == Qt::Checked);
        emit dataChanged(index, index, {Qt::CheckStateRole});
        return true;
    }

    if (role != Qt::EditRole)
        return false;
    
    switch (index.column())
    {
        case 0:
            invoice.setClient(value.toString().toStdString());
            break;
        case 1:
            invoice.setAmount(value.toDouble());
            break;
        case 2:
            invoice.setPaid(value.toBool());
            break;
        default:
            return false;
    }

    emit dataChanged(index, index);
    return true;
}