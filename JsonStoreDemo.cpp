#include "JsonStoreDemo.h"

#include <iostream>

#include "JsonStore.h"

void runJsonStoreDemo(const std::string& path) {
    JsonValue data = JsonStore::read(path);

    std::map<std::string, JsonValue> fields;
    if (data.isObject()) {
        fields = data.asObject();
    }

    double count = fields.count("count") ? fields["count"].asNumber() : 0.0;
    std::cout << "read " << path << " -> count = " << count << "\n";

    count += 1;
    fields["count"] = JsonValue(count);
    JsonValue updated(fields);

    JsonStore::write(path, updated);
    std::cout << "wrote " << path << " -> count = " << count << "\n";
}
