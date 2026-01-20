#pragma once
#include <optional>

template <typename Item, typename Model>
std::optional<std::reference_wrapper<const Item>>
readSelected(
    QTableView *view,
    Model *model)
{
    QModelIndex index = view->currentIndex();
    if (!index.isValid())
        return std::nullopt;

    return std::cref((*model->items())[index.row()]);
};
