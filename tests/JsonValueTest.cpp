#include <gtest/gtest.h>

#include "../JsonValue.h"

TEST(JsonValue, DefaultIsNull) {
    JsonValue value;
    EXPECT_TRUE(value.isNull());
}

TEST(JsonValue, BoolTypeAndValue) {
    JsonValue value(true);
    EXPECT_TRUE(value.isBool());
    EXPECT_TRUE(value.asBool());
}

TEST(JsonValue, NumberTypeAndValue) {
    JsonValue value(3.14);
    EXPECT_TRUE(value.isNumber());
    EXPECT_DOUBLE_EQ(3.14, value.asNumber());
}

TEST(JsonValue, IntLiteralBecomesNumber) {
    JsonValue value(5);
    EXPECT_TRUE(value.isNumber());
    EXPECT_DOUBLE_EQ(5.0, value.asNumber());
}

TEST(JsonValue, StringLiteralBecomesString) {
    JsonValue value("Mia");
    EXPECT_TRUE(value.isString());
    EXPECT_EQ("Mia", value.asString());
}

TEST(JsonValue, StringTypeAndValue) {
    JsonValue value(std::string("hello"));
    EXPECT_TRUE(value.isString());
    EXPECT_EQ("hello", value.asString());
}

TEST(JsonValue, ArrayTypeAndValue) {
    std::vector<JsonValue> items{ JsonValue(1.0), JsonValue(2.0) };
    JsonValue value(items);
    EXPECT_TRUE(value.isArray());
    EXPECT_EQ(2u, value.asArray().size());
}

TEST(JsonValue, EmptyArray) {
    JsonValue value(std::vector<JsonValue>{});
    EXPECT_TRUE(value.isArray());
    EXPECT_TRUE(value.asArray().empty());
}

TEST(JsonValue, ArrayIndexAccess) {
    std::vector<JsonValue> items{ JsonValue(std::string("a")), JsonValue(std::string("b")) };
    JsonValue value(items);
    EXPECT_EQ("a", value[static_cast<size_t>(0)].asString());
    EXPECT_EQ("b", value[static_cast<size_t>(1)].asString());
}

TEST(JsonValue, ArrayIndexOutOfRangeThrows) {
    JsonValue value(std::vector<JsonValue>{ JsonValue(1.0) });
    EXPECT_THROW(value[static_cast<size_t>(5)], std::runtime_error);
}

TEST(JsonValue, ObjectTypeAndValue) {
    std::map<std::string, JsonValue> fields{ { "name", JsonValue(std::string("Mia")) } };
    JsonValue value(fields);
    EXPECT_TRUE(value.isObject());
    EXPECT_EQ(1u, value.asObject().size());
}

TEST(JsonValue, EmptyObject) {
    JsonValue value(std::map<std::string, JsonValue>{});
    EXPECT_TRUE(value.isObject());
    EXPECT_TRUE(value.asObject().empty());
}

TEST(JsonValue, ObjectKeyAccess) {
    std::map<std::string, JsonValue> fields{ { "name", JsonValue(std::string("Mia")) } };
    JsonValue value(fields);
    EXPECT_EQ("Mia", value["name"].asString());
}

TEST(JsonValue, ObjectMissingKeyThrows) {
    JsonValue value(std::map<std::string, JsonValue>{});
    EXPECT_THROW(value["missing"], std::runtime_error);
}

TEST(JsonValue, WrongTypeAccessThrows) {
    JsonValue value(std::string("text"));
    EXPECT_THROW(value.asNumber(), std::runtime_error);
    EXPECT_THROW(value.asBool(), std::runtime_error);
    EXPECT_THROW(value.asArray(), std::runtime_error);
    EXPECT_THROW(value.asObject(), std::runtime_error);
}

TEST(JsonValue, IndexOnNonArrayThrows) {
    JsonValue value(std::string("text"));
    EXPECT_THROW(value[static_cast<size_t>(0)], std::runtime_error);
}

TEST(JsonValue, KeyOnNonObjectThrows) {
    JsonValue value(std::string("text"));
    EXPECT_THROW(value["key"], std::runtime_error);
}
