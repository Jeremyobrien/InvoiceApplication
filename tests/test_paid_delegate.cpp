#include <QtTest/QtTest>
#include <QPainter>
#include <QImage>
#include "ui/PaidDelegate.h"

class PaidDelegateTests : public QObject
{
    Q_OBJECT

private slots:
    void paint_does_not_crash()
    {
        PaidDelegate delegate;
        QImage image(10, 10, QImage::Format_ARGB32);
        QPainter painter(&image);

        QStyleOptionViewItem option;
        QModelIndex index;

        delegate.paint(&painter, option, index);
        QVERIFY(true);
    }
};

QTEST_MAIN(PaidDelegateTests)
#include "test_paid_delegate.moc"
