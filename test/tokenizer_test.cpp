
#include "token.h"
#include "tokenizer.h" // Include your tokenizer header file here
#include <filesystem>
#include <gtest/gtest.h>
#include <iomanip>
#include <sstream>
#include <string>

TEST(TokenizerTest, ParenTest) {
    std::string code = R"(
        ();
        fn main() { }
     )";

    std::shared_ptr<File> file = File::from_string(std::move(code), "test.msp");

    auto tfile = tokenize(file);

    std::cerr << *tfile << "\n";
    TokenIterator it = tfile;

    std::vector<std::string> expected = {
        "(", ")", ";", "fn", "main", "(", ")", "{", "}"};

    for (const auto &expected_token : expected) {
        ASSERT_TRUE(it.current() != nullptr);
        EXPECT_EQ(expected_token, it.current()->text());
        ++it;
    }

    ASSERT_EQ(nullptr, it.current());
}

TEST(TokenizerTest, SingleDoubleCharacterOperator) {
    std::string code = R"(
        ++ ++
     )";

    std::shared_ptr<File> file = File::from_string(std::move(code), "test.msp");

    auto tfile = tokenize(file);

    std::cerr << *tfile << "\n";
    TokenIterator it = tfile;

    std::vector<std::string> expected = {"++", "++"};

    for (const auto &expected_token : expected) {
        ASSERT_TRUE(it.current() != nullptr);
        EXPECT_EQ(expected_token, it.current()->text());
        ++it;
    }

    ASSERT_EQ(nullptr, it.current());
}

TEST(TokenizerTest, BasicTest) {
    std::string code = R"(
         fn main() {
             let x = 10;
             let y = 20;
             let sum = x + y;
         }
     )";

    std::shared_ptr<File> file = File::from_string(std::move(code), "test.msp");

    auto tfile = tokenize(file);
    TokenIterator it = tfile;

    std::cerr << *tfile << std::endl;

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

TEST(TokenizerTest, OperatorTest) {
    std::string code = R"(
         fn main() {
            let i = 0;
            let x = x ^ 2 + ++i;
            let y = &x;
         }
     )";

    std::shared_ptr<File> file = File::from_string(std::move(code), "test.msp");

    auto tfile = tokenize(file);

    std::cerr << *tfile << std::endl;

    TokenIterator it = tfile;

    std::vector<std::string> expected = {
        "fn", "main", "(",   ")", "{", "let", "i", "=", "0",
        ";",  "let",  "x",   "=", "x", "^",   "2", "+", "++",
        "i",  ";",    "let", "y", "=", "&",   "x", ";", "}"};

    for (const auto &expected_token : expected) {
        ASSERT_TRUE(it.current() != nullptr);
        EXPECT_EQ(expected_token, it.current()->text());
        ++it;
    }

    ASSERT_EQ(nullptr, it.current());
}
