#include <gtest/gtest.h>

#include <filesystem>

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

namespace {

class RecordRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        path = (std::filesystem::temp_directory_path() / "aiproject5_record_repo_test.json").string();
        std::filesystem::remove(path);
    }

    void TearDown() override {
        std::filesystem::remove(path);
    }

    std::string path;
};

}  // namespace

TEST_F(RecordRepositoryTest, ReadAllRecordsReturnsEmptyForMissingFile) {
    std::vector<Record> records = readAllRecords(path);
    EXPECT_TRUE(records.empty());
}

TEST_F(RecordRepositoryTest, WriteThenReadRoundTrips) {
    std::vector<Record> records{
        Record{ 1, "Mia", "010-1111-2222" },
        Record{ 2, "Choe", "010-3333-4444" },
    };

    writeAllRecords(path, records);
    std::vector<Record> reloaded = readAllRecords(path);

    ASSERT_EQ(2u, reloaded.size());
    EXPECT_EQ("Mia", reloaded[0].name);
    EXPECT_EQ("Choe", reloaded[1].name);
}
