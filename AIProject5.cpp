#include <gtest/gtest.h>

#include <iostream>
#include <limits>
#include <optional>
#include <string>

#include "Create/Create.h"
#include "Delete/Delete.h"
#include "Read/Read.h"
#include "Record.h"
#include "Update/Update.h"

namespace {

const std::string kDataPath = "data.json";

void printRecord(const Record& record) {
    std::cout << "  [" << record.id << "] " << record.name << " - " << record.phone << "\n";
}

int readIntInput(const std::string& prompt) {
    std::cout << prompt;
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "숫자를 입력해주세요: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::string readLineInput(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

void handleCreate() {
    std::string name = readLineInput("이름: ");
    std::string phone = readLineInput("전화번호: ");
    Record record = createRecord(kDataPath, name, phone);
    std::cout << "추가되었습니다.\n";
    printRecord(record);
}

void handleReadAll() {
    std::vector<Record> records = readAll(kDataPath);
    if (records.empty()) {
        std::cout << "저장된 연락처가 없습니다.\n";
        return;
    }
    for (const auto& record : records) {
        printRecord(record);
    }
}

void handleFindById() {
    int id = readIntInput("찾을 id: ");
    std::optional<Record> found = findById(kDataPath, id);
    if (!found.has_value()) {
        std::cout << "해당 id의 연락처가 없습니다.\n";
        return;
    }
    printRecord(*found);
}

void handleUpdate() {
    int id = readIntInput("수정할 id: ");
    if (!findById(kDataPath, id).has_value()) {
        std::cout << "해당 id의 연락처가 없습니다.\n";
        return;
    }

    std::string name = readLineInput("새 이름 (건너뛰려면 빈 값): ");
    std::string phone = readLineInput("새 전화번호 (건너뛰려면 빈 값): ");
    std::optional<std::string> newName = name.empty() ? std::nullopt : std::optional<std::string>(name);
    std::optional<std::string> newPhone = phone.empty() ? std::nullopt : std::optional<std::string>(phone);

    std::optional<Record> updated = updateRecord(kDataPath, id, newName, newPhone);
    std::cout << "수정되었습니다.\n";
    printRecord(*updated);
}

void handleDelete() {
    int id = readIntInput("삭제할 id: ");
    std::optional<Record> found = findById(kDataPath, id);
    if (!found.has_value()) {
        std::cout << "해당 id의 연락처가 없습니다.\n";
        return;
    }

    std::cout << "삭제하시겠습니까?\n";
    printRecord(*found);
    std::string answer = readLineInput("(y/n): ");
    if (answer != "y" && answer != "Y") {
        std::cout << "취소되었습니다.\n";
        return;
    }

    deleteRecord(kDataPath, id);
    std::cout << "삭제되었습니다.\n";
}

void printMenu() {
    std::cout << "\n1. Create\n2. Read (전체 목록)\n3. Read (id 검색)\n"
                  "4. Update\n5. Delete\n6. Exit\n선택: ";
}

void runConsoleMenu() {
    while (true) {
        printMenu();
        int choice;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                return;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: handleCreate(); break;
                case 2: handleReadAll(); break;
                case 3: handleFindById(); break;
                case 4: handleUpdate(); break;
                case 5: handleDelete(); break;
                case 6: return;
                default: std::cout << "잘못된 선택입니다.\n"; break;
            }
        } catch (const std::exception& e) {
            std::cout << "오류가 발생했습니다: " << e.what() << "\n";
        }
    }
}

}  // namespace

int main(int argc, char** argv) {
    // 인자가 하나라도 있으면 테스트 모드로 취급한다. Visual Studio의
    // GoogleTest 어댑터(Test Explorer)는 --test가 아니라
    // --gtest_list_tests 같은 자체 플래그로 실행 파일을 호출하므로,
    // 특정 플래그 이름 대신 "인자 존재 여부"로 분기해야 어댑터와도
    // 정상 동작한다.
    if (argc > 1) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

    runConsoleMenu();
    return 0;
}
