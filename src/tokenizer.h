#pragma once

#include "file.h"
#include <string_view>

enum TokenType {
    ParenthesesBegin,
    ParenthesesEnd,
    Word,
    NumericLiteral,
    BraceBegin,
    BraceEnd,
    Comma,
    Semicolon,
    BinaryOperator,
    Let,
    Template,
    Type,
    Fn,
};

struct Token {
    std::string _text;
    TokenType _type;

    std::string_view text() const {
        return _text;
    }
};

struct TokenizedFile;

struct TokenIterator {
    std::shared_ptr<TokenizedFile> _file;
    std::vector<Token>::iterator _current;
    std::vector<Token>::iterator _end;

    TokenIterator(std::shared_ptr<TokenizedFile> file);

    TokenIterator(const TokenIterator &) = delete;
    TokenIterator(TokenIterator &&) = default;

    const Token &operator()() {
        return *current();
    }

    Token *current() {
        if (_current == _end) {
            return nullptr;
        }
        return &(*_current);
    }

    Token *next() {
        if (_current == _end || std::next(_current) == _end) {
            return nullptr;
        }
        return &(*std::next(_current));
    }

    TokenIterator &operator++() {
        if (_current != _end) {
            ++_current;
        }
        return *this;
    }

    //    TokenIterator operator++(int) {
    //        TokenIterator tmp(*this);
    //        operator++();
    //        return tmp;
    //    }

    // Add more functions if needed
};

TokenIterator tokenize(const std::shared_ptr<File> &file);
