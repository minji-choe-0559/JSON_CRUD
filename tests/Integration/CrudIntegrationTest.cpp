#include <gtest/gtest.h>

#include <filesystem>

#include "../../Create/Create.h"
#include "../../Read/Read.h"
#include "../../Update/Update.h"
#include "../../Delete/Delete.h"

namespace {

class CrudIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        path = (std::filesystem::temp_directory_path() / "aiproject5_crud_integration_test.json").string();
        std::filesystem::remove(path);
    }

    void TearDown() override {
        std::filesystem::remove(path);
    }

    std::string path;
};

}  // namespace

TEST_F(CrudIntegrationTest, FullLifecycleAcrossAllFeatures) {
    // Create: 세 명 등록
    Record mia = createRecord(path, "Mia", "010-1111-1111");
    Record choe = createRecord(path, "Choe", "010-2222-2222");
    Record kim = createRecord(path, "Kim", "010-3333-3333");
    EXPECT_EQ(1, mia.id);
    EXPECT_EQ(2, choe.id);
    EXPECT_EQ(3, kim.id);

    // Read: 전체 목록 + id 검색
    std::vector<Record> all = readAll(path);
    ASSERT_EQ(3u, all.size());

    std::optional<Record> found = findById(path, choe.id);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ("Choe", found->name);

    // Update: Choe의 이름만 수정, phone은 유지
    std::optional<Record> updated = updateRecord(path, choe.id, "Choe2", std::nullopt);
    ASSERT_TRUE(updated.has_value());
    EXPECT_EQ("Choe2", updated->name);
    EXPECT_EQ("010-2222-2222", updated->phone);

    // Delete: Mia 삭제
    std::optional<Record> deleted = deleteRecord(path, mia.id);
    ASSERT_TRUE(deleted.has_value());
    EXPECT_EQ("Mia", deleted->name);

    // 삭제/수정 반영 후 상태 확인
    all = readAll(path);
    ASSERT_EQ(2u, all.size());
    EXPECT_FALSE(findById(path, mia.id).has_value());
    EXPECT_EQ("Choe2", findById(path, choe.id)->name);
    EXPECT_EQ("Kim", findById(path, kim.id)->name);

    // Create: 삭제 후에도 id는 기존 최댓값(3) + 1 = 4, id 1 재사용 안 함
    Record park = createRecord(path, "Park", "010-4444-4444");
    EXPECT_EQ(4, park.id);

    // 존재하지 않는 id에 대한 Update/Delete는 예외 없이 nullopt
    EXPECT_FALSE(updateRecord(path, 999, "X", std::nullopt).has_value());
    EXPECT_FALSE(deleteRecord(path, 999).has_value());

    // 최종 상태: Choe2, Kim, Park 3명 남음
    all = readAll(path);
    ASSERT_EQ(3u, all.size());
}
