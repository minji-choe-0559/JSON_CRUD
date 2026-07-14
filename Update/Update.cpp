#include "Update.h"

std::optional<Record> updateRecord(
    const std::string& path,
    int id,
    std::optional<std::string> newName,
    std::optional<std::string> newPhone) {
    std::vector<Record> records = readAllRecords(path);

    for (auto& record : records) {
        if (record.id != id) {
            continue;
        }

        if (newName.has_value()) {
            record.name = *newName;
        }
        if (newPhone.has_value()) {
            record.phone = *newPhone;
        }

        writeAllRecords(path, records);
        return record;
    }

    return std::nullopt;
}
