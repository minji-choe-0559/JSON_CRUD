#include "JsonStore.h"

#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "JsonParser.h"
#include "JsonWriter.h"

namespace {

bool isBlank(const std::string& text) {
    for (char c : text) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

}  // namespace

JsonValue JsonStore::read(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        return JsonValue(std::vector<JsonValue>{});
    }

    std::ostringstream buffer;
    buffer << in.rdbuf();
    std::string content = buffer.str();

    if (isBlank(content)) {
        return JsonValue(std::vector<JsonValue>{});
    }

    return JsonParser::parse(content);
}

void JsonStore::write(const std::string& path, const JsonValue& value) {
    std::ofstream out(path, std::ios::trunc);
    if (!out.is_open()) {
        throw std::runtime_error("JsonStore: cannot open file for writing: " + path);
    }
    out << JsonWriter::write(value);
}
