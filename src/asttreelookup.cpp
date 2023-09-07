#include "asttreelookup.h"
#include "tokentype.h"

StateComposite::StateComposite() {
    // Using c++ operator precedence
    // https://en.cppreference.com/w/cpp/language/operator_precedence

    using T = TokenType;

    {
        // Complex expressions
        auto &l = lookups.emplace_back();
        l.add(T::StructDeclaration,
              {T::Struct, {T::Word, T::Name}, T::BraceGroup});
        l.add(T::FunctionDeclaration,
              {T::Fn, {T::Word, T::Name}, T::ParenGroup});
        l.add(T::FunctionDeclaration,
              {T::Fn, {T::Word, T::Name}, T::ParenGroup, T::BraceGroup});
    }
    {
        // 2
        auto &l = lookups.emplace_back();

        l.add(T::FunctionCall,
              {T::Expression, T::ParenGroup},
              {T::FunctionDeclaration});

        l.add(T::MemberAccessor,
              {T::Expression, T::MemberAccessOperator, T::Expression});
    }

    {
        // 16
        auto &l = lookups.emplace_back();

        l.add(T::AssignmentExpression,
              {T::Expression, {T::Equals, T::BinaryOperator}, T::Expression});
    }

    {
        // Unordered
        auto &l = lookups.emplace_back();

        l.add(T::BinaryOperation,
              {T::Expression, T::BinaryOperator, T::Expression});

        l.add(T::LetStatement, {T::Let, T::AssignmentExpression, T::Semicolon});

        /// TODO: Create separate result type?
        l.add(T::LetStatement, {T::Let, T::Word, T::Colon, T::Expression});

        /// TODO: Why does Expression work, but not Word for the first type?
        l.add(T::VariableWithType, {T::Expression, T::Colon, T::Expression});
    }
    {
        // Semicolons
        auto &l = lookups.emplace_back();
        l.add(T::Statement, {T::Expression, T::Semicolon});
        l.add(T::CommaList, {T::Expression, T::Comma, T::Expression});
    }
}
