#include "GenericSearchProxy.h"

GenericSearchProxy::GenericSearchProxy(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterKeyColumn(-1);
}
