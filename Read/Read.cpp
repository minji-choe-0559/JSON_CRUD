#include "Read.h"

#include "../JsonStore.h"

std::vector<Record> readAll(const std::string& path) {
    JsonValue data = JsonStore::read(path);
    std::vector<Record> records;
    for (const auto& item : data.asArray()) {
        records.push_back(fromJson(item));
    }
    return records;
}

std::optional<Record> findById(const std::string& path, int id) {
    for (const auto& record : readAll(path)) {
        if (record.id == id) {
            return record;
        }
    }
    return std::nullopt;
}
