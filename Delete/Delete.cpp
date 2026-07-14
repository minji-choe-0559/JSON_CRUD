#include "Delete.h"

std::optional<Record> deleteRecord(const std::string& path, int id) {
    std::vector<Record> records = readAllRecords(path);

    for (auto it = records.begin(); it != records.end(); ++it) {
        if (it->id != id) {
            continue;
        }

        Record deleted = *it;
        records.erase(it);
        writeAllRecords(path, records);
        return deleted;
    }

    return std::nullopt;
}
