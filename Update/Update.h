#pragma once

#include <optional>
#include <string>

#include "../Record.h"

std::optional<Record> updateRecord(
    const std::string& path,
    int id,
    std::optional<std::string> newName,
    std::optional<std::string> newPhone);
