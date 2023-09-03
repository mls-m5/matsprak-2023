#pragma once

#include <string>
#include <string_view>

#include <stdexcept>

enum TokenCategory {
    Uncategorized,
    KeyWord,
    UnaryOperator,
    BasicOperator,
    BinaryOperator,
    RelationalOperator,
    LogicalOperator,
    BitwiseShiftOperator,
    MemberAccessOperator,
    ScopeOperator,
    PointerToMemberOperator,
    Punctuation
};

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

constexpr TokenCategory category(TokenType type) {
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
        return Uncategorized;

    case Let:
    case Template:
    case Type:
    case Fn:
        return KeyWord;

    case PlusPlus:
    case MinusMinus:
        return UnaryOperator;

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
        return BasicOperator;

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
        return BinaryOperator;

    case EqualEqual:
    case NotEqual:
    case Less:
    case Greater:
    case LessOrEqual:
    case GreaterOrEqual:
        return RelationalOperator;

    case LogicalAnd:
    case LogicalOr:
        return LogicalOperator;

    case LeftShift:
    case RightShift:
        return BitwiseShiftOperator;

    case Arrow:
    case ArrowStar:
        return MemberAccessOperator;

    case ScopeResolution:
        return ScopeOperator;

    case DotStar:
        return PointerToMemberOperator;
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

private:
    std::string_view _text;
    TokenType _type;
};
