#pragma once

#include "ast.h"
#include <list>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct Struct {
    std::string name;
};

struct Type {
    std::unique_ptr<Struct> customType;
};

struct FunctionArguments {
    Type type;
    std::string name;
};

struct Function {
    std::vector<Type> argument;
};

struct Module {
    std::string_view name;

    std::unordered_map<std::string, Function> functions;
    std::unordered_map<std::string, Function> types;
};

struct CodeGenerator {
    Module module;

    struct Scope {};

    void generateRoot(Ast &ast);

    void generateGlobal(Ast &ast);
};
