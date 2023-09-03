#pragma once

#include "ast.h"
#include "token.h"
#include <array>
#include <cstddef>
#include <map>
#include <ranges>
#include <span>
#include <stdexcept>
#include <string_view>
#include <variant>
#include <vector>

using DoubleTypeT = std::variant<nullptr_t, Ast, TokenType>;

constexpr std::string_view toString(DoubleTypeT t) {
    switch (t.index()) {
    case 1:
        return toString(std::get<1>(t));
    case 2:
        return toString(std::get<2>(t));
    }
    throw std::runtime_error{"unsupported to string"};
}

struct Matcher {
    Matcher(DoubleTypeT t)
        : type{t} {}

    Matcher(Ast t)
        : type{t} {}
    Matcher(TokenType t)
        : type{t} {}

    bool operator()(DoubleTypeT t) const {
        return t == type;
    }

    DoubleTypeT type = Ast::Uncategorized;
};

class AstTreeLookup {
public:
    struct Node {
        DoubleTypeT type = Ast::Uncategorized;

        bool hasType() const {
            return type != DoubleTypeT{Ast::Uncategorized};
        }

        std::vector<std::pair<Matcher, Node>> children;

        const Node *find(DoubleTypeT t) const {
            for (auto &c : children) {
                if (c.first(t)) {
                    return &c.second;
                }
            }
            return nullptr;
        }

        Node *find(DoubleTypeT t) {
            for (auto &c : children) {
                if (c.first(t)) {
                    return &c.second;
                }
            }
            return nullptr;
        }

        Node &findOrCreate(DoubleTypeT t) {
            if (auto f = find(t)) {
                return *f;
            }
            children.push_back({Matcher{t}, Node{}});
            return children.back().second;
        }

        friend AstTreeLookup;

    private:
        void add(DoubleTypeT type, std::vector<DoubleTypeT> key) {
            if (key.empty()) {
                this->type = type;
                return;
            }
            findOrCreate(key.front())
                .add(type, std::vector(key.begin() + 1, key.end()));
        }
    };

    AstTreeLookup() {
        using VecT = std::vector<DoubleTypeT>;
        add(Ast::LetStatement, VecT{Let, Word, Semicolon});
    }

    Node root;

private:
    void add(Ast resT, std::vector<DoubleTypeT> arr) {
        root.add(resT, arr);
    }
};

class AstTreeState {
public:
    //    const AstTreeLookup *lookup = nullptr;
    AstTreeLookup::Node *root = nullptr;
    AstTreeLookup::Node *current = nullptr;

    AstTreeState(AstTreeLookup &l)
        : root{&l.root}
        , current{&l.root} {}

    AstTreeLookup::Node *push(DoubleTypeT t) {
        if (auto f = current->find(t)) {
            current = f;
            if (f->hasType()) {
                return f;
            }
        }

        return nullptr;
    }
};
