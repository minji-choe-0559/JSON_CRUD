#include <gtest/gtest.h>

#include <string>

#include "../JsonStoreDemo.h"

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runJsonStoreDemo("data.json");
        return 0;
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
