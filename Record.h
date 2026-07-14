#pragma once

#include <string>

#include "JsonValue.h"

struct Record {
    int id;
    std::string name;
    std::string phone;
};

JsonValue toJson(const Record& record);
Record fromJson(const JsonValue& value);
