
#include "token.h"
#include "tokentreelookup.h"
#include <gtest/gtest.h>

TEST(TokenTreeLookupTest, basic) {
    {
        auto t = TokenTreeLookup{};

        EXPECT_EQ(t.push('l'), TokenType::Invalid);
        EXPECT_EQ(t.push('e'), TokenType::Invalid);
        EXPECT_EQ(t.push('t'), TokenType::Invalid);
        EXPECT_EQ(t.push(' '), TokenType::Let);
    }

    {
        auto t = TokenTreeLookup{};

        EXPECT_EQ(t.push('l'), TokenType::Invalid);
        EXPECT_EQ(t.push('e'), TokenType::Invalid);
        EXPECT_EQ(t.push('t'), TokenType::Invalid);
        EXPECT_EQ(t.get(), TokenType::Let);
    }

    {
        auto t = TokenTreeLookup{};

        EXPECT_EQ(t.push('f'), TokenType::Invalid);
        EXPECT_EQ(t.push('n'), TokenType::Invalid);
        EXPECT_EQ(t.get(), TokenType::Fn);
    }
}
