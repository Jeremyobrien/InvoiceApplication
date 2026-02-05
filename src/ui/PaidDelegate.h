#pragma once
#include <QStyledItemDelegate>

class PaidDelegate : public QStyledItemDelegate
{
        Q_OBJECT
    public:
        explicit PaidDelegate(QObject *parent = nullptr);
        using QStyledItemDelegate::QStyledItemDelegate;
        void paint(QPainter *painter,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
        bool editorEvent(QEvent* event, QAbstractItemModel* model, 
                const QStyleOptionViewItem& option, const QModelIndex& index);
        QRect checkboxRect(const QStyleOptionViewItem& option, const QModelIndex& index) const;
};