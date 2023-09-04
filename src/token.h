#pragma once

#include "ast.h"
#include <string>
#include <string_view>

#include <stdexcept>

#if 0
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


    // Ast types --------------------------


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
#endif

#define TOKEN_TYPE_LIST(X)                                                     \
    /* Uncategorized */                                                        \
    X(Invalid, Uncategorized)                                                  \
    X(ParenthesesBegin, BeginGroup)                                            \
    X(ParenthesesEnd, EndGroup)                                                \
    X(Word, Expression)                                                        \
    X(NumericLiteral, Expression)                                              \
    X(BraceBegin, Uncategorized)                                               \
    X(BraceEnd, Uncategorized)                                                 \
    X(Comma, Uncategorized)                                                    \
    X(Semicolon, Uncategorized)                                                \
    /* KeyWords */                                                             \
    X(Let, KeyWord)                                                            \
    X(Template, KeyWord)                                                       \
    X(Type, KeyWord)                                                           \
    X(Fn, KeyWord)                                                             \
    /* Unary and basic operators */                                            \
    X(Plus, BasicOperator)     /* + */                                         \
    X(Minus, BasicOperator)    /* - */                                         \
    X(Multiply, BasicOperator) /* * */                                         \
    X(Divide, BasicOperator)   /* / */                                         \
    X(Modulo, BasicOperator)   /* % */                                         \
    X(And, BasicOperator)      /* & */                                         \
    X(Or, BasicOperator)       /* | */                                         \
    X(Xor, BasicOperator)      /* ^ */                                         \
    X(Not, BasicOperator)      /* ! */                                         \
    X(Tilde, BasicOperator)    /* ~ */                                         \
    X(Equals, BasicOperator)   /* = */                                         \
    /* Unary operators */                                                      \
    X(PlusPlus, UnaryOperator)   /* ++ */                                      \
    X(MinusMinus, UnaryOperator) /* -- */                                      \
    /* Assignment operators */                                                 \
    X(PlusEqual, BinaryOperator)       /* += */                                \
    X(MinusEqual, BinaryOperator)      /* -= */                                \
    X(MulEqual, BinaryOperator)        /* *= */                                \
    X(DivEqual, BinaryOperator)        /* /= */                                \
    X(ModEqual, BinaryOperator)        /* %= */                                \
    X(AndEqual, BinaryOperator)        /* &= */                                \
    X(OrEqual, BinaryOperator)         /* |= */                                \
    X(XorEqual, BinaryOperator)        /* ^= */                                \
    X(RightShiftEqual, BinaryOperator) /* >>= */                               \
    X(LeftShiftEqual, BinaryOperator)  /* <<= */                               \
    /* Relational operators */                                                 \
    X(EqualEqual, RelationalOperator)     /* == */                             \
    X(NotEqual, RelationalOperator)       /* != */                             \
    X(Less, RelationalOperator)           /* < */                              \
    X(Greater, RelationalOperator)        /* > */                              \
    X(LessOrEqual, RelationalOperator)    /* <= */                             \
    X(GreaterOrEqual, RelationalOperator) /* >= */                             \
    /* Logical operators */                                                    \
    X(LogicalAnd, LogicalOperator) /* && */                                    \
    X(LogicalOr, LogicalOperator)  /* || */                                    \
    /* Bitwise shift operators */                                              \
    X(LeftShift, BitwiseShiftOperator)  /* << */                               \
    X(RightShift, BitwiseShiftOperator) /* >> */                               \
    /* Member Access */                                                        \
    X(Arrow, MemberAccessOperator)     /* -> */                                \
    X(ArrowStar, MemberAccessOperator) /* ->* */                               \
    /* Scope resolution */                                                     \
    X(ScopeResolution, ScopeOperator) /* :: */                                 \
    /* Pointer to member */                                                    \
    X(DotStar, PointerToMemberOperator) /* .* */                               \
    /* Additional Ast Tokens */                                                \
    X(Uncategorized, Uncategorized)                                            \
    X(KeyWord, Uncategorized)                                                  \
    X(UnaryOperator, Uncategorized)                                            \
    X(BasicOperator, Uncategorized)                                            \
    X(BinaryOperator, Uncategorized)                                           \
    X(RelationalOperator, Uncategorized)                                       \
    X(LogicalOperator, Uncategorized)                                          \
    X(BitwiseShiftOperator, Uncategorized)                                     \
    X(MemberAccessOperator, Uncategorized)                                     \
    X(ScopeOperator, Uncategorized)                                            \
    X(PointerToMemberOperator, Uncategorized)                                  \
    X(Punctuation, Uncategorized)                                              \
    X(LetStatement, Uncategorized)                                             \
    X(BeginGroup, Uncategorized)                                               \
    X(EndGroup, Uncategorized)                                                 \
    X(AssignmentExpression, Uncategorized)                                     \
    X(Expression, Uncategorized)                                               \
    X(Statement, Uncategorized)                                                \
    X(Count, Uncategorized) // This should always be the last item

// Generate enum
enum TokenType {
#define ENUM_ITEM(name, ast_type) name,
    TOKEN_TYPE_LIST(ENUM_ITEM)
#undef ENUM_ITEM
};

// Generate category function
constexpr TokenType category(TokenType type) {
    switch (type) {
#define CASE_ITEM(name, ast_type)                                              \
    case name:                                                                 \
        return ast_type;
        TOKEN_TYPE_LIST(CASE_ITEM)
#undef CASE_ITEM
    default:
        throw std::invalid_argument("Invalid TokenType");
    }
}

// Generate toString function
inline std::string_view toString(TokenType t) {
    switch (t) {
#define CASE_ITEM(name, ast_type)                                              \
    case name:                                                                 \
        return #name;
        TOKEN_TYPE_LIST(CASE_ITEM)
#undef CASE_ITEM
    default:
        throw std::runtime_error{"Invalid TokenType"};
    }
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

    void type(TokenType t) {
        _type = t;
    }

private:
    std::string_view _text;
    TokenType _type;
    Token *next = nullptr;
    Token *children = nullptr;
};

#if 0
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
#endif
