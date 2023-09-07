
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

TEST(ParserTest, BasicTest) {
    std::string code = R"(
        let x = 10;
        x = 30;
        let y: int;

        y = 1 + 2 * 3;

        fn hello(text: string_view) {
            let apa = Apa();
        }
    )";

    std::cerr << code << "\n";

    auto file = TestFile{code};

    auto ast = Ast{*file.tfile};

    groupParentheses(ast);
    groupAst(ast);

    std::cerr << ast << std::endl;
}

TEST(ParserTest, Functions) {
    std::string code = R"(
        fn there(text: string_view) {
            print(text);
        }

        fn hello(text: string_view, unused: int) {
            there(text);
        }
    )";

    std::cerr << code << "\n";

    auto file = TestFile{code};

    auto ast = Ast{*file.tfile};

    groupParentheses(ast);
    groupAst(ast);

    std::cerr << ast << std::endl;
}

TEST(ParserTest, Structs) {
    std::string code = R"(
        struct Apa {
            fn print(text: string_view) {
                x(text);
            }
        }

        fn hello(text: string_view, unused: int) {
            let apa = Apa();
            apa.print("hello");
        }
    )";

    std::cerr << code << "\n";

    auto file = TestFile{code};

    auto ast = Ast{*file.tfile};

    groupParentheses(ast);
    groupAst(ast);

    std::cerr << ast << std::endl;
}

TEST(ParserTest, Parentheses) {
    std::string code = R"(
        let x = (x + 2 * (f(10)));
    )";

    std::cerr << code << "\n";

    auto file = TestFile{code};

    auto ast = Ast{*file.tfile};

    groupParentheses(ast);
    groupAst(ast);

    std::cerr << ast << std::endl;
}

TEST(ParserTest, Types) {
    std::string code = R"(
          x: int;
          let y: int;
    )";

    std::cerr << code << "\n";

    auto file = TestFile{code};

    auto ast = Ast{*file.tfile};

    groupParentheses(ast);
    groupAst(ast);

    std::cerr << ast << std::endl;
}

TEST(ParserTest, ArgumentTypes) {
    std::string code = R"(
        (y: int, y: int)
        (x: int)
    )";

    std::cerr << code << "\n";

    auto file = TestFile{code};

    auto ast = Ast{*file.tfile};

    groupParentheses(ast);
    groupAst(ast);

    std::cerr << ast << std::endl;
}
