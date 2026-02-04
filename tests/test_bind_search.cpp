#include <QtTest/QtTest>
#include <QLineEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

#include "ui/SearchBinder.h"

class BindSearchTests : public QObject
{
    Q_OBJECT

private slots:
    // Exercises: Initial configuration logic
    void proxy_is_configured_correctly()
    {
        QLineEdit search;
        QTableView table;
        QStandardItemModel model(2, 1); // 2 rows, 1 column
        model.setData(model.index(0, 0), "Apple");
        model.setData(model.index(1, 0), "Banana");

        // The 'this' refers to the test object as the owner
        auto* proxy = bindSearch(this, &search, &table, &model);

        // Verify Structural Integrity
        QVERIFY(proxy != nullptr);
        QCOMPARE(proxy->sourceModel(), &model);
        QCOMPARE(table.model(), proxy);

        // Verify Default State (Column -1 means search all columns)
        QCOMPARE(proxy->filterKeyColumn(), -1);
        QCOMPARE(proxy->filterCaseSensitivity(), Qt::CaseInsensitive);
    }

    // Exercises: The Lambda connection (textChanged -> setFilterRegularExpression)
    void text_change_updates_filter()
    {
        QLineEdit search;
        QTableView table;
        QStandardItemModel model(3, 1);
        model.setData(model.index(0, 0), "Apple");
        model.setData(model.index(1, 0), "Apricot");
        model.setData(model.index(2, 0), "Banana");

        auto* proxy = bindSearch(this, &search, &table, &model);

        // 1. Initially, all 3 rows should be visible
        QCOMPARE(proxy->rowCount(), 3);

        // 2. Simulate user typing "Ap"
        // This triggers the signal and the lambda inside bindSearch
        search.setText("Ap");

        // 3. Verify the proxy filtered the results
        QCOMPARE(proxy->rowCount(), 2); // Apple and Apricot match

        // 4. Simulate user typing "Banana"
        search.setText("Banana");
        QCOMPARE(proxy->rowCount(), 1);

        // 5. Test Case Insensitivity (since the lambda uses CaseInsensitiveOption)
        search.setText("apple");
        QCOMPARE(proxy->rowCount(), 1);
    }

    // Exercises: Ownership and Lifetime
    void proxy_is_deleted_with_owner()
    {
        auto* owner = new QObject();
        QLineEdit search;
        QTableView table;
        QStandardItemModel model;

        QPointer<QSortFilterProxyModel> proxyTracker = bindSearch(owner, &search, &table, &model);

        QVERIFY(!proxyTracker.isNull());
        delete owner;
        // QPointer becomes null automatically when the object is deleted
        QVERIFY(proxyTracker.isNull());
    }
};

QTEST_MAIN(BindSearchTests)
#include "test_bind_search.moc"