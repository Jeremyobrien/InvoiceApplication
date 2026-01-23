#include <QtTest/QtTest>
#include <QLineEdit>
#include <QTableView>
#include <QStandardItemModel>

#include "ui/SearchBinder.h"

class BindSearchTests : public QObject
{
    Q_OBJECT

private slots:
    void proxy_is_configured()
    {
        QLineEdit search;
        QTableView table;
        QStandardItemModel model;

        auto* proxy = bindSearch(&table, &search, &table, &model);

        QVERIFY(proxy->sourceModel() == &model);
        QVERIFY(table.model() == proxy);
    }
};

QTEST_MAIN(BindSearchTests)
#include "test_bind_search.moc"
