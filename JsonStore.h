#pragma once

#include <string>

#include "JsonValue.h"

class JsonStore {
public:
    static JsonValue read(const std::string& path);
    static void write(const std::string& path, const JsonValue& value);
};
