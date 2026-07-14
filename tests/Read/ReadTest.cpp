#include <gtest/gtest.h>

#include <filesystem>

#include "../../Read/Read.h"
#include "../../Create/Create.h"

namespace {

class ReadTest : public ::testing::Test {
protected:
    void SetUp() override {
        path = (std::filesystem::temp_directory_path() / "aiproject5_read_test.json").string();
        std::filesystem::remove(path);
    }

    void TearDown() override {
        std::filesystem::remove(path);
    }

    std::string path;
};

}  // namespace

TEST_F(ReadTest, ReadAllReturnsEmptyForMissingFile) {
    std::vector<Record> records = readAll(path);
    EXPECT_TRUE(records.empty());
}

TEST_F(ReadTest, ReadAllReturnsAllRecords) {
    createRecord(path, "Mia", "010-1111-2222");
    createRecord(path, "Choe", "010-3333-4444");

    std::vector<Record> records = readAll(path);
    ASSERT_EQ(2u, records.size());
    EXPECT_EQ("Mia", records[0].name);
    EXPECT_EQ("Choe", records[1].name);
}

TEST_F(ReadTest, FindByIdReturnsMatchingRecord) {
    createRecord(path, "Mia", "010-1111-2222");
    Record second = createRecord(path, "Choe", "010-3333-4444");

    std::optional<Record> found = findById(path, second.id);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ("Choe", found->name);
}

TEST_F(ReadTest, FindByIdReturnsNulloptWhenMissing) {
    createRecord(path, "Mia", "010-1111-2222");

    std::optional<Record> found = findById(path, 999);
    EXPECT_FALSE(found.has_value());
}
