#include "astgrouping.h"
#include "asttreelookup.h"

void groupParentheses(Ast &ast) {
    groupParentheses(ast, 1);
}

void groupParentheses(Ast &ast, ptrdiff_t a) {
    for (size_t i = a; i < ast.children().size(); ++i) {
        auto child = ast.children().at(i).get();
        if (child->type() == ParenthesesBegin) {
            groupParentheses(ast, i + 1);

            for (size_t j = i + 1; j < ast.children().size(); ++j) {
                auto child2 = ast.children().at(j).get();
                if (child2->type() == ParenthesesEnd) {
                    ast.group(
                        ParenGroup, ast.begin() + i, ast.begin() + j + 1, true);
                    i = i + 1;
                    break;
                }
            }
        }
    }
}

void groupAst(Ast &ast, AstTreeLookup &t) {
    //    auto t = AstTreeLookup{};
    auto state = AstTreeState{t};

    for (size_t i = 2; i < ast.children().size(); ++i) {
        state.reset();
        auto index1 = i - 2;

        TokenType hypothesis = Invalid;
        auto resIndex2 = 0;

        for (size_t index2 = index1; index2 < ast.children().size(); ++index2) {
            auto &currentChild = *ast.children().at(index2);
            auto res = state.push(currentChild.type());
            if (!res) {
                break;
            }
            // Prioritize longer matches
            if (res->type == Uncategorized) {
                continue;
            }
            if (res->type == Invalid) {
                continue;
            }
            hypothesis = res->type;
            resIndex2 = index2;
        }

        if (hypothesis != Invalid) {
            if (resIndex2 - index1 + 1 >= ast.children().size()) {
                continue;
            }
            ast.group(
                hypothesis, ast.begin() + index1, ast.begin() + resIndex2 + 1);
        }
    }

    for (auto &c : ast.children()) {
        groupAst(*c);
    }
}

void groupAst(Ast &ast) {
    StateComposite composite;

    for (auto &lookup : composite.lookups) {
        groupAst(ast, lookup);
    }
}
