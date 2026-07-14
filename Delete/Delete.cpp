#include "Delete.h"

#include "../JsonStore.h"

std::optional<Record> deleteRecord(const std::string& path, int id) {
    JsonValue data = JsonStore::read(path);
    std::vector<JsonValue> records = data.asArray();

    for (auto it = records.begin(); it != records.end(); ++it) {
        Record existing = fromJson(*it);
        if (existing.id != id) {
            continue;
        }

        records.erase(it);
        JsonStore::write(path, JsonValue(records));
        return existing;
    }

    return std::nullopt;
}
