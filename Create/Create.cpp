#include "Create.h"

#include "../JsonStore.h"

Record createRecord(const std::string& path, const std::string& name, const std::string& phone) {
    JsonValue data = JsonStore::read(path);
    std::vector<JsonValue> records = data.asArray();

    int nextId = 1;
    for (const auto& item : records) {
        Record existing = fromJson(item);
        if (existing.id >= nextId) {
            nextId = existing.id + 1;
        }
    }

    Record record{ nextId, name, phone };
    records.push_back(toJson(record));
    JsonStore::write(path, JsonValue(records));
    return record;
}
