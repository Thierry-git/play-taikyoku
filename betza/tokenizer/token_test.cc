#include <gtest/gtest.h>

#include "token.hh"

TEST(Token, chReportsNullTermintorIfNoData) {
    const betza::Token t = { "", betza::TokenType::COMMA, 0 };
    EXPECT_EQ(t.ch(), '\0');
}

TEST(Token, chReportsFirstCharIfData) {
    const betza::Token t = { "AB", betza::TokenType::UPPER, 1 };
    EXPECT_EQ(t.ch(), 'A');
}

TEST(Token, numberThrowsIfNotNumberType) {
    const betza::Token t = { "12", betza::TokenType::END, 2 };
    EXPECT_THROW(t.number(), std::logic_error);
}

TEST(Token, numberCanReportSingleDigitAsInteger) {
    constexpr int EXPECTED = 4;
    const betza::Token t = { "4", betza::TokenType::NUMBER, 3 };
    EXPECT_EQ(t.number(), EXPECTED);
}

TEST(Token, numberCanReportMultiDigitAsInteger) {
    constexpr int EXPECTED = 179;
    const betza::Token t = { "179", betza::TokenType::NUMBER, 4 };
    EXPECT_EQ(t.number(), EXPECTED);
}

class TokenIsTest : public testing::Test {
protected:
    TokenIsTest() :
    t1_({ "", betza::TokenType::LPAREN, 5 }), t2_({ "t", betza::TokenType::LOWER, 6 }) { }
    ~TokenIsTest() override = default;

    const betza::Token t1_;
    const betza::Token t2_;
};

TEST_F(TokenIsTest, reportsFalseIfDifferent) {
    EXPECT_FALSE(t1_.is(betza::TokenType::END));
    EXPECT_FALSE(t1_.is(betza::TokenType::LPAREN, 'L'));
    EXPECT_FALSE(t2_.is(betza::TokenType::ERROR, 'x'));
    EXPECT_FALSE(t2_.is(betza::TokenType::LOWER, 'x'));
    EXPECT_FALSE(t2_.is(betza::TokenType::UPPER, 't'));
}

TEST_F(TokenIsTest, reportsTrueIfMatchesCondition) {
    EXPECT_TRUE(t1_.is(betza::TokenType::LPAREN));
    EXPECT_TRUE(t1_.is(betza::TokenType::LPAREN, '\0'));
    EXPECT_TRUE(t2_.is(betza::TokenType::LOWER));
    EXPECT_TRUE(t2_.is(betza::TokenType::LOWER, 't'));
}
