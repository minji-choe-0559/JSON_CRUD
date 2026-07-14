#include "Read.h"

std::vector<Record> readAll(const std::string& path) {
    return readAllRecords(path);
}

std::optional<Record> findById(const std::string& path, int id) {
    for (const auto& record : readAll(path)) {
        if (record.id == id) {
            return record;
        }
    }
    return std::nullopt;
}
