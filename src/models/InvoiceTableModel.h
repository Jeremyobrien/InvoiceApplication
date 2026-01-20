#pragma once

#include <QAbstractTableModel>
#include <memory>
#include <vector>
#include "Invoice.h"

class InvoiceTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit InvoiceTableModel(QObject *parent = nullptr);
    void setInvoices(std::shared_ptr<std::vector<Invoice>> invoices);
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    std::vector<Invoice> *items();
    void updateRow(int row, const Invoice &updated);
    void refresh();
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    std::shared_ptr<std::vector<Invoice>> invoices;
};