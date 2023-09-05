
#include "ast.h"
#include "file.h"
#include "tokenizer.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

void groupParentheses(Ast &ast, ptrdiff_t a) {
    for (size_t i = a; i < ast.children().size(); ++i) {
        auto child = ast.children().at(i).get();
        if (child->type() == ParenthesesBegin) {
            groupParentheses(ast, i + 1);

            for (size_t j = i + 1; j < ast.children().size(); ++j) {
                auto child2 = ast.children().at(j).get();
                if (child2->type() == ParenthesesEnd) {
                    ast.group(
                        ParenGroup, ast.begin() + i, ast.begin() + j + 1, true);
                    i = i + 1;
                    break;
                }
            }
        }
    }
}

void groupParentheses(Ast &ast) {
    groupParentheses(ast, 1);
}

TEST(AstTest, BasicTest) {
    std::string code = R"(
        let b = (x(arg) + y);
        let x = 10;
        x = 30;
    )";

    std::shared_ptr<File> file = File::from_string(code, "test.msp");
    auto tfile = tokenize(file);

    std::cout << *tfile << std::endl;

    auto ast = Ast{*tfile};

    //    ast.group(Invalid, ast.begin() + 1, ast.begin() + 4);
    groupParentheses(ast);

    std::cout << ast << std::endl;
}
