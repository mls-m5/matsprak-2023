#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

struct File {
    std::string content;
    std::vector<std::string_view> lines;

    std::filesystem::path path;

    File(std::filesystem::path path);

    void splitLines();

    File(std::istream &in, std::filesystem::path path) {
        load(in, path);
    }

    explicit File(std::string str, std::filesystem::path path);

    void load(std::istream &stream, std::filesystem::path path);

    // Pretend to load from file
    static std::shared_ptr<File> from_string(std::string str,
                                             std::filesystem::path path);
};
