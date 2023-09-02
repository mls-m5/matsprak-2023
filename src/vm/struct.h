#pragma once

#include <string>
#include <vector>

struct VariableType {
    std::string name;
    struct Struct *userType;
};

struct Struct {
    struct Member {
        std::string name;
        VariableType type;
    };

    std::size_t memorySize = 0;

    std::vector<Member> member;

    void instantiate(char *memory);
};
