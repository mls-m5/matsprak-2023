#pragma once

#include "tokenizer.h"
#include <memory>

struct TestFile {
    TestFile(std::string code)
        : code{std::move(code)} {}

    std::string code;
    std::shared_ptr<File> file = File::from_string(code, "test.msp");
    std::shared_ptr<TokenizedFile> tfile = tokenize(file);

    void print() {}
};
