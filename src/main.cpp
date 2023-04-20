#include "file.h"
#include "module.h"
#include "tokenizer.h"
#include <memory>

int main(int argc, char *argv[]) {
    auto file = std::make_shared<File>("demo/test1.msp");

    TokenIterator it = tokenize(file);

    while (it.current() != nullptr) {
        // Process the current token
        std::cout << "Current: " << it.current()->text() << " ";
        if (it.next()) {
            std::cout << "Next: " << it.next()->text() << std::endl;
        }
        ++it;
    }

    return 0;
}
