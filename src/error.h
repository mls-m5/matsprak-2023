#pragma once

#include "ast.h"
#include "token.h"
#include "tokentype.h"
#include <stdexcept>
#include <string>
#include <string_view>

struct Error : public std::runtime_error {
    // Todo: Handle location
    Error(const Token *token, std::string_view text)
        : std::runtime_error{(token ? std::string{token->text()} : "") + " " +
                             std::string{text}} {}
};

void raise(const Token &token, std::string_view text) {
    throw Error(&token, text);
}

void raise(const Ast &ast, std::string_view text) {
    throw Error(&ast.token(), text);
}

void assertToken(const Token &token, TokenType type, std::string_view text) {
    if (!doesMatch(token.type(), type)) {
        raise(token, text);
    }
}
