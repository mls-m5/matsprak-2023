#pragma once

#include "tokentype.h"
#include <iosfwd>
#include <stdexcept>
#include <string>
#include <string_view>

struct Token {
    Token(const Token &) = default;
    Token(Token &&) = default;
    Token &operator=(const Token &) = default;
    Token &operator=(Token &&) = default;
    ~Token() = default;

    Token(std::string_view text, TokenType type)
        : _text{text}
        , _type{type} {}

    std::string_view text() const {
        return _text;
    }

    TokenType type() const {
        return _type;
    }

    void type(TokenType t) {
        _type = t;
    }

    void children(Token *c) {
        _children = c;
    }

    void next(Token *n) {
        _next = n;
    }

    void print(std::ostream &stream, int indent = 0);

private:
    std::string_view _text;
    TokenType _type;
    Token *_next = nullptr;
    Token *_children = nullptr;
};
