
// #include "astmodule.h"
#include "asttreelookup.h"
#include "file.h"
#include "token.h"
#include "tokenizer.h"
// #include "parser.h"
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
    )";

    std::shared_ptr<File> file = File::from_string(code, "test.msp");
    auto it = tokenize(file);

    auto tree = AstTreeLookup{};
    auto state = AstTreeState{tree};

    for (; it.current(); ++it) {
        std::cout << std::setw(10) << std::left << it.current()->text();

        std::cout << std::setw(20) << std::left
                  << toString(it.current()->type());

        auto t = state.push(it.current()->type());
        if (t) {
            std::cout << toString(t->type);
        }

        std::cout << std::endl;
    }

    //    AstModule module;

    //    parse(module, file);
}

// TEST(ParserTest, BasicTest) {
//     std::string code = R"(
//         module main;
//         import apa;

//        fn main() {
//            let x = 10;
//            let y = 20;
//            let sum = x + y;
//        }
//    )";

//    std::shared_ptr<File> file = File::from_string(code, "test.msp");

////    AstModule module;

////    parse(module, file);
//}
