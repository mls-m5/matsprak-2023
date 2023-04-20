#pragma once

#include <istream>
#include <memory>
#include <string_view>

struct Module;
struct File;

void parse(Module &, std::istream &in);
