#pragma once

#include "token.h"
#include "tokenizer.h"
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

    private:
        void add(TokenType type, std::vector<Matcher> key) {
            if (key.empty()) {
                this->type = type;
                return;
            }
            findOrCreate(key.front())
                .add(type, std::vector(key.begin() + 1, key.end()));
        }
    };

    AstTreeLookup() {
        using VecT = std::vector<Matcher>;
        add(LetStatement, VecT{Let, Word, Equals, NumericLiteral, Semicolon});

        /// TODO: Create separate result type?
        add(LetStatement, VecT{Let, Word, Colon, Expression});
        add(AssignmentExpression,
            VecT{Expression, {Equals, BinaryOperator}, Expression, Semicolon});
    }

    Node root{{}, {Uncategorized}};

private:
    void add(TokenType resT, std::vector<Matcher> arr) {
        root.add(resT, arr);
    }
};

class AstTreeState {
public:
    AstTreeLookup::Node *root = nullptr;
    AstTreeLookup::Node *current = nullptr;

    AstTreeState(AstTreeLookup &l)
        : root{&l.root}
        , current{&l.root} {}

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
};

inline void group(AstTreeState &state, std::shared_ptr<TokenizedFile> tokens) {
    for (auto it = TokenIterator{tokens}; it.current(); ++it) {
        if (auto t = state.push(it.current()->type())) {
            it.current()->type(t->type);
        }
    }
}
