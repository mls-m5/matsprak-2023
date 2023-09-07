#pragma once

#include <stdexcept>
#include <string_view>

/// The first argument is what the token is called
/// The second argument it its "parent" i.e the more abstract version of the
/// concept
#define TOKEN_TYPE_LIST(X)                                                     \
    /* Uncategorized */                                                        \
    X(Invalid, Uncategorized)                                                  \
    X(ParenthesesBegin, BeginGroup)                                            \
    X(ParenthesesEnd, EndGroup)                                                \
    X(ParenGroup, Expression)                                                  \
    X(BraceGroup, Uncategorized)                                               \
    X(BracketGroup, Uncategorized)                                             \
    X(Word, Expression)                                                        \
    X(Name, Uncategorized)                                                     \
    X(NumericLiteral, Expression)                                              \
    X(BraceBegin, Uncategorized)                                               \
    X(BraceEnd, Uncategorized)                                                 \
    X(BracketBegin, Uncategorized)                                             \
    X(BracketEnd, Uncategorized)                                               \
    X(Comma, Uncategorized)                                                    \
    X(Colon, Uncategorized)                                                    \
    X(Semicolon, Uncategorized)                                                \
    /* KeyWords */                                                             \
    X(Let, KeyWord)                                                            \
    X(Template, KeyWord)                                                       \
    X(Type, KeyWord)                                                           \
    X(Fn, KeyWord)                                                             \
    X(Struct, KeyWord)                                                         \
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
    X(Xor, UnaryOperator)       /* ^ */                                        \
    X(Not, UnaryOperator)       /* ! */                                        \
    X(Tilde, UnaryOperator)     /* ~ */                                        \
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
    X(Period, MemberAccessOperator)                                            \
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
    X(BasicOperator, BinaryOperator)                                           \
    X(BinaryOperator, Uncategorized)                                           \
    X(BinaryOperation, Expression)                                             \
    X(RelationalOperator, Uncategorized)                                       \
    X(LogicalOperator, Uncategorized)                                          \
    X(BitwiseShiftOperator, Uncategorized)                                     \
    X(MemberAccessor, Expression)                                              \
    X(MemberAccessOperator, Uncategorized)                                     \
    X(ScopeOperator, Uncategorized)                                            \
    X(PointerToMemberOperator, Uncategorized)                                  \
    X(Punctuation, Uncategorized)                                              \
    X(LetStatement, Statement)                                                 \
    X(StructDeclaration, Uncategorized)                                        \
    X(FunctionDeclaration, Uncategorized)                                      \
    X(FunctionCall, Expression)                                                \
    X(BeginGroup, Uncategorized)                                               \
    X(EndGroup, Uncategorized)                                                 \
    X(AssignmentExpression, Uncategorized)                                     \
    X(Expression, Uncategorized)                                               \
    X(Statement, Uncategorized)                                                \
    X(CommaList, Uncategorized)                                                \
    X(VariableWithType, Expression)                                            \
    X(Module, Uncategorized)                                                   \
    X(Import, Uncategorized)                                                   \
    X(Count, Uncategorized) // This should always be the last item

// Generate enum
enum class TokenType {
#define ENUM_ITEM(name, ast_type) name,
    TOKEN_TYPE_LIST(ENUM_ITEM)
#undef ENUM_ITEM
};

// Generate category function
constexpr TokenType category(TokenType type) {
    switch (type) {
#define CASE_ITEM(name, ast_type)                                              \
    case TokenType::name:                                                      \
        return TokenType::ast_type;
        TOKEN_TYPE_LIST(CASE_ITEM)
#undef CASE_ITEM
    default:
        throw std::invalid_argument("Invalid TokenType");
    }
}

// Generate toString function
constexpr inline std::string_view toString(TokenType t) {
    switch (t) {
#define CASE_ITEM(name, ast_type)                                              \
    case TokenType::name:                                                      \
        return #name;
        TOKEN_TYPE_LIST(CASE_ITEM)
#undef CASE_ITEM
    default:
        throw std::runtime_error{"Invalid TokenType"};
    }
}

/// type is the specific type, typeOrCategory also checks for parent catergories
constexpr inline bool doesMatch(TokenType type, TokenType typeOrCategory) {
    for (; typeOrCategory != TokenType::Uncategorized;
         typeOrCategory = category(typeOrCategory)) {
        if (typeOrCategory == type) {
            return true;
        }
    }
    return false;
}
