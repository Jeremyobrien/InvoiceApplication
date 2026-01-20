#include "PaidDelegate.h"
#include <QApplication>
#include <QStyle>
#include <QPainter>

PaidDelegate::PaidDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{
}
void PaidDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);

    // Clear default text but keep background and selection
    opt.text.clear();

    // Disable default checkbox drawing
    opt.features &= ~QStyleOptionViewItem::HasCheckIndicator;

    // Draw the cell background, selection, focus, etc.
    QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter);

    // --- Prepare checkbox ---
    QStyleOptionButton checkbox;
    checkbox.state |= QStyle::State_Enabled;
    checkbox.state |= (index.data(Qt::CheckStateRole).toInt() == Qt::Checked)
                        ? QStyle::State_On
                        : QStyle::State_Off;

    QSize checkboxSize = QApplication::style()->sizeFromContents(
        QStyle::CT_CheckBox, &checkbox, QSize(), nullptr);

    // Center checkbox vertically in the cell
    checkbox.rect = QRect(
        option.rect.left() + 4, // small left margin
        option.rect.top() + (option.rect.height() - checkboxSize.height()) / 2,
        checkboxSize.width(),
        checkboxSize.height()
    );

    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkbox, painter);

    // --- Draw text ("Yes"/"No") to the right of the checkbox ---
    QString text = index.data(Qt::DisplayRole).toString();
    QRect textRect = option.rect.adjusted(checkbox.rect.width() + 8, 0, 0, 0);

    painter->drawText(
        textRect,
        Qt::AlignVCenter | Qt::AlignLeft,
        text
    );
}