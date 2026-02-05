#include <QtTest/QtTest>
#include <QApplication>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QPainter>
#include "../src/ui/PaidDelegate.h"

class PaidDelegateTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase() {
        if (!qApp) {
            qputenv("QT_QPA_PLATFORM", "offscreen");
            static int argc = 1;
            static char* argv[] = { (char*)"test" };
            new QApplication(argc, argv);
        }
    }

    void paintCoverage() {
        PaidDelegate delegate;
        QStandardItemModel model(1, 3);
        QModelIndex index = model.index(0, 2);
        model.setData(index, Qt::Checked, Qt::CheckStateRole);
        model.setData(index, "Yes", Qt::DisplayRole);

        QImage img(200, 50, QImage::Format_ARGB32);
        QPainter painter(&img);
        QStyleOptionViewItem option;
        option.rect = QRect(0, 0, 200, 50);

        // Test invalid index (branch coverage)
        delegate.paint(&painter, option, QModelIndex());

        // Test valid index (full paint coverage)
        delegate.paint(&painter, option, index);
        QVERIFY(!img.allGray()); // Simple check that something happened
    }

    void editorEventClickHandling() {
        PaidDelegate delegate;
        QStandardItemModel model(1, 3);
        QModelIndex index = model.index(0, 2);
        model.setData(index, Qt::Unchecked, Qt::CheckStateRole);
        model.setData(index, "No", Qt::DisplayRole);

        QStyleOptionViewItem option;
        option.rect = QRect(0, 0, 200, 50);
        option.font = QApplication::font();

        // 1. Test clicking OUTSIDE the checkbox rect
        QMouseEvent missEvent(QEvent::MouseButtonRelease, QPoint(5, 5), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        bool handledMiss = delegate.editorEvent(&missEvent, &model, option, index);
        QVERIFY(!handledMiss);
        QCOMPARE(model.data(index, Qt::CheckStateRole).toInt(), (int)Qt::Unchecked);

        // 2. Test clicking INSIDE the checkbox rect
        // We calculate the center point to ensure a hit
        QRect box = delegate.checkboxRect(option, index);
        QMouseEvent hitEvent(QEvent::MouseButtonRelease, box.center(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);

        bool handledHit = delegate.editorEvent(&hitEvent, &model, option, index);
        QVERIFY(handledHit);
        QCOMPARE(model.data(index, Qt::CheckStateRole).toInt(), (int)Qt::Checked);

        // 3. Non-trigger events (branch coverage)
        QMouseEvent moveEvent(QEvent::MouseMove, box.center(), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
        QVERIFY(!delegate.editorEvent(&moveEvent, &model, option, index));

        // 4. Non-column 2 (branch coverage)
        QVERIFY(!delegate.editorEvent(&hitEvent, &model, option, model.index(0, 0)));
    }

    void sizeHintCoverage() {
        PaidDelegate delegate;
        QStyleOptionViewItem option;
        option.decorationSize = QSize(20, 20);
        QStandardItemModel model(1, 3);
        QModelIndex index = model.index(0,2);
        model.setData(index, "Test Data", Qt::DisplayRole);
        QSize size = delegate.sizeHint(option, index);
        QVERIFY(size.width() > 0);
    }
};

QTEST_MAIN(PaidDelegateTests)
#include "test_paid_delegate.moc"