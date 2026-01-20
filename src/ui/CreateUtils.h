#pragma once

template<typename Item, typename Model, typename DialogFactory>
void createItem(
    QWidget* parent,
    Model* model,
    DialogFactory createDialog
)
{
    auto dialog = createDialog(parent);

    if (dialog.exec() == QDialog::Accepted)
    {
        model->items()->push_back(dialog.getResult());
        model->refresh();
    }
};
