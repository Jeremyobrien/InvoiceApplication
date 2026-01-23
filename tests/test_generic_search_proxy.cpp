#include <QtTest/QtTest>
#include "../src/ui/GenericSearchProxy.h"

class GenericSearchProxyTests : public QObject
{
    Q_OBJECT

private slots:
    void default_configuration()
    {
        GenericSearchProxy proxy;
        QCOMPARE(proxy.filterKeyColumn(), -1);
        QCOMPARE(proxy.filterCaseSensitivity(), Qt::CaseInsensitive);
    }
};

QTEST_MAIN(GenericSearchProxyTests)
#include "test_generic_search_proxy.moc"
