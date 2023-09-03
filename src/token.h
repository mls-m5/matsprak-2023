#pragma once

#include "ast.h"
#include <string>
#include <string_view>

#include <stdexcept>

enum TokenType {
    // Uncategorized
    Invalid,
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

    // Unary and basic operators
    Plus,     // +
    Minus,    // -
    Multiply, // *
    Divide,   // /
    Modulo,   // %
    And,      // &
    Or,       // |
    Xor,      // ^
    Not,      // !
    Tilde,    // ~
    Equals,   // =

    // Unary operators
    PlusPlus,   // ++
    MinusMinus, // --

    // Assignment operators
    PlusEqual,       // +=
    MinusEqual,      // -=
    MulEqual,        // *=
    DivEqual,        // /=
    ModEqual,        // %=
    AndEqual,        // &=
    OrEqual,         // |=
    XorEqual,        // ^=
    RightShiftEqual, // >>=
    LeftShiftEqual,  // <<=

    // Relational operators
    EqualEqual,     // ==
    NotEqual,       // !=
    Less,           // <
    Greater,        // >
    LessOrEqual,    // <=
    GreaterOrEqual, // >=

    // Logical operators
    LogicalAnd, // &&
    LogicalOr,  // ||

    // Bitwise shift operators
    LeftShift,  // <<
    RightShift, // >>

    // Member Access
    Arrow,     // ->
    ArrowStar, // ->*

    // Scope resolution
    ScopeResolution, // ::

    // Pointer to member
    DotStar // .*
};

constexpr Ast category(TokenType type) {
    switch (type) {
    case Invalid:
    case ParenthesesBegin:
    case ParenthesesEnd:
    case Word:
    case NumericLiteral:
    case BraceBegin:
    case BraceEnd:
    case Comma:
    case Semicolon:
        return Ast::Uncategorized;

    case Let:
    case Template:
    case Type:
    case Fn:
        return Ast::KeyWord;

    case PlusPlus:
    case MinusMinus:
        return Ast::UnaryOperator;

    case Plus:
    case Minus:
    case Multiply:
    case Divide:
    case Modulo:
    case And:
    case Or:
    case Xor:
    case Not:
    case Tilde:
    case Equals:
        return Ast::BasicOperator;

    case PlusEqual:
    case MinusEqual:
    case MulEqual:
    case DivEqual:
    case ModEqual:
    case AndEqual:
    case OrEqual:
    case XorEqual:
    case RightShiftEqual:
    case LeftShiftEqual:
        return Ast::BinaryOperator;

    case EqualEqual:
    case NotEqual:
    case Less:
    case Greater:
    case LessOrEqual:
    case GreaterOrEqual:
        return Ast::RelationalOperator;

    case LogicalAnd:
    case LogicalOr:
        return Ast::LogicalOperator;

    case LeftShift:
    case RightShift:
        return Ast::BitwiseShiftOperator;

    case Arrow:
    case ArrowStar:
        return Ast::MemberAccessOperator;

    case ScopeResolution:
        return Ast::ScopeOperator;

    case DotStar:
        return Ast::PointerToMemberOperator;
    }

    throw std::invalid_argument("Invalid TokenType");
}

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

    Ast astType() const {
        return _astType;
    }

private:
    std::string_view _text;
    TokenType _type;
    Ast _astType = Ast::Uncategorized;
    Token *next = nullptr;
    Token *children = nullptr;
};

inline std::string_view toString(TokenType t) {
    switch (t) {
    case Invalid:
        return "Invalid";
    case ParenthesesBegin:
        return "ParenthesesBegin";
    case ParenthesesEnd:
        return "ParenthesesEnd";
    case Word:
        return "Word";
    case NumericLiteral:
        return "NumericLiteral";
    case BraceBegin:
        return "BraceBegin";
    case BraceEnd:
        return "BraceEnd";
    case Comma:
        return "Comma";
    case Semicolon:
        return "Semicolon";
    case Let:
        return "Let";
    case Template:
        return "Template";
    case Type:
        return "Type";
    case Fn:
        return "Fn";

    case Plus:
        return "Plus";
    case Minus:
        return "Minus";
    case Multiply:
        return "Multiply";
    case Divide:
        return "Divide";
    case Modulo:
        return "Modulo";
    case And:
        return "And";
    case Or:
        return "Or";
    case Xor:
        return "Xor";
    case Not:
        return "Not";
    case Tilde:
        return "Tilde";
    case Equals:
        return "Equals";

    case PlusPlus:
        return "PlusPlus";
    case MinusMinus:
        return "MinusMinus";

    case PlusEqual:
        return "PlusEqual";
    case MinusEqual:
        return "MinusEqual";
    case MulEqual:
        return "MulEqual";
    case DivEqual:
        return "DivEqual";
    case ModEqual:
        return "ModEqual";
    case AndEqual:
        return "AndEqual";
    case OrEqual:
        return "OrEqual";
    case XorEqual:
        return "XorEqual";
    case RightShiftEqual:
        return "RightShiftEqual";
    case LeftShiftEqual:
        return "LeftShiftEqual";

    case EqualEqual:
        return "EqualEqual";
    case NotEqual:
        return "NotEqual";
    case Less:
        return "Less";
    case Greater:
        return "Greater";
    case LessOrEqual:
        return "LessOrEqual";
    case GreaterOrEqual:
        return "GreaterOrEqual";

    case LogicalAnd:
        return "LogicalAnd";
    case LogicalOr:
        return "LogicalOr";

    case LeftShift:
        return "LeftShift";
    case RightShift:
        return "RightShift";

    case Arrow:
        return "Arrow";
    case ArrowStar:
        return "ArrowStar";

    case ScopeResolution:
        return "ScopeResolution";

    case DotStar:
        return "DotStar";
    }
    throw std::runtime_error{"Invalid TokenType"};
}
