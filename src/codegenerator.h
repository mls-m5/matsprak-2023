#pragma once

#include "ast.h"
#include <string_view>

struct Function {};

struct Module {
    std::string_view name;
};

struct CodeGenerator {

    struct Scope {};

    void generate(Ast &ast);
};
