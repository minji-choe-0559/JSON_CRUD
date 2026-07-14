#pragma once

#include <optional>
#include <string>

#include "../Record.h"

std::optional<Record> deleteRecord(const std::string& path, int id);
