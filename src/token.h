#pragma once

#include <string>
#include <string_view>

enum TokenCategory {
    KeyWord,
    BinaryOperator,
    UnaryOperator,
};

enum TokenType {
    Invalid, // Use only as default value
    ParenthesesBegin,
    ParenthesesEnd,
    Word,
    NumericLiteral,
    BraceBegin,
    BraceEnd,
    Comma,
    Semicolon,
    Let,
    Template,
    Type,
    Fn,
};

struct TypePair {
    TokenCategory cat;
    TokenType
};

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

private:
    std::string_view _text;
    TokenType _type;
};
