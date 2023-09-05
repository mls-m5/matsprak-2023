#pragma once

#include "file.h"
#include "token.h"
#include <iosfwd>

struct TokenizedFile {
    TokenizedFile(const TokenizedFile &) = delete;
    TokenizedFile(TokenizedFile &&) = delete;
    TokenizedFile &operator=(const TokenizedFile &) = delete;
    TokenizedFile &operator=(TokenizedFile &&) = delete;
    TokenizedFile(std::shared_ptr<File> file)
        : file{std::move(file)} {}
    ~TokenizedFile() = default;

    std::shared_ptr<File> file;
    std::vector<Token> tokens;
    Token root = Token{"", RootNode};
};

inline std::ostream &operator<<(std::ostream &stream, TokenizedFile &file) {
    if (file.tokens.empty()) {
        return stream;
    }
    file.root.print(stream);

    return stream;
}

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
