#pragma once
#include <QMessageBox>
#include <QtWidgets/qtableview.h>

template<typename Model>
void deleteSelected(
    QWidget* parent,
    QTableView* view,
    Model* model,
    const QString& title,
    const QString& message
)
{
    QModelIndex index = view->currentIndex();
    if (!index.isValid())
        return;

    int row = index.row();

    auto reply = QMessageBox::question(
        parent,
        title,
        message,
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes)
    {
        model->items()->erase(model->items()->begin() + row);
        model->refresh();
    }
};
