#pragma once

#include "tokentype.h"
#include <array>
#include <cstddef>
#include <list>
#include <map>
#include <ranges>
#include <span>
#include <stdexcept>
#include <string_view>
#include <variant>
#include <vector>

struct Matcher {
    Matcher(TokenType t, TokenType result = Uncategorized)
        : type{t}
        , result{(result != Uncategorized) ? result : t} {}

    bool operator()(TokenType t) const {
        for (; t != Uncategorized; t = category(t)) {
            if (t == type) {
                return true;
            }
        }

        return false;
    }

    bool operator==(const Matcher &other) const {
        return other.type == type && other.result == result;
    }

    TokenType type = Uncategorized;
    TokenType result = Uncategorized;
};

class AstTreeLookup {
public:
    struct Node {
        Node *parent = nullptr;
        Matcher matcher;

        Node(Node *parent, Matcher matcher)
            : parent{parent}
            , matcher{matcher} {}

        TokenType type = Uncategorized;

        bool hasType() const {
            return type != TokenType{Uncategorized};
        }

        /// List since we want to preserve the elements location in memory
        std::list<Node> children;

        const Node *find(TokenType t) const {
            for (auto &c : children) {
                if (c.matcher(t)) {
                    return &c;
                }
            }
            return nullptr;
        }

        Node *find(TokenType t) {
            for (auto &c : children) {
                if (c.matcher(t)) {
                    return &c;
                }
            }
            return nullptr;
        }

        Node &findOrCreate(Matcher t) {
            for (auto &c : children) {
                if (c.matcher == t) {
                    return c;
                }
            }
            children.push_back(Node{this, t});
            return children.back();
        }

        friend AstTreeLookup;

        void add(TokenType type, std::vector<Matcher> key) {
            if (key.empty()) {
                this->type = type;
                return;
            }
            findOrCreate(key.front())
                .add(type, std::vector(key.begin() + 1, key.end()));
        }
    };

    void add(TokenType resT, std::vector<Matcher> arr) {
        root.add(resT, arr);
    }

    AstTreeLookup() {
        //        using VecT = std::vector<Matcher>;
    }

    Node root{{}, {Uncategorized}};
};

class AstTreeState {
public:
    AstTreeLookup::Node *root = nullptr;
    AstTreeLookup::Node *current = nullptr;

    AstTreeState(AstTreeLookup &l)
        : root{&l.root}
        , current{&l.root} {}

    AstTreeState() = default;

    AstTreeLookup::Node *push(TokenType t) {
        if (auto f = current->find(t)) {
            current = f;
            return f;
        }

        return nullptr;
    }

    void reset() {
        current = root;
    }

    void reset(AstTreeLookup::Node *node) {
        root = current = node;
    }
};

class StateComposite {
public:
    AstTreeState state;

    std::vector<AstTreeLookup> lookups;

    StateComposite() {
        // Using c++ operator precedence
        // https://en.cppreference.com/w/cpp/language/operator_precedence

        {
            // Complex expressions
            auto &l = lookups.emplace_back();
            l.add(StructDeclaration, {Struct, {Word, Name}, BraceGroup});
            l.add(FunctionDeclaration, {Fn, Word, ParenGroup});
            l.add(FunctionDeclaration, {Fn, Word, ParenGroup, BraceGroup});
        }
        {
            // 2
            auto &l = lookups.emplace_back();

            l.add(FunctionCall,
                  {Expression,
                   ParenGroup}); // Does not seem to work for member accessors
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

    StateComposite(const StateComposite &) = delete;
    StateComposite(StateComposite &&) = delete;
    StateComposite &operator=(const StateComposite &) = delete;
    StateComposite &operator=(StateComposite &&) = delete;
    void reset() {}
};
