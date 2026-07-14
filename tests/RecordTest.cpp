#include <gtest/gtest.h>

#include "../Record.h"

TEST(Record, ToJsonProducesExpectedFields) {
    Record record{ 1, "Mia", "010-1234-5678" };
    JsonValue value = toJson(record);

    ASSERT_TRUE(value.isObject());
    EXPECT_DOUBLE_EQ(1.0, value["id"].asNumber());
    EXPECT_EQ("Mia", value["name"].asString());
    EXPECT_EQ("010-1234-5678", value["phone"].asString());
}

TEST(Record, RoundTripsThroughJson) {
    Record original{ 42, "Choe", "010-9999-0000" };
    Record restored = fromJson(toJson(original));

    EXPECT_EQ(original.id, restored.id);
    EXPECT_EQ(original.name, restored.name);
    EXPECT_EQ(original.phone, restored.phone);
}

TEST(Record, FromJsonThrowsWhenNotObject) {
    EXPECT_THROW(fromJson(JsonValue("not an object")), std::runtime_error);
}

TEST(Record, FromJsonThrowsWhenFieldMissing) {
    std::map<std::string, JsonValue> fields{ { "id", JsonValue(1) }, { "name", JsonValue("Mia") } };
    EXPECT_THROW(fromJson(JsonValue(fields)), std::runtime_error);
}
