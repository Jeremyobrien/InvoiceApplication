#pragma once
#include <QLineEdit>
#include <QTableView>
#include <QSortFilterProxyModel>

template<typename ModelT>
QSortFilterProxyModel* bindSearch(
    QObject* owner,
    QLineEdit* searchBox,
    QTableView* table,
    ModelT* model
)
{
    auto* proxy = new QSortFilterProxyModel(owner);
    proxy->setSourceModel(model);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(-1);

    table->setModel(proxy);

    QObject::connect(
        searchBox, &QLineEdit::textChanged,
        proxy, [proxy](const QString& text)
        {
            proxy->setFilterRegularExpression(
                QRegularExpression(text, QRegularExpression::CaseInsensitiveOption)
            );
        });
        
    return proxy;
}