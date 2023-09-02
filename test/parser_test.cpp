
#include "astmodule.h"
#include "file.h"
#include "parser.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

TEST(ParserTest, BasicTest) {
    std::string code = R"(
        module main;
        import apa;

        fn main() {
            let x = 10;
            let y = 20;
            let sum = x + y;
        }
    )";

    std::shared_ptr<File> file = File::from_string(code, "test.msp");

    AstModule module;

    parse(module, file);
}
