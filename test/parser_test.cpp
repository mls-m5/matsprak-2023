
// #include "astmodule.h"
#include "asttreelookup.h"
#include "file.h"
#include "token.h"
#include "tokenizer.h"
// #include "parser.h"
#include "ast.h"
#include "astgrouping.h"
#include "testfile.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

TEST(ParserTest, BasicTest) {
    std::string code = R"(
        let x = 10;
        x = 30;
        let y: int;


        fn main() {
            let apa = Apa();
        }
    )";

    std::cerr << code << "\n";

    auto file = TestFile{code};
    auto it = TokenIterator{file.tfile};

    auto tree = AstTreeLookup{};
    auto state = AstTreeState{tree};

    std::cerr << *file.tfile << std::endl;

    for (; it.current(); ++it) {
        std::cerr << std::setw(10) << std::left << it.current()->text();

        std::cerr << std::setw(20) << std::left
                  << toString(it.current()->type());

        auto t = state.push(it.current()->type());
        if (t) {
            std::cerr << toString(t->type);

            std::cerr << ": ";
            auto resVec = std::vector<TokenType>{};
            for (auto res = t; res != nullptr; res = res->parent) {
                resVec.push_back(res->matcher.result);
            }
            resVec.pop_back();
            std::reverse(resVec.begin(), resVec.end());

            for (auto r : resVec) {
                std::cerr << toString(r) << " ";
            }
        }

        std::cerr << std::endl;
    }

    auto ast = Ast{*file.tfile};

    groupParentheses(ast);
    groupAst(ast);

    std::cerr << ast << std::endl;
}
