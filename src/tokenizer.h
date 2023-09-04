#pragma once

#include "file.h"
#include "token.h"

struct TokenizedFile {
    std::shared_ptr<File> file;
    std::vector<Token> tokens;
};

struct TokenIterator {
    std::shared_ptr<TokenizedFile> _file;
    std::vector<Token>::iterator _current;
    std::vector<Token>::iterator _end;

    TokenIterator(std::shared_ptr<TokenizedFile> file);

    TokenIterator(const TokenIterator &) = default;
    TokenIterator(TokenIterator &&) = default;

    const Token &operator()() {
        return *current();
    }

    Token *current() {
        if (_current == _end) {
            return nullptr;
        }
        return &(*_current);
    }

    Token *next() {
        if (_current == _end || std::next(_current) == _end) {
            return nullptr;
        }
        return &(*std::next(_current));
    }

    TokenIterator &operator++() {
        if (_current != _end) {
            ++_current;
        }
        return *this;
    }

    // Add more functions if needed
};

std::shared_ptr<TokenizedFile> tokenize(const std::shared_ptr<File> &file);
