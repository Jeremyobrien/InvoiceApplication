#pragma once

#include <QTableView>
#include <QMessageBox>

template<
    typename Item,
    typename Model,
    typename DialogFactory
    >
void editSelectedRow(
    QWidget* parent,
    QTableView* view,
    Model* model,
    DialogFactory createDialog
)
{
    QModelIndex index = view->currentIndex();
    if (!index.isValid())
        return;
    
    int row = index.row();
    Item& item = (*model->items())[row];

    auto dialog = createDialog(parent, item);
    if (dialog.exec() == QDialog::Accepted)
    {
        model->updateRow(row, dialog.getResult());
    }
}