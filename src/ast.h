#pragma once

#include "token.h"
#include "tokenizer.h"
#include <iosfwd>
#include <memory>
#include <vector>

struct Ast {
    using ContainerT = std::vector<std::unique_ptr<Ast>>;
    using iterator = ContainerT::iterator;
    using const_iterator = ContainerT::const_iterator;

    Ast(const Token &token)
        : _token{&token}
        , _type{token.type()} {}

    Ast(TokenType type)
        : _type{type} {}

    Ast(const TokenizedFile &file) {
        for (auto &token : file.tokens) {
            _children.push_back(std::make_unique<Ast>(token));
        }
    }

    const Token &token() const {
        return *_token;
    }

    void group(TokenType type,
               iterator begin,
               iterator end,
               bool shouldStripSurrounding = false) {
        auto child = std::make_unique<Ast>(type);

        if (shouldStripSurrounding) {
            openAst = std::move(*begin);
            auto a = begin + 1;
            auto b = end - 1;
            closeAst = std::move(*b);

            child->_children.reserve(std::distance(begin, end) - 2);
            for (auto it = a; it != b; ++it) {
                child->_children.push_back(std::move(*it));
            }
        }
        else {
            child->_children.reserve(std::distance(begin, end));
            for (auto it = begin; it != end; ++it) {
                child->_children.push_back(std::move(*it));
            }
        }

        _children.erase(begin + 1, end);
        *begin = std::move(child);
    }

    auto begin() {
        return _children.begin();
    }

    auto end() {
        return _children.end();
    }

    auto cbegin() const {
        return _children.cbegin();
    }

    auto cend() const {
        return _children.cend();
    }

    void print(std::ostream &stream, int indent);

    ContainerT &children() {
        return _children;
    }

    TokenType type() {
        return _type;
    }

private:
    const Token *_token = nullptr;
    TokenType _type = Invalid;

    ContainerT _children;
    std::unique_ptr<Ast> openAst;
    std::unique_ptr<Ast> closeAst;
};

std::ostream &operator<<(std::ostream &stream, Ast &ast);
