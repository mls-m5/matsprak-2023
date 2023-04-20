#include "file.h"
#include <fstream>
#include <string>

File::File(std::filesystem::path path) {
    auto file = std::ifstream{path};

    for (std::string line; std::getline(file, line);) {
        lines.push_back(line);
    }
}
