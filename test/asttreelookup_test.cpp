
#include "ast.h"
#include "astgrouping.h"
#include "asttreelookup.h"
#include "testfile.h"
#include "tokenizer.h"
#include "tokentype.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

//// Special parsing tests

TEST(AstTreeLookup, AFunctionDeclarationShouldNotContainAFunctionCall) {
    std::string code = R"(
        fn hello(text: string_view) {
        }

        fn main() {
        }
    )";

    std::cerr << code << "\n";

    auto file = TestFile{code};

    auto ast = Ast{*file.tfile};

    groupParentheses(ast);
    groupAst(ast);

    std::cerr << ast << std::endl;
    EXPECT_FALSE(ast.find(FunctionCall, true));
}
