#include <QtTest/QtTest>
#include <QTableView>
#include <QTimer>
#include <QMessageBox>
#include <QPushButton>
#include "models/InvoiceTableModel.h"
#include "../src/ui/DeleteUtils.h"

class DeleteSelectedTests : public QObject
{
    Q_OBJECT

private slots:
    // Exercises: The guard clause "if (!index.isValid()) return;"
    void no_selection_does_nothing()
    {
        QTableView view;
        InvoiceTableModel model;
        // Current index is invalid by default
        deleteSelected(nullptr, &view, &model, "Title", "Message");
        QCOMPARE(model.rowCount(QModelIndex()), 0);
    }

    // Exercises: The "Yes" branch and the model interaction
    void delete_confirmed_removes_row()
    {
        // 1. Setup Data
        auto model = std::make_unique<InvoiceTableModel>();
        auto data = std::make_shared<std::vector<Invoice>>();
        Invoice inv; inv.setClient("To Be Deleted");
        data->push_back(inv);
        model->setInvoices(data);

        QTableView view;
        view.setModel(model.get());
        view.setCurrentIndex(model->index(0, 0));

        // 2. Schedule a "human" click on the 'Yes' button
        // Since QMessageBox::question is blocking, we use a single-shot timer
        // to find the active message box and click 'Yes' as soon as it appears.
        QTimer::singleShot(500, []() {
            QWidget* widget = QApplication::activeModalWidget();
            if (auto* box = qobject_cast<QMessageBox*>(widget)) {
                // Find the 'Yes' button and click it
                QAbstractButton* yesButton = box->button(QMessageBox::Yes);
                yesButton->click();
            }
            });

        // 3. Execute the function
        deleteSelected(nullptr, &view, model.get(), "Title", "Confirm Delete?");

        // 4. Verify result
        QCOMPARE(model->rowCount(QModelIndex()), 0);
    }

    // Exercises: The "No" branch
    void delete_cancelled_keeps_row()
    {
        auto model = std::make_unique<InvoiceTableModel>();
        auto data = std::make_shared<std::vector<Invoice>>();
        data->push_back(Invoice());
        model->setInvoices(data);

        QTableView view;
        view.setModel(model.get());
        view.setCurrentIndex(model->index(0, 0));

        // Schedule 'No' click
        QTimer::singleShot(500, []() {
            if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget())) {
                box->button(QMessageBox::No)->click();
            }
            });

        deleteSelected(nullptr, &view, model.get(), "Title", "Delete?");

        QCOMPARE(model->rowCount(QModelIndex()), 1);
    }
};

QTEST_MAIN(DeleteSelectedTests)
#include "test_delete_selected.moc"