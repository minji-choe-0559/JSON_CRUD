#include "Create.h"

Record createRecord(const std::string& path, const std::string& name, const std::string& phone) {
    std::vector<Record> records = readAllRecords(path);

    int nextId = 1;
    for (const auto& existing : records) {
        if (existing.id >= nextId) {
            nextId = existing.id + 1;
        }
    }

    Record record{ nextId, name, phone };
    records.push_back(record);
    writeAllRecords(path, records);
    return record;
}
