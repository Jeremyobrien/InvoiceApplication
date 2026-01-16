#pragma once

#include <vector>
#include <ImportMode.h>

template <typename T>
void applyImport(
    std::vector<T> &existing,
    const std::vector<T> &incoming,
    ImportMode mode)
{
    if (mode == ImportMode::Replace)
        existing = incoming;
    else
        existing.insert(existing.end(), incoming.begin(), incoming.end());
}