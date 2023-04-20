#pragma once

#include "file.h"
#include <string_view>

struct TokenType {
    // More types
};

struct Token {
    std::shared_ptr<File> _file;
    std::string_view _text;

    std::string_view text() const {
        return _text;
    }
};

struct TIterator {
    const Token &operator()() {
        return current();
    }

    Token &current() {
        //
    }

    Token &next() {
        //
    }
};
