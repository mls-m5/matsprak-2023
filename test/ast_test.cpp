
#include "ast.h"
#include "astgrouping.h"
#include "testfile.h"
#include "tokenizer.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

TEST(AstTest, BasicTest) {
    std::string code = R"(
        let b = (x(arg) + y);
        let x = 10;
        x = 30;
    )";

    auto file = TestFile{code};

    std::cout << *file.tfile << std::endl;

    auto ast = Ast{*file.tfile};

    groupParentheses(ast);

    std::cout << ast << std::endl;
}
