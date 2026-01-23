#pragma once
#include <QSortFilterProxyModel>

class GenericSearchProxy : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit GenericSearchProxy(QObject *parent = nullptr);
};
