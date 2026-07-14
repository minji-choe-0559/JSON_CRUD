#pragma once

#include <optional>
#include <string>
#include <vector>

#include "../Record.h"

std::vector<Record> readAll(const std::string& path);
std::optional<Record> findById(const std::string& path, int id);
