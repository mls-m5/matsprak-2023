#include "file.h"
#include "module.h"

int main(int argc, char *argv[]) {
    auto file = File{"demo/test1.msp"};

    for (auto line : file.lines) {
        std::cout << line << "\n";
    }

    return 0;
}
