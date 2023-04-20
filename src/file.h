#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

struct File {
    std::vector<std::string> lines;
    std::filesystem::path path;

    File(std::filesystem::path path);

    File(std::istream &in, std::filesystem::path path) {
        load(in, path);
    }

    void load(std::istream &stream, std::filesystem::path path);

    // Pretend to load from file
    static std::shared_ptr<File> fromString(std::string_view str,
                                            std::filesystem::path path);
};
