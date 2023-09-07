#include "asttreelookup.h"

StateComposite::StateComposite() {
    // Using c++ operator precedence
    // https://en.cppreference.com/w/cpp/language/operator_precedence

    {
        // Complex expressions
        auto &l = lookups.emplace_back();
        l.add(StructDeclaration, {Struct, {Word, Name}, BraceGroup});
        l.add(FunctionDeclaration, {Fn, {Word, Name}, ParenGroup});
        l.add(FunctionDeclaration,
              {Fn, {Word, Name}, ParenGroup, BraceGroup});
    }
    {
        // 2
        auto &l = lookups.emplace_back();

        l.add(
            FunctionCall, {Expression, ParenGroup}, {FunctionDeclaration});

        l.add(MemberAccessor,
              {Expression, MemberAccessOperator, Expression});
    }

    {
        // 16
        auto &l = lookups.emplace_back();

        l.add(AssignmentExpression,
              {Expression, {Equals, BinaryOperator}, Expression});
    }

    {
        // Unordered
        auto &l = lookups.emplace_back();

        l.add(BinaryOperation, {Expression, BinaryOperator, Expression});

        l.add(LetStatement, {Let, AssignmentExpression, Semicolon});

               /// TODO: Create separate result type?
        l.add(LetStatement, {Let, Word, Colon, Expression});

               /// TODO: Why does Expression work, but not Word for the first type?
        l.add(VariableWithType, {Expression, Colon, Expression});
    }
    {
        // Semicolons
        auto &l = lookups.emplace_back();
        l.add(Statement, {Expression, Semicolon});
        l.add(CommaList, {Expression, Comma, Expression});
    }
}
