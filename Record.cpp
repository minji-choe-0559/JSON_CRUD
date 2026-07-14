#include "Record.h"

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
