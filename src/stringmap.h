#pragma once

#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

using namespace std::literals;

// From here:
/// https://en.cppreference.com/w/cpp/container/unordered_map/find

struct string_hash {
    using hash_type = std::hash<std::string_view>;
    using is_transparent = void;

    std::size_t operator()(const char *str) const {
        return hash_type{}(str);
    }
    std::size_t operator()(std::string_view str) const {
        return hash_type{}(str);
    }
    std::size_t operator()(std::string const &str) const {
        return hash_type{}(str);
    }
};

template <typename Key, typename Value>
using Map = std::unordered_map<Key, Value, string_hash, std::equal_to<>>;
