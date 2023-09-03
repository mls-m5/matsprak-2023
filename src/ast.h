#pragma once

// enum AstType {
//     InvalidAst,
//     LetStatement,
//     BeginGroup,
//     EndGroup,
// };

#include <stdexcept>
#include <string_view>

enum class Ast {
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
    Punctuation,

    Let,

    /// Processed statements
    LetStatement,
    BeginGroup,
    EndGroup,
};

constexpr std::string_view toString(Ast t) {
    switch (t) {
    case Ast::Uncategorized:
        return "Uncategorized";
    case Ast::KeyWord:
        return "KeyWord";
    case Ast::UnaryOperator:
        return "UnaryOperator";
    case Ast::BasicOperator:
        return "BasicOperator";
    case Ast::BinaryOperator:
        return "BinaryOperator";
    case Ast::RelationalOperator:
        return "RelationalOperator";
    case Ast::LogicalOperator:
        return "LogicalOperator";
    case Ast::BitwiseShiftOperator:
        return "BitwiseShiftOperator";
    case Ast::MemberAccessOperator:
        return "MemberAccessOperator";
    case Ast::ScopeOperator:
        return "ScopeOperator";
    case Ast::PointerToMemberOperator:
        return "PointerToMemberOperator";
    case Ast::Punctuation:
        return "Punctuation";
    case Ast::Let:
        return "Let";
    case Ast::LetStatement:
        return "LetStatement";
    case Ast::BeginGroup:
        return "BeginGroup";
    case Ast::EndGroup:
        return "EndGroup";
    }
    throw std::runtime_error{"Invalid ast type"};
}
