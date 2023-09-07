
#include "astgrouping.h"
#include "codegenerator.h"
#include "testfile.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(CodegenTest, BasicTest) {
    std::string code = R"(
        fn main() {
            let b = (x(arg) + y);
            let x = 10;
            x = 30;
        }
    )";

    auto file = TestFile{code};

    auto ast = Ast{*file.tfile};

    groupParentheses(ast);
    groupAst(ast);

    std::cerr << ast << std::endl;

    auto gen = CodeGenerator{};
    gen.generateRoot(ast);
}
