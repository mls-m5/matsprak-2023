
#include "astmodule.h"
#include "parser.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

TEST(TokenizerTest, BasicTest) {
    std::string_view code = R"(
        fn main() {
            let x = 10;
            let y = 20;
            let sum = x + y;
        }
    )";

    std::shared_ptr<File> file = File::fromString(code, "test.msp");

    AstModule module;

    parse(module, file);

    //    std::vector<std::string> expected = {
    //        "fn", "main", "(", ")",   "{",   "let", "x", "=", "10", ";",
    //        "let", "y",
    //        "=",  "20",   ";", "let", "sum", "=",   "x", "+", "y",  ";", "}"};

    //    for (const auto &expected_token : expected) {
    //        ASSERT_TRUE(it.current() != nullptr);
    //        EXPECT_EQ(expected_token, it.current()->text());
    //        ++it;
    //    }

    //    ASSERT_EQ(nullptr, it.current());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
