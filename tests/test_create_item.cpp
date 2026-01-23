#include <QtTest/QtTest>
#include <QDialog>
#include "../src/ui/CreateUtils.h"

//Mocked data
struct FakeItem { int value = 0; };

struct FakeModel {
    std::vector<FakeItem> data;
    std::vector<FakeItem>* items() { return &data; }
    void refresh() {}
};

struct FakeDialog {
    int exec() { return QDialog::Accepted; }
    FakeItem getResult() { return {42}; }
};

class CreateItemTests : public QObject
{
    Q_OBJECT

private slots:
    void adds_item_on_accept()
    {
        FakeModel model;

        createItem<FakeItem>(
            nullptr,
            &model,
            [](QWidget*) { return FakeDialog{}; }
        );

        QCOMPARE(model.data.size(), size_t(1));
        QCOMPARE(model.data[0].value, 42);
    }
};

QTEST_MAIN(CreateItemTests)
#include "test_create_item.moc"
