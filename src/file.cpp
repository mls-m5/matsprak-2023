#include "file.h"
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

File::File(std::filesystem::path path) {
    auto file = std::ifstream{path};

    load(file, path);
}

void File::load(std::istream &file, std::filesystem::path path) {
    this->path = path;
    for (std::string line; std::getline(file, line);) {
        lines.push_back(line);
    }
}

std::shared_ptr<File> File::fromString(std::string_view str,
                                       std::filesystem::path path) {
    auto ss = std::istringstream{std::string{str}};

    return std::make_shared<File>(ss, path);
}
