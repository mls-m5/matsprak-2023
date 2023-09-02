#pragma once

#include "token.h"
#include <exception>
#include <map>
#include <optional>

/// TODO: Optimize when the basic idea is fixed
/// For example save between runs
struct TokenTreeLookup {
    struct Node {
        TokenType type = Invalid;
        std::map<char, Node> children; // Should probably be a vector...

    private:
        void add(std::string_view key, TokenType type) {
            if (key.empty()) {
                this->type = type;
                return;
            }
            children[key.front()].add(key.substr(1), type);
        }

        Node *find(char c) {
            if (auto f = children.find(c); f != children.end()) {
                return &f->second;
            }
            return nullptr;
        }

        friend TokenTreeLookup;
    };

    TokenTreeLookup() {
        root.add("let", Let);
        root.add("fn", Fn);
        //        root.add("template", Template);
        //        root.add("type", Type);
    }

    TokenTreeLookup(const TokenTreeLookup &) = delete;
    TokenTreeLookup(TokenTreeLookup &&) = delete;
    TokenTreeLookup &operator=(const TokenTreeLookup &) = delete;
    TokenTreeLookup &operator=(TokenTreeLookup &&) = delete;

    ~TokenTreeLookup() = default;

    TokenType push(char c) {
        if (auto f = current->find(c)) {
            current = f;
            return Invalid;
        }

        return std::exchange(current, &root)->type;
    }

    /// Return value without pushing another character, for example on end of
    /// word
    TokenType get() {
        return std::exchange(current, &root)->type;
    }

    /// Check the current type without consuming it
    std::optional<TokenType> peek(char c) {
        if (auto f = current->find(c)) {
            if (f->type != Invalid) {
                return f->type;
            }
        }
        return std::nullopt;
    }

    void reset() {
        current = &root;
    }

private:
    Node root;
    Node *current = &root;
};
