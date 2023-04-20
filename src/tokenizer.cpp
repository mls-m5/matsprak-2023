#include "tokenizer.h"
#include <memory>
#include <regex>

namespace {

TokenType getTokenType(const std::string_view &text) {
    if (text == "(")
        return ParenthesesBegin;
    if (text == ")")
        return ParenthesesEnd;
    if (text == "{")
        return BraceBegin;
    if (text == "}")
        return BraceEnd;
    if (text == ",")
        return Comma;
    if (text == ";")
        return Semicolon;
    if (text == "=" || text == "+" || text == "-" || text == "*" ||
        text == "/" || text == "?")
        return BinaryOperator;

    if (std::regex_match(text.begin(), text.end(), std::regex(R"(\d+)"))) {
        return NumericLiteral;
    }

    return Word;
}

void tokenizeLine(const std::string &line,
                  std::vector<Token> &tokens,
                  const std::shared_ptr<File> &file) {
    static const std::regex token_regex(
        R"((\(|\)|\{|\}|,|;|=|\+|-|\*|/|\?|\d+|[\w<>]+))");

    std::sregex_iterator it(line.begin(), line.end(), token_regex);
    std::sregex_iterator end;

    while (it != end) {
        Token token;
        token._text = it->str();
        token._type = getTokenType(token._text);

        tokens.push_back(token);

        ++it;
    }
}

} // anonymous namespace

struct TokenizedFile {
    std::vector<Token> tokens;
};

TokenIterator tokenize(const std::shared_ptr<File> &file) {
    auto tokenizedFile = std::make_shared<TokenizedFile>();

    for (const auto &line : file->lines) {
        tokenizeLine(line, tokenizedFile->tokens, file);
    }

    return TokenIterator(tokenizedFile);
}

TokenIterator::TokenIterator(std::shared_ptr<TokenizedFile> file)
    : _file(file)
    , _current(file->tokens.begin())
    , _end(file->tokens.end()) {}
