#pragma once

#include <optional>
#include <QString>
#include "ImportResult.h"

class CsvImporter
{
    public:
        static std::optional<ImportResult> parse(const QString &csvText);
};