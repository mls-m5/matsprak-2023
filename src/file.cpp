#include "file.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

File::File(std::filesystem::path path) {
    auto file = std::ifstream{path};

    load(file, path);
}

void File::splitLines() {
    if (content.empty()) {
        return;
    }

    auto numLines = std::count(content.begin(), content.end(), '\n');

    lines.reserve(numLines + 1);

    size_t p = 0, n = 0;
    for (; (n = content.find('\n', p + 1)), n != std::string::npos; p = n) {
        lines.push_back({content.data() + p, n - p});
    }

    lines.push_back({content.data() + p, std::min(n - p, content.size() - p)});
}

File::File(std::string str, std::filesystem::path path)
    : content{std::move(str)}
    , path{path} {
    splitLines();
}

void File::load(std::istream &file, std::filesystem::path path) {
    this->path = path;
    for (std::string line; std::getline(file, line);) {
        content += (line + '\n');
    }
    splitLines();
}

std::shared_ptr<File> File::from_string(std::string str,
                                        std::filesystem::path path) {
    return std::make_shared<File>(std::move(str), path);
}
