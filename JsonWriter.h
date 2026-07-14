#pragma once

#include <string>

#include "JsonValue.h"

class JsonWriter {
public:
    static std::string write(const JsonValue& value);
};
