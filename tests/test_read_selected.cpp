#include <QtTest/QtTest>
#include <QTableView>
#include "ui/ReadUtils.h"

class ReadSelectedTests : public QObject
{
    Q_OBJECT

private slots:
    void no_selection_returns_nullopt()
    {
        QTableView view;
        struct Model {
            std::vector<int> data;
            std::vector<int>* items() { return &data; }
        } model;

        auto result = readSelected<int>(&view, &model);
        QVERIFY(!result.has_value());
    }
};

QTEST_MAIN(ReadSelectedTests)
#include "test_read_selected.moc"
