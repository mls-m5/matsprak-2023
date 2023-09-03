#include "tokenizer.h"
#include "token.h"
#include "tokentreelookup.h"
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

    auto finishToken = [&](/*char c*/) {
        if (current.empty()) {
            return;
        }

        auto type = t.get();
        if (type == Invalid) {
            type = Word;
            if (firstType == Numeric) {
                // TODO: Fix when names ends with digits
                type = NumericLiteral;
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

        if (charType == Operator && type != Invalid) {
            finishToken();
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

    finishToken();
}

} // anonymous namespace

struct TokenizedFile {
    std::shared_ptr<File> file;
    std::vector<Token> tokens;
};

TokenIterator tokenize(const std::shared_ptr<File> &file) {
    auto tokenizedFile = std::make_shared<TokenizedFile>(file);

    for (const auto &line : file->lines) {
        tokenizeLine(line, tokenizedFile->tokens, file);
    }

    return TokenIterator(tokenizedFile);
}

TokenIterator::TokenIterator(std::shared_ptr<TokenizedFile> file)
    : _file(file)
    , _current(file->tokens.begin())
    , _end(file->tokens.end()) {}
