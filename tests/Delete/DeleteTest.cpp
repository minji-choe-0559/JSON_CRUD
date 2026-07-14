#include <gtest/gtest.h>

#include <filesystem>

#include "../../Delete/Delete.h"
#include "../../Create/Create.h"
#include "../../Read/Read.h"

namespace {

class DeleteTest : public ::testing::Test {
protected:
    void SetUp() override {
        path = (std::filesystem::temp_directory_path() / "aiproject5_delete_test.json").string();
        std::filesystem::remove(path);
    }

    void TearDown() override {
        std::filesystem::remove(path);
    }

    std::string path;
};

}  // namespace

TEST_F(DeleteTest, ReturnsDeletedRecord) {
    Record record = createRecord(path, "Mia", "010-1111-2222");

    std::optional<Record> deleted = deleteRecord(path, record.id);
    ASSERT_TRUE(deleted.has_value());
    EXPECT_EQ("Mia", deleted->name);
}

TEST_F(DeleteTest, RemovesRecordFromFile) {
    Record record = createRecord(path, "Mia", "010-1111-2222");
    deleteRecord(path, record.id);

    std::optional<Record> found = findById(path, record.id);
    EXPECT_FALSE(found.has_value());
}

TEST_F(DeleteTest, OtherRecordsAreUnaffected) {
    Record first = createRecord(path, "Mia", "010-1111-2222");
    Record second = createRecord(path, "Choe", "010-3333-4444");

    deleteRecord(path, first.id);

    std::optional<Record> untouched = findById(path, second.id);
    ASSERT_TRUE(untouched.has_value());
    EXPECT_EQ("Choe", untouched->name);
}

TEST_F(DeleteTest, DeletingOnlyRecordLeavesEmptyList) {
    Record record = createRecord(path, "Mia", "010-1111-2222");
    deleteRecord(path, record.id);

    std::vector<Record> all = readAll(path);
    EXPECT_TRUE(all.empty());
}

TEST_F(DeleteTest, ReturnsNulloptWhenIdMissing) {
    createRecord(path, "Mia", "010-1111-2222");

    std::optional<Record> result = deleteRecord(path, 999);
    EXPECT_FALSE(result.has_value());
}
