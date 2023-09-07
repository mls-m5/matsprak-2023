#include "tokenizer.h"
#include "token.h"
#include "tokentreelookup.h"
#include "tokentype.h"
#include <memory>
#include <regex>
#include <stdexcept>
#include <string_view>

namespace {

void tokenizeLine(std::string_view line,
                  std::vector<Token> &tokens,
                  const std::shared_ptr<File> &file) {

    auto t = TokenTreeLookup{};

    auto current = std::string_view{};

    enum CurrentType {
        Alphabetic,
        Numeric,
        Operator,
        Space,
        Semicolon,
    };

    auto getType = [](char c) {
        switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return Numeric;
        case '+':
        case '-':
        case '*':
        case '/':
        case '<':
        case '>':
        case '=':
        case '!':
        case '&':
        case '|':
        case '^':
        case '%':
        case '~':
        case '?':
        case ':':
        case '.':
        case ',':
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
            return Operator;
        case ' ':
        case '\n':
        case '\t':
        case '\r':
            return Space;

        case ';':
            return Semicolon;
        default:
            return Alphabetic;
        }
    };

    auto prevType = Space;
    auto charType = Space;
    auto firstType = Space;

    auto finishToken = [&](TokenType foundType = TokenType::Invalid) {
        if (current.empty()) {
            return;
        }

        auto type = (foundType == TokenType::Invalid) ? t.get() : foundType;
        //        if (!foundType) {
        //        auto type = t.get();
        //        }
        if (type == TokenType::Invalid) {
            type = TokenType::Word;
            if (firstType == Numeric) {
                // TODO: Fix when names ends with digits
                type = TokenType::NumericLiteral;
            }
        }
        tokens.emplace_back(current, type);
        current = {};
        t.reset();
        firstType = Space;
    };

    for (size_t i = 0; i < line.size(); ++i) {
        auto c = line.at(i);
        auto charType = getType(c);

        if (firstType == Space) {
            firstType = charType;
        }

        if (charType != prevType &&
            !(charType == Numeric && prevType == Alphabetic)) {
            finishToken();
            prevType = charType;
        }

        auto type = t.push(c);

        if (charType == Operator && type != TokenType::Invalid) {
            finishToken(type);
            t.push(c); // Since push lags behind a character
        }

        if (charType != Space) {
            if (current.empty()) {
                current = std::string_view{line}.substr(i, 1);
            }
            else {
                current = std::string_view{current.data(), current.size() + 1};
            }
        }
    }

    if (!current.empty()) {
        t.reset();
        for (auto c : current) {
            t.push(c);
        }
        finishToken(t.get());
    }
}

} // anonymous namespace

std::shared_ptr<TokenizedFile> tokenize(const std::shared_ptr<File> &file) {
    auto tokenizedFile = std::make_shared<TokenizedFile>(file);

    for (const auto &line : file->lines) {
        tokenizeLine(line, tokenizedFile->tokens, file);
    }

    auto &tokens = tokenizedFile->tokens;
    for (int i = 1; i < tokens.size(); ++i) {
        tokens.at(i - 1).next(&tokens.at(i));
    }

    tokenizedFile->root.children(&tokens.front());

    return tokenizedFile;
}

TokenIterator::TokenIterator(std::shared_ptr<TokenizedFile> file)
    : _file(file)
    , _current(file->tokens.begin())
    , _end(file->tokens.end()) {}
