#include "PaidDelegate.h"
#include <QApplication>
#include <QStyle>
#include <QPainter>
#include <QMouseEvent>

PaidDelegate::PaidDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{
}
void PaidDelegate::paint(QPainter* painter,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    if (!index.isValid())
        return;

    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);

    // Clear default text + checkbox
    opt.text.clear();
    opt.features &= ~QStyleOptionViewItem::HasCheckIndicator;

    // Draw background / selection
    QApplication::style()->drawControl(
        QStyle::CE_ItemViewItem, &opt, painter);

    // ---- Checkbox state ----
    QStyleOptionButton checkbox;
    checkbox.state = QStyle::State_Enabled;
    checkbox.state |= (index.data(Qt::CheckStateRole).toInt() == Qt::Checked)
        ? QStyle::State_On
        : QStyle::State_Off;

    QSize checkboxSize = QApplication::style()->sizeFromContents(
        QStyle::CT_CheckBox, &checkbox, QSize(), nullptr);

    // ---- Text ----
    QString text = index.data(Qt::DisplayRole).toString();
    QFontMetrics fm(option.font);
    int textWidth = fm.horizontalAdvance(text);
    int spacing = 6;

    // ---- Center combined content ----
    int totalWidth = checkboxSize.width() + spacing + textWidth;

    int startX = option.rect.left()
        + (option.rect.width() - totalWidth) / 2;

    int centerY = option.rect.top()
        + (option.rect.height() - checkboxSize.height()) / 2;

    // ---- Checkbox rect ----
    checkbox.rect = QRect(
        startX,
        centerY,
        checkboxSize.width(),
        checkboxSize.height()
    );

    QApplication::style()->drawControl(
        QStyle::CE_CheckBox, &checkbox, painter);

    // ---- Text rect ----
    QRect textRect(
        checkbox.rect.right() + spacing,
        option.rect.top(),
        textWidth,
        option.rect.height()
    );

    painter->drawText(
        textRect,
        Qt::AlignVCenter,
        text
    );
}

QRect PaidDelegate::checkboxRect(
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    QStyleOptionButton checkbox;
    checkbox.state = QStyle::State_Enabled;

    QSize size = QApplication::style()->sizeFromContents(
        QStyle::CT_CheckBox, &checkbox, QSize(), nullptr);

    QString text = index.data(Qt::DisplayRole).toString();
    QFontMetrics fm(option.font);
    int textWidth = fm.horizontalAdvance(text);
    int spacing = 6;

    int totalWidth = size.width() + spacing + textWidth;

    int x = option.rect.left()
        + (option.rect.width() - totalWidth) / 2;

    int y = option.rect.top()
        + (option.rect.height() - size.height()) / 2;

    return QRect(x, y, size.width(), size.height());
}

bool PaidDelegate::editorEvent(QEvent* event,
    QAbstractItemModel* model,
    const QStyleOptionViewItem& option,
    const QModelIndex& index)
{
    if (index.column() != 2)
        return false;

    if (event->type() != QEvent::MouseButtonRelease)
        return false;

    auto* mouse = static_cast<QMouseEvent*>(event);

    QRect box = checkboxRect(option, index);

    if (!box.contains(mouse->pos()))
        return false;

    Qt::CheckState state =
        index.data(Qt::CheckStateRole).toInt() == Qt::Checked
        ? Qt::Unchecked
        : Qt::Checked;

    return model->setData(index, state, Qt::CheckStateRole);
}

