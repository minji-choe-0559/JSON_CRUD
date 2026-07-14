#pragma once

#include <string>
#include <vector>

#include "JsonValue.h"

struct Record {
    int id;
    std::string name;
    std::string phone;
};

JsonValue toJson(const Record& record);
Record fromJson(const JsonValue& value);

// Create/Read/Update/Delete가 공통으로 쓰는 저장소 접근점.
// JsonStore/JsonValue를 직접 다루지 않고 Record 단위로 읽고 쓴다.
std::vector<Record> readAllRecords(const std::string& path);
void writeAllRecords(const std::string& path, const std::vector<Record>& records);
