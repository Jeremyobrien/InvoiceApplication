#include <QtTest/QtTest>
#include <QTableView>
#include "models/InvoiceTableModel.h"
#include "../src/ui/DeleteUtils.h"

class DeleteSelectedTests : public QObject
{
    Q_OBJECT

private slots:
    void no_selection_does_nothing()
    {
        QTableView view;
        InvoiceTableModel model;

        deleteSelected(nullptr, &view, &model, "t", "m");
        QCOMPARE(model.rowCount(), 0);
    }
};

QTEST_MAIN(DeleteSelectedTests)
#include "test_delete_selected.moc"
