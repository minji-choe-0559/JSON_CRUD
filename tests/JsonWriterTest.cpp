#include <gtest/gtest.h>

#include "../JsonParser.h"
#include "../JsonWriter.h"

TEST(JsonWriter, WritesNull) {
    EXPECT_EQ("null", JsonWriter::write(JsonValue()));
}

TEST(JsonWriter, WritesBool) {
    EXPECT_EQ("true", JsonWriter::write(JsonValue(true)));
    EXPECT_EQ("false", JsonWriter::write(JsonValue(false)));
}

TEST(JsonWriter, WritesIntegerWithoutDecimal) {
    EXPECT_EQ("42", JsonWriter::write(JsonValue(42.0)));
}

TEST(JsonWriter, WritesNegativeNumber) {
    EXPECT_EQ("-7", JsonWriter::write(JsonValue(-7.0)));
}

TEST(JsonWriter, WritesRealNumber) {
    EXPECT_EQ("3.14", JsonWriter::write(JsonValue(3.14)));
}

TEST(JsonWriter, WritesString) {
    EXPECT_EQ("\"hello\"", JsonWriter::write(JsonValue(std::string("hello"))));
}

TEST(JsonWriter, WritesStringWithEscapes) {
    EXPECT_EQ("\"a\\\"b\\\\c\"", JsonWriter::write(JsonValue(std::string("a\"b\\c"))));
}

TEST(JsonWriter, WritesEmptyArray) {
    EXPECT_EQ("[]", JsonWriter::write(JsonValue(std::vector<JsonValue>{})));
}

TEST(JsonWriter, WritesArray) {
    std::vector<JsonValue> items{ JsonValue(1.0), JsonValue(2.0) };
    EXPECT_EQ("[1,2]", JsonWriter::write(JsonValue(items)));
}

TEST(JsonWriter, WritesEmptyObject) {
    EXPECT_EQ("{}", JsonWriter::write(JsonValue(std::map<std::string, JsonValue>{})));
}

TEST(JsonWriter, WritesObject) {
    std::map<std::string, JsonValue> fields{ { "name", JsonValue(std::string("Mia")) } };
    EXPECT_EQ("{\"name\":\"Mia\"}", JsonWriter::write(JsonValue(fields)));
}

TEST(JsonWriter, WritesNestedStructure) {
    std::map<std::string, JsonValue> inner{ { "x", JsonValue(true) } };
    std::vector<JsonValue> items{ JsonValue(1.0), JsonValue(inner) };
    std::map<std::string, JsonValue> fields{ { "items", JsonValue(items) } };
    EXPECT_EQ("{\"items\":[1,{\"x\":true}]}", JsonWriter::write(JsonValue(fields)));
}

TEST(JsonWriter, RoundTripsThroughParser) {
    std::map<std::string, JsonValue> fields{
        { "name", JsonValue(std::string("Mia")) },
        { "age", JsonValue(30.0) },
        { "active", JsonValue(true) },
    };
    JsonValue original(fields);
    std::string serialized = JsonWriter::write(original);
    JsonValue reparsed = JsonParser::parse(serialized);

    EXPECT_EQ("Mia", reparsed["name"].asString());
    EXPECT_DOUBLE_EQ(30.0, reparsed["age"].asNumber());
    EXPECT_TRUE(reparsed["active"].asBool());
}
