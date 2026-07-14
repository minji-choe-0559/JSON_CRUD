#include <gtest/gtest.h>

#include "../JsonParser.h"

TEST(JsonParser, ParsesNull) {
    JsonValue value = JsonParser::parse("null");
    EXPECT_TRUE(value.isNull());
}

TEST(JsonParser, ParsesTrueAndFalse) {
    EXPECT_TRUE(JsonParser::parse("true").asBool());
    EXPECT_FALSE(JsonParser::parse("false").asBool());
}

TEST(JsonParser, ParsesIntegerNumber) {
    EXPECT_DOUBLE_EQ(42.0, JsonParser::parse("42").asNumber());
}

TEST(JsonParser, ParsesNegativeNumber) {
    EXPECT_DOUBLE_EQ(-7.0, JsonParser::parse("-7").asNumber());
}

TEST(JsonParser, ParsesRealNumber) {
    EXPECT_DOUBLE_EQ(3.14, JsonParser::parse("3.14").asNumber());
}

TEST(JsonParser, ParsesString) {
    EXPECT_EQ("hello", JsonParser::parse("\"hello\"").asString());
}

TEST(JsonParser, ParsesStringWithEscapes) {
    EXPECT_EQ("a\"b\\c\nd", JsonParser::parse("\"a\\\"b\\\\c\\nd\"").asString());
}

TEST(JsonParser, ParsesEmptyArray) {
    JsonValue value = JsonParser::parse("[]");
    EXPECT_TRUE(value.isArray());
    EXPECT_TRUE(value.asArray().empty());
}

TEST(JsonParser, ParsesArray) {
    JsonValue value = JsonParser::parse("[1, 2, 3]");
    ASSERT_TRUE(value.isArray());
    ASSERT_EQ(3u, value.asArray().size());
    EXPECT_DOUBLE_EQ(1.0, value[static_cast<size_t>(0)].asNumber());
    EXPECT_DOUBLE_EQ(3.0, value[static_cast<size_t>(2)].asNumber());
}

TEST(JsonParser, ParsesEmptyObject) {
    JsonValue value = JsonParser::parse("{}");
    EXPECT_TRUE(value.isObject());
    EXPECT_TRUE(value.asObject().empty());
}

TEST(JsonParser, ParsesObject) {
    JsonValue value = JsonParser::parse("{\"name\": \"Mia\", \"age\": 30}");
    ASSERT_TRUE(value.isObject());
    EXPECT_EQ("Mia", value["name"].asString());
    EXPECT_DOUBLE_EQ(30.0, value["age"].asNumber());
}

TEST(JsonParser, ParsesNestedStructure) {
    JsonValue value = JsonParser::parse("{\"items\": [1, {\"x\": true}]}");
    ASSERT_TRUE(value.isObject());
    JsonValue items = value["items"];
    ASSERT_TRUE(items.isArray());
    EXPECT_DOUBLE_EQ(1.0, items[static_cast<size_t>(0)].asNumber());
    EXPECT_TRUE(items[static_cast<size_t>(1)]["x"].asBool());
}

TEST(JsonParser, IgnoresWhitespaceAndNewlines) {
    JsonValue value = JsonParser::parse("  {\n \"a\" : 1 \n} \n");
    EXPECT_DOUBLE_EQ(1.0, value["a"].asNumber());
}

TEST(JsonParser, ThrowsOnEmptyString) {
    EXPECT_THROW(JsonParser::parse(""), std::runtime_error);
}

TEST(JsonParser, ThrowsOnMismatchedBrackets) {
    EXPECT_THROW(JsonParser::parse("[1, 2"), std::runtime_error);
    EXPECT_THROW(JsonParser::parse("{\"a\": 1"), std::runtime_error);
}

TEST(JsonParser, ThrowsOnMissingComma) {
    EXPECT_THROW(JsonParser::parse("[1 2]"), std::runtime_error);
}

TEST(JsonParser, ThrowsOnMissingQuote) {
    EXPECT_THROW(JsonParser::parse("{a\": 1}"), std::runtime_error);
}

TEST(JsonParser, ThrowsOnTrailingCharacters) {
    EXPECT_THROW(JsonParser::parse("1 2"), std::runtime_error);
}
