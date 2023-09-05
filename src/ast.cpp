#include "ast.h"

void Ast::print(std::ostream &stream, int numIndent) {
    auto indent = [&] { stream << std::setw(numIndent * 4) << " "; };

    indent();
    stream << toString(_type);
    if (_token) {
        stream << "   " << _token->text();
    }
    if (openAst) {
        stream << " " << toString(openAst->type());
    }
    if (closeAst) {
        stream << " " << toString(closeAst->type());
    }

    stream << "\n";

    for (auto &c : _children) {
        c->print(stream, numIndent + 1);
    }
}

std::ostream &operator<<(std::ostream &stream, Ast &ast) {
    ast.print(stream, 0);
    return stream;
}
