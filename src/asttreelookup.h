#pragma once

#include "ast.h"
#include "token.h"
#include "tokenizer.h"
#include <array>
#include <cstddef>
#include <map>
#include <ranges>
#include <span>
#include <stdexcept>
#include <string_view>
#include <variant>
#include <vector>

struct Matcher {
    Matcher(TokenType t)
        : type{t} {}

    bool operator()(TokenType t) const {
        return t == type;
    }

    TokenType type = Uncategorized;
};

class AstTreeLookup {
public:
    struct Node {
        TokenType type = Uncategorized;

        bool hasType() const {
            return type != TokenType{Uncategorized};
        }

        std::vector<std::pair<Matcher, Node>> children;

        const Node *find(TokenType t) const {
            for (auto &c : children) {
                if (c.first(t)) {
                    return &c.second;
                }
            }
            return nullptr;
        }

        Node *find(TokenType t) {
            for (auto &c : children) {
                if (c.first(t)) {
                    return &c.second;
                }
            }
            return nullptr;
        }

        Node &findOrCreate(TokenType t) {
            if (auto f = find(t)) {
                return *f;
            }
            children.push_back({Matcher{t}, Node{}});
            return children.back().second;
        }

        friend AstTreeLookup;

    private:
        void add(TokenType type, std::vector<TokenType> key) {
            if (key.empty()) {
                this->type = type;
                return;
            }
            findOrCreate(key.front())
                .add(type, std::vector(key.begin() + 1, key.end()));
        }
    };

    AstTreeLookup() {
        using VecT = std::vector<TokenType>;
        add(LetStatement, VecT{Let, Word, Equals, NumericLiteral, Semicolon});
        add(AssignmentExpression,
            VecT{Expression, Equals, Expression, Semicolon});
    }

    Node root;

private:
    void add(TokenType resT, std::vector<TokenType> arr) {
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
            if (f->hasType()) {
                current = root;
                return f;
            }
        }

        return nullptr;
    }
};

void group(AstTreeState &state, std::shared_ptr<TokenizedFile> tokens) {
    for (auto it = TokenIterator{tokens}; it.current(); ++it) {
        if (auto t = state.push(it.current()->type())) {
            it.current()->type(t->type);
        }
    }
}
