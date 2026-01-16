#pragma once

#include <optional>
#include <QByteArray>
#include "ImportResult.h"

class JsonImporter
{
    public:
        static std::optional<ImportResult> parse(const QByteArray &jsonData);
};