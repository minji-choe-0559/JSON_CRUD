#include <gtest/gtest.h>

#include <filesystem>

#include "../../Update/Update.h"
#include "../../Create/Create.h"
#include "../../Read/Read.h"

namespace {

class UpdateTest : public ::testing::Test {
protected:
    void SetUp() override {
        path = (std::filesystem::temp_directory_path() / "aiproject5_update_test.json").string();
        std::filesystem::remove(path);
    }

    void TearDown() override {
        std::filesystem::remove(path);
    }

    std::string path;
};

}  // namespace

TEST_F(UpdateTest, UpdatesNameOnly) {
    Record record = createRecord(path, "Mia", "010-1111-2222");

    std::optional<Record> updated = updateRecord(path, record.id, "Mia2", std::nullopt);
    ASSERT_TRUE(updated.has_value());
    EXPECT_EQ("Mia2", updated->name);
    EXPECT_EQ("010-1111-2222", updated->phone);
}

TEST_F(UpdateTest, UpdatesPhoneOnly) {
    Record record = createRecord(path, "Mia", "010-1111-2222");

    std::optional<Record> updated = updateRecord(path, record.id, std::nullopt, "010-9999-0000");
    ASSERT_TRUE(updated.has_value());
    EXPECT_EQ("Mia", updated->name);
    EXPECT_EQ("010-9999-0000", updated->phone);
}

TEST_F(UpdateTest, UpdatesBothFields) {
    Record record = createRecord(path, "Mia", "010-1111-2222");

    std::optional<Record> updated = updateRecord(path, record.id, "Mia2", "010-9999-0000");
    ASSERT_TRUE(updated.has_value());
    EXPECT_EQ("Mia2", updated->name);
    EXPECT_EQ("010-9999-0000", updated->phone);
}

TEST_F(UpdateTest, PersistsChangeToFile) {
    Record record = createRecord(path, "Mia", "010-1111-2222");
    updateRecord(path, record.id, "Mia2", std::nullopt);

    std::optional<Record> reloaded = findById(path, record.id);
    ASSERT_TRUE(reloaded.has_value());
    EXPECT_EQ("Mia2", reloaded->name);
}

TEST_F(UpdateTest, OtherRecordsAreUnaffected) {
    Record first = createRecord(path, "Mia", "010-1111-2222");
    Record second = createRecord(path, "Choe", "010-3333-4444");

    updateRecord(path, first.id, "Mia2", std::nullopt);

    std::optional<Record> untouched = findById(path, second.id);
    ASSERT_TRUE(untouched.has_value());
    EXPECT_EQ("Choe", untouched->name);
    EXPECT_EQ("010-3333-4444", untouched->phone);
}

TEST_F(UpdateTest, ReturnsNulloptWhenIdMissing) {
    createRecord(path, "Mia", "010-1111-2222");

    std::optional<Record> result = updateRecord(path, 999, "X", std::nullopt);
    EXPECT_FALSE(result.has_value());
}

TEST_F(UpdateTest, NoFieldsProvidedKeepsRecordUnchanged) {
    Record record = createRecord(path, "Mia", "010-1111-2222");

    std::optional<Record> result = updateRecord(path, record.id, std::nullopt, std::nullopt);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ("Mia", result->name);
    EXPECT_EQ("010-1111-2222", result->phone);

    std::optional<Record> reloaded = findById(path, record.id);
    ASSERT_TRUE(reloaded.has_value());
    EXPECT_EQ("Mia", reloaded->name);
    EXPECT_EQ("010-1111-2222", reloaded->phone);
}
