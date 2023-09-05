#pragma once

#include <iosfwd>
#include <stdexcept>
#include <string>
#include <string_view>

/// The first argument is what the token is called
/// The second argument it its "parent" i.e the more abstract version of the
/// concept
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
    X(Plus, BasicOperator)      /* + */                                        \
    X(Minus, BasicOperator)     /* - */                                        \
    X(Multiply, BasicOperator)  /* * */                                        \
    X(Divide, BasicOperator)    /* / */                                        \
    X(Modulo, BasicOperator)    /* % */                                        \
    X(And, BasicOperator)       /* && */                                       \
    X(BinaryAnd, BasicOperator) /* & */                                        \
    X(BinaryOr, BasicOperator)  /* | */                                        \
    X(Or, BasicOperator)        /* || */                                       \
    X(Xor, BasicOperator)       /* ^ */                                        \
    X(Not, BasicOperator)       /* ! */                                        \
    X(Tilde, BasicOperator)     /* ~ */                                        \
    X(Equals, BasicOperator)    /* = */                                        \
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
    X(RootNode, Uncategorized)                                                 \
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
