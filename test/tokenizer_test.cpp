
#include "tokenizer.h" // Include your tokenizer header file here
#include <filesystem>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

TEST(TokenizerTest, BasicTest) {
    std::string code = R"(
         fn main() {
             let x = 10;
             let y = 20;
             let sum = x + y;
         }
     )";

    std::shared_ptr<File> file = File::from_string(std::move(code), "test.msp");

    TokenIterator it = tokenize(file);

    auto it2 = it;

    {
        Token *token = nullptr;
        for (auto it2 = it; (token = it2.current()); ++it2) {
            std::cerr << token->text() << "\n";
        }
    }

    std::vector<std::string> expected = {
        "fn", "main", "(", ")",   "{",   "let", "x", "=", "10", ";", "let", "y",
        "=",  "20",   ";", "let", "sum", "=",   "x", "+", "y",  ";", "}"};

    for (const auto &expected_token : expected) {
        ASSERT_TRUE(it.current() != nullptr);
        EXPECT_EQ(expected_token, it.current()->text());
        ++it;
    }

    ASSERT_EQ(nullptr, it.current());
}
