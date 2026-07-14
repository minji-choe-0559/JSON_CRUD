#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "../JsonStore.h"

namespace {

class JsonStoreTest : public ::testing::Test {
protected:
    void SetUp() override {
        path = (std::filesystem::temp_directory_path() / "aiproject5_json_store_test.json").string();
        std::filesystem::remove(path);
    }

    void TearDown() override {
        std::filesystem::remove(path);
    }

    std::string path;
};

}  // namespace

TEST_F(JsonStoreTest, WritesAndReadsBack) {
    std::map<std::string, JsonValue> fields{ { "name", JsonValue(std::string("Mia")) } };
    JsonStore::write(path, JsonValue(fields));

    JsonValue result = JsonStore::read(path);
    EXPECT_EQ("Mia", result["name"].asString());
}

TEST_F(JsonStoreTest, OverwritesExistingFile) {
    JsonStore::write(path, JsonValue(std::string("first")));
    JsonStore::write(path, JsonValue(std::string("second")));

    JsonValue result = JsonStore::read(path);
    EXPECT_EQ("second", result.asString());
}

TEST_F(JsonStoreTest, ReadingMissingFileReturnsEmptyArray) {
    JsonValue result = JsonStore::read(path);
    EXPECT_TRUE(result.isArray());
    EXPECT_TRUE(result.asArray().empty());
}

TEST_F(JsonStoreTest, ReadingEmptyFileReturnsEmptyArray) {
    std::ofstream(path).close();

    JsonValue result = JsonStore::read(path);
    EXPECT_TRUE(result.isArray());
    EXPECT_TRUE(result.asArray().empty());
}

TEST_F(JsonStoreTest, ReadingInvalidJsonThrows) {
    std::ofstream out(path);
    out << "{invalid";
    out.close();

    EXPECT_THROW(JsonStore::read(path), std::runtime_error);
}
