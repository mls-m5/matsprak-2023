#pragma once

#include "token.h"
#include "tokenizer.h"
#include "tokentype.h"
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

    Ast(const TokenizedFile &file)
        : _type{TokenType::RootNode} {
        for (auto &token : file.tokens) {
            _children.push_back(std::make_unique<Ast>(token));
        }
    }

    const Token &token() const {
        return *_token;
    }

    Ast &group(TokenType type,
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
        return *begin->get();
    }

    [[nodiscard]] auto begin() {
        return _children.begin();
    }

    [[nodiscard]] auto end() {
        return _children.end();
    }

    [[nodiscard]] auto cbegin() const {
        return _children.cbegin();
    }

    [[nodiscard]] auto cend() const {
        return _children.cend();
    }

    void print(std::ostream &stream, int indent);

    ContainerT &children() {
        return _children;
    }

    [[nodiscard]] TokenType type() {
        return _type;
    }

    void type(TokenType type) {
        _type = type;
    }

    bool isParsed() const {
        return _isParsed;
    }

    void isParsed(bool value) {
        _isParsed = value;
    }

    [[nodiscard]] Ast *find(TokenType type, bool shouldRecurse = false) {
        for (auto &c : children()) {
            if (doesMatch(c->type(), type)) {
                return c.get();
            }
            if (shouldRecurse) {
                if (auto f = c->find(type, true)) {
                    return f;
                }
            }
        }
        return nullptr;
    }

private:
    const Token *_token = nullptr;
    TokenType _type = TokenType::Invalid;

    ContainerT _children;
    std::unique_ptr<Ast> openAst;
    std::unique_ptr<Ast> closeAst;
    bool _isParsed = false;
};

std::ostream &operator<<(std::ostream &stream, Ast &ast);
