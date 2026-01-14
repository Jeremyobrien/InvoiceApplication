#pragma once
#include <QAbstractTableModel>
#include <memory>
#include <vector>
#include "Expense.h"

class ExpenseTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ExpenseTableModel(QObject *parent = nullptr);
    void setExpenses(std::shared_ptr<std::vector<Expense>> expenses);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    std::shared_ptr<std::vector<Expense>> expenses;
};
