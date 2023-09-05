#include "token.h"
#include <iomanip>

void Token::print(std::ostream &stream, int indent) {
    // Print all tokens at the same level
    for (auto n = this; n; n = n->_next) {
        stream << std::setw(4 * indent) << " ";
        stream << std::setw(10) << std::left << n->_text;
        stream << toString(n->_type) << "\n";

        if (n->_children) {
            n->_children->print(stream, indent + 1);
        }
    }

    //    for (auto n = _next; n; n = n->_next) {
    //        n->print(stream, indent);
    //    }
}
