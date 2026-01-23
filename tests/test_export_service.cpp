#include <QtTest/QtTest>
#include "export/ExportService.h"
#include "export/CsvExporter.h"
#include "export/JsonExporter.h"

class ExportServiceTests : public QObject
{
    Q_OBJECT

private slots:
    void creates_csv_exporter()
    {
        auto exporter = ExportService::createExporter(ExportFormat::Csv);
        QVERIFY(dynamic_cast<CsvExporter*>(exporter.get()) != nullptr);
    }

    void creates_json_exporter()
    {
        auto exporter = ExportService::createExporter(ExportFormat::Json);
        QVERIFY(dynamic_cast<JsonExporter*>(exporter.get()) != nullptr);
    }
};

QTEST_MAIN(ExportServiceTests)
#include "test_export_service.moc"
