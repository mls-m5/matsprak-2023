#include <stdexcept>
#include <string_view>

// Define the X-Macro list
#define AST_TYPES(X)                                                           \
    X(Uncategorized)                                                           \
    X(KeyWord)                                                                 \
    X(UnaryOperator)                                                           \
    X(BasicOperator)                                                           \
    X(BinaryOperator)                                                          \
    X(RelationalOperator)                                                      \
    X(LogicalOperator)                                                         \
    X(BitwiseShiftOperator)                                                    \
    X(MemberAccessOperator)                                                    \
    X(ScopeOperator)                                                           \
    X(PointerToMemberOperator)                                                 \
    X(Punctuation)                                                             \
    X(Let)                                                                     \
    X(LetStatement)                                                            \
    X(BeginGroup)                                                              \
    X(EndGroup)                                                                \
    X(AssignmentExpression)                                                    \
    X(Expression)

// Generate the enum class
enum class Ast {
#define ENUM_ITEM(name) name,
    AST_TYPES(ENUM_ITEM)
#undef ENUM_ITEM
};

// Generate the toString function
constexpr std::string_view toString(Ast t) {
    switch (t) {
#define CASE_ITEM(name)                                                        \
    case Ast::name:                                                            \
        return #name;
        AST_TYPES(CASE_ITEM)
#undef CASE_ITEM
    default:
        throw std::runtime_error{"Invalid ast type"};
    }
}
