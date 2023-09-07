#pragma once

#include "token.h"
#include "tokentype.h"
#include <exception>
#include <map>
#include <optional>

/// TODO: Optimize when the basic idea is fixed
/// For example save between runs
struct TokenTreeLookup {
    using T = TokenType;

    struct Node {
        TokenType type = T::Invalid;
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

    // TokenTreeLookup constructor
    TokenTreeLookup() {
        // Keywords
        root.add("let", T::Let);
        root.add("fn", T::Fn);
        root.add("template", T::Template);
        root.add("type", T::Type);
        root.add("struct", T::Struct);

        // Single-character Operators
        root.add("+", T::Plus);
        root.add("-", T::Minus);
        root.add("*", T::Multiply);
        root.add("/", T::Divide);
        root.add("%", T::Modulo);

        root.add("&", T::BinaryAnd);
        root.add("|", T::BinaryOr);
        root.add("&&", T::And);
        root.add("||", T::Or);
        root.add("^", T::Xor);
        root.add("!", T::Not);
        root.add("~", T::Tilde);
        root.add("<", T::Less);
        root.add(">", T::Greater);
        root.add("=", T::Equals);

        // Multi-character Operators
        root.add("++", T::PlusPlus);
        root.add("--", T::MinusMinus);
        root.add("+=", T::PlusEqual);
        root.add("-=", T::MinusEqual);
        root.add("*=", T::MulEqual);
        root.add("/=", T::DivEqual);
        root.add("%=", T::ModEqual);
        root.add("&=", T::AndEqual);
        root.add("|=", T::OrEqual);
        root.add("^=", T::XorEqual);
        root.add(">>=", T::RightShiftEqual);
        root.add("<<=", T::LeftShiftEqual);
        root.add("==", T::EqualEqual);
        root.add("!=", T::NotEqual);
        root.add("<=", T::LessOrEqual);
        root.add(">=", T::GreaterOrEqual);
        root.add("&&", T::LogicalAnd);
        root.add("||", T::LogicalOr);
        root.add("<<", T::LeftShift);
        root.add(">>", T::RightShift);
        root.add("->", T::Arrow);
        root.add("->*", T::ArrowStar);
        root.add("::", T::ScopeResolution);
        root.add(".*", T::DotStar);

        // Punctuation and other symbols
        root.add("(", T::ParenthesesBegin);
        root.add(")", T::ParenthesesEnd);
        root.add("{", T::BraceBegin);
        root.add("}", T::BraceEnd);
        root.add(",", T::Comma);
        root.add(";", T::Semicolon);
        root.add(":", T::Colon);
        root.add(".", T::Period);
    }

    TokenTreeLookup(const TokenTreeLookup &) = delete;
    TokenTreeLookup(TokenTreeLookup &&) = delete;
    TokenTreeLookup &operator=(const TokenTreeLookup &) = delete;
    TokenTreeLookup &operator=(TokenTreeLookup &&) = delete;

    ~TokenTreeLookup() = default;

    TokenType push(char c) {
        if (auto f = current->find(c)) {
            current = f;
            return T::Invalid;
        }

        return std::exchange(current, &root)->type;
    }

    /// Return value without pushing another character, for example on end
    /// of word
    TokenType get() {
        return std::exchange(current, &root)->type;
    }

    /// Check the current type without consuming it
    std::optional<TokenType> peek(char c) {
        if (auto f = current->find(c)) {
            return f->type;
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
