#pragma once

#include <filesystem>
#include <string>
#include <vector>

struct File {
    std::vector<std::string> lines;

    File(std::filesystem::path path);
};
