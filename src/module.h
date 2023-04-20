#pragma once

#include "stringmap.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct Module;
struct ModuleNode;

struct StringRef {
    std::string_view get(Module &module);

    int index = 0;
};

struct NodeRef {
    unsigned int ref = 0;
    StringRef text;

    ModuleNode *get(Module &module);
};

// Reference that can be used in memory but never saved
// Saves pointer to the module
struct TempNodeRef {
    Module *module;
    NodeRef ref;
};

struct NodeRange {
    unsigned int begin = 0;
    unsigned int end = 0;
};

enum NodeType {
    Function,
    FunctionCall,
    ImportStatement,
};

struct ModuleNode {
    StringRef text;
    NodeRef ref;
    NodeType type;
    NodeRange range;
};

struct Module {
    Map<std::string, int> words; // Not serialized only used on parsing

    std::vector<std::string> wordContainer;
    std::vector<ModuleNode> nodes;
    std::string name;

    void save(std::ostream &out) {
        // Something like this
        for (const auto &word : wordContainer) {
            auto size = word.size();
            out.write(reinterpret_cast<char *>(&size), sizeof(size));
            out.write(word.data(), word.size());
        }

        {
            auto size = nodes.size();
            out.write(reinterpret_cast<const char *>(&size), sizeof(size));
        }
        for (const auto &node : nodes) {
            out.write(reinterpret_cast<const char *>(&node), sizeof(node));
        }
    }

    void load(std::istream &out) {
        // Same as save but the opposite, and maybe populate some maps
    }

    std::vector<ModuleNode *> findSymbol(std::string_view name) {
        return {};
    }
};

// Keep track of all modules open in the current session
struct ModuleRegister {
    Map<std::string_view, Module> modules{};

    Module *get(std::string_view name) {
        if (auto it = modules.find(name); it != modules.end()) {
            return &it->second;
        }
        return nullptr;
    }
};
