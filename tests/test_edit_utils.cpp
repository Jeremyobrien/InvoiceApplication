#include <QtTest/QtTest>
#include <QTableView>
#include <QStandardItemModel>
#include <QDialog>

#include "../src/ui/EditUtils.h"

//Mocked data
struct FakeItem
{
    int value = 0;
};

struct FakeModel
{
    std::vector<FakeItem> data;
    bool updateCalled = false;
    int updatedRow = -1;
    int updatedValue = -1;

    std::vector<FakeItem>* items()
    {
        return &data;
    }

    void updateRow(int row, const FakeItem& item)
    {
        updateCalled = true;
        updatedRow = row;
        updatedValue = item.value;
        data[row] = item;
    }
};

struct AcceptDialog
{
    FakeItem result{42};

    int exec()
    {
        return QDialog::Accepted;
    }

    FakeItem getResult() const
    {
        return result;
    }
};

struct RejectDialog
{
    int exec()
    {
        return QDialog::Rejected;
    }

    FakeItem getResult() const
    {
        return {};
    }
};

//Test class
class EditSelectedRowTests : public QObject
{
    Q_OBJECT

private slots:
    void no_selection_does_nothing()
    {
        QTableView view;
        FakeModel model;
        model.data.push_back({1});

        editSelectedRow<FakeItem>(
            nullptr,
            &view,
            &model,
            [](QWidget*, FakeItem&) {
                return AcceptDialog{};
            }
        );

        QVERIFY(!model.updateCalled);
    }

        void dialog_rejected_does_not_update()
    {
        QStandardItemModel qtModel(1, 1);
        QTableView view;
        view.setModel(&qtModel);
        view.setCurrentIndex(qtModel.index(0, 0));

        FakeModel model;
        model.data.push_back({10});

        editSelectedRow<FakeItem>(
            nullptr,
            &view,
            &model,
            [](QWidget*, FakeItem&) {
                return RejectDialog{};
            }
        );

        QVERIFY(!model.updateCalled);
        QCOMPARE(model.data[0].value, 10);
    }

        void dialog_accepted_updates_row()
    {
        QStandardItemModel qtModel(1, 1);
        QTableView view;
        view.setModel(&qtModel);
        view.setCurrentIndex(qtModel.index(0, 0));

        FakeModel model;
        model.data.push_back({5});

        editSelectedRow<FakeItem>(
            nullptr,
            &view,
            &model,
            [](QWidget*, FakeItem&) {
                return AcceptDialog{};
            }
        );

        QVERIFY(model.updateCalled);
        QCOMPARE(model.updatedRow, 0);
        QCOMPARE(model.updatedValue, 42);
        QCOMPARE(model.data[0].value, 42);
    }
};

QTEST_MAIN(EditSelectedRowTests)
#include "test_edit_utils.moc"

