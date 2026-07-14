#include "Record.h"

#include "JsonStore.h"

JsonValue toJson(const Record& record) {
    std::map<std::string, JsonValue> fields;
    fields["id"] = JsonValue(record.id);
    fields["name"] = JsonValue(record.name);
    fields["phone"] = JsonValue(record.phone);
    return JsonValue(fields);
}

Record fromJson(const JsonValue& value) {
    Record record;
    record.id = static_cast<int>(value["id"].asNumber());
    record.name = value["name"].asString();
    record.phone = value["phone"].asString();
    return record;
}

std::vector<Record> readAllRecords(const std::string& path) {
    JsonValue data = JsonStore::read(path);
    std::vector<Record> records;
    for (const auto& item : data.asArray()) {
        records.push_back(fromJson(item));
    }
    return records;
}

void writeAllRecords(const std::string& path, const std::vector<Record>& records) {
    std::vector<JsonValue> items;
    items.reserve(records.size());
    for (const auto& record : records) {
        items.push_back(toJson(record));
    }
    JsonStore::write(path, JsonValue(items));
}
