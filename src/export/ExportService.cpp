#include "ExportService.h"
#include "CsvExporter.h"
#include "JsonExporter.h"

std::unique_ptr<Exporter> ExportService::createExporter(ExportFormat format)
{
    switch (format)
    {
    case ExportFormat::Csv:
        return std::make_unique<CsvExporter>();
    case ExportFormat::Json:
        return std::make_unique<JsonExporter>();
    }
    return nullptr;
}
