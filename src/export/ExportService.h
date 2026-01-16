#pragma once
#include <memory>
#include "Exporter.h"

enum class ExportFormat
{
    Csv,
    Json
};

class ExportService
{
public:
    static std::unique_ptr<Exporter> createExporter(ExportFormat format);
};
