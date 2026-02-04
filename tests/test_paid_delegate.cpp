#include <QtTest/QtTest>
#include <QPainter>
#include <QImage>
#include <QStandardItemModel>
#include <QApplication>
#include "ui/PaidDelegate.h"

class PaidDelegateTests : public QObject
{
    Q_OBJECT

private slots:
    // This runs once before all tests to set up the GUI environment
    void initTestCase()
    {
        if (!qApp) {
            // Force Qt to run without a real GPU/Display requirement
            qputenv("QT_QPA_PLATFORM", "offscreen");

            static int argc = 1;
            static char* argv[] = { (char*)"test" };
            new QApplication(argc, argv);
        }
    }

    // Exercises: The "if (!index.isValid())" guard clause
    void paint_invalid_index_returns_early()
    {
        PaidDelegate delegate;
        QImage image(100, 30, QImage::Format_ARGB32);
        QPainter painter(&image);
        QStyleOptionViewItem option;

        delegate.paint(&painter, option, QModelIndex());
        QVERIFY(true); // Reaching here means no crash
    }

    // Exercises: Full rendering path (Checkbox + "Yes"/"No" text)
    void paint_valid_index_draws_content()
    {
        PaidDelegate delegate;

        QStandardItemModel model(1, 1);
        QModelIndex index = model.index(0, 0);
        model.setData(index, Qt::Checked, Qt::CheckStateRole);
        model.setData(index, "Yes", Qt::DisplayRole);

        QImage image(200, 50, QImage::Format_ARGB32);
        image.fill(Qt::white);
        QPainter painter(&image);

        QStyleOptionViewItem option;
        option.rect = QRect(0, 0, 200, 50);
        option.state = QStyle::State_Enabled | QStyle::State_Active;

        delegate.paint(&painter, option, index);
        painter.end();

        // Check if anything was painted
        bool imageChanged = false;
        for (int y = 0; y < image.height() && !imageChanged; ++y) {
            for (int x = 0; x < image.width(); ++x) {
                if (image.pixelColor(x, y) != Qt::white) {
                    imageChanged = true;
                    break;
                }
            }
        }
        QVERIFY2(imageChanged, "The delegate did not paint any pixels on the image.");
    }

    void sizeHint_returns_valid_size()
    {
        PaidDelegate delegate;
        QStyleOptionViewItem option;
        QStandardItemModel model(1, 1);
        QModelIndex index = model.index(0, 0);

        QSize size = delegate.sizeHint(option, index);
        QVERIFY(size.isValid());
        QVERIFY(size.width() > 0);
        QVERIFY(size.height() > 0);
    }
};

// Note: Use QTEST_MAIN which handles most setup, but initTestCase ensures 
// QApplication is alive for the specific style calls in delegate.
QTEST_MAIN(PaidDelegateTests)
#include "test_paid_delegate.moc"