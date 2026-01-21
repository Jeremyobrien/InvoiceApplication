#pragma once
#include <QSortFilterProxyModel>

class GenericSearchProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit GenericSearchProxy(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent)
    {
        setFilterCaseSensitivity(Qt::CaseInsensitive);
        setFilterKeyColumn(-1);
    }
};