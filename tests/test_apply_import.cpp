#include <QtTest/QtTest>
#include "import/ImportMode.h"
#include "import/ImportUtils.h"

class ApplyImportTests : public QObject
{
    Q_OBJECT

private slots:
    void replace_mode_replaces_data()
    {
        std::vector<int> existing{1, 2};
        std::vector<int> incoming{3};

        applyImport(existing, incoming, ImportMode::Replace);

        QCOMPARE(existing.size(), size_t(1));
        QCOMPARE(existing[0], 3);
    }

    void merge_mode_appends_data()
    {
        std::vector<int> existing{1};
        std::vector<int> incoming{2, 3};

        applyImport(existing, incoming, ImportMode::Merge);

        QCOMPARE(existing.size(), size_t(3));
    }
};

QTEST_MAIN(ApplyImportTests)
#include "test_apply_import.moc"
