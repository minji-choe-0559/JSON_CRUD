#include "Update.h"

#include "../JsonStore.h"

std::optional<Record> updateRecord(
    const std::string& path,
    int id,
    std::optional<std::string> newName,
    std::optional<std::string> newPhone) {
    JsonValue data = JsonStore::read(path);
    std::vector<JsonValue> records = data.asArray();

    for (auto& item : records) {
        Record existing = fromJson(item);
        if (existing.id != id) {
            continue;
        }

        if (newName.has_value()) {
            existing.name = *newName;
        }
        if (newPhone.has_value()) {
            existing.phone = *newPhone;
        }

        item = toJson(existing);
        JsonStore::write(path, JsonValue(records));
        return existing;
    }

    return std::nullopt;
}
