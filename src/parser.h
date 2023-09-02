#pragma once

#include <istream>
#include <memory>
#include <string_view>

struct AstModule;
struct File;

void parse(AstModule &, std::shared_ptr<File> file);
