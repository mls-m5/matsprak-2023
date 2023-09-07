#include "codegenerator.h"
#include "error.h"
#include "tokentype.h"
#include <stdexcept>

void CodeGenerator::generateRoot(Ast &ast) {
    Scope scope;

    if (ast.type() != TokenType::RootNode) {
        throw std::runtime_error{
            "Trying to generate root code from non rote node"};
    }

    for (auto &c : ast.children()) {
        generateGlobal(*c);
    }
}

void CodeGenerator::generateGlobal(Ast &ast) {
    switch (ast.type()) {
    case TokenType::FunctionDeclaration:
        break;
    default:
        raise(ast, "Unexpected statement " + std::string{toString(ast.type())});
    }
}
