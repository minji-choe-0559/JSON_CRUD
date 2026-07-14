#include <gtest/gtest.h>

#include <filesystem>

#include "../../Create/Create.h"
#include "../../JsonStore.h"

namespace {

class CreateTest : public ::testing::Test {
protected:
    void SetUp() override {
        path = (std::filesystem::temp_directory_path() / "aiproject5_create_test.json").string();
        std::filesystem::remove(path);
    }

    void TearDown() override {
        std::filesystem::remove(path);
    }

    std::string path;
};

}  // namespace

TEST_F(CreateTest, FirstRecordGetsIdOne) {
    Record record = createRecord(path, "Mia", "010-1111-2222");
    EXPECT_EQ(1, record.id);
    EXPECT_EQ("Mia", record.name);
    EXPECT_EQ("010-1111-2222", record.phone);
}

TEST_F(CreateTest, SecondRecordGetsNextId) {
    createRecord(path, "Mia", "010-1111-2222");
    Record second = createRecord(path, "Choe", "010-3333-4444");
    EXPECT_EQ(2, second.id);
}

TEST_F(CreateTest, WrittenRecordsCanBeReadBack) {
    createRecord(path, "Mia", "010-1111-2222");
    createRecord(path, "Choe", "010-3333-4444");

    JsonValue data = JsonStore::read(path);
    ASSERT_TRUE(data.isArray());
    ASSERT_EQ(2u, data.asArray().size());
    EXPECT_EQ("Mia", data[static_cast<size_t>(0)]["name"].asString());
    EXPECT_EQ("Choe", data[static_cast<size_t>(1)]["name"].asString());
}

TEST_F(CreateTest, NextIdIsMaxExistingIdPlusOne) {
    createRecord(path, "Mia", "010-1111-2222");
    createRecord(path, "Choe", "010-3333-4444");

    JsonValue data = JsonStore::read(path);
    std::vector<JsonValue> records = data.asArray();
    records.erase(records.begin());  // id 1 삭제, id 2만 남음
    JsonStore::write(path, JsonValue(records));

    Record third = createRecord(path, "Kim", "010-5555-6666");
    EXPECT_EQ(3, third.id);
}
