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
        if (doesMatch(type, t)) {
            return true;
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
        std::vector<Matcher> ignoredParents;
        TokenType type = Uncategorized;

        Node(const Node &) = delete;
        Node(Node &&) = delete;
        Node &operator=(const Node &) = delete;
        Node &operator=(Node &&) = delete;

        Node(Node *parent, Matcher matcher)
            : parent{parent}
            , matcher{matcher} {}

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

        bool doesMatchIgnored(TokenType type) const {
            for (auto p : ignoredParents) {
                if (p(type)) {
                    return true;
                }
            }
            return false;
        }

        Node *find(TokenType t, TokenType parent) {
            for (auto &c : children) {
                if (c.matcher(t)) {
                    if (c.doesMatchIgnored(parent)) {
                        return nullptr;
                    }
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
            children.emplace_back(this, t);
            return children.back();
        }

        friend AstTreeLookup;

        Node &add(TokenType type,
                  std::vector<Matcher> key,
                  std::vector<Matcher> ignoredParents) {
            if (key.empty()) {
                this->type = type;
                this->ignoredParents = std::move(ignoredParents);
                return *this;
            }
            findOrCreate(key.front())
                .add(type,
                     std::vector(key.begin() + 1, key.end()),
                     ignoredParents);

            return *this;
        }
    };

    void add(TokenType resT,
             std::vector<Matcher> arr,
             std::vector<Matcher> ignoredParents = {}) {
        root.add(resT, arr, std::move(ignoredParents));
    }

    AstTreeLookup() {}

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

    AstTreeLookup::Node *push(TokenType t, TokenType parent) {
        if (auto f = current->find(t, parent)) {
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

    std::list<AstTreeLookup> lookups;

    StateComposite();

    StateComposite(const StateComposite &) = delete;
    StateComposite(StateComposite &&) = delete;
    StateComposite &operator=(const StateComposite &) = delete;
    StateComposite &operator=(StateComposite &&) = delete;
    ~StateComposite() = default;
    void reset() {}
};
