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

TEST(Token, nonNumberTypeReportsNullopt) {
    const betza::Token t1 = { "12", betza::TokenType::END, 2 };
    const betza::Token t2 = { "af", betza::TokenType::RPAREN, 3 };
    EXPECT_FALSE(t1.number().has_value());
    EXPECT_FALSE(t2.number().has_value());
}

TEST(Token, emptyNumberTypeReportsNullopt) {
    const betza::Token t = { "", betza::TokenType::NUMBER, 4 };
    EXPECT_FALSE(t.number().has_value());
}

TEST(Token, numberTypeWithNonNumericalValueReportsNullopt) {
    const betza::Token t = { "af", betza::TokenType::NUMBER, 5 };
    EXPECT_FALSE(t.number().has_value());
}

TEST(Token, numberTypeWithPartiallyNumericalValueReportsNullopt) {
    const betza::Token t = { "12abc", betza::TokenType::NUMBER, 5 };
    EXPECT_FALSE(t.number().has_value());
}

TEST(Token, numberCanReportSingleDigitAsInteger) {
    constexpr unsigned EXPECTED = 4;
    const betza::Token t = { "4", betza::TokenType::NUMBER, 6 };
    ASSERT_TRUE(t.number().has_value());
    EXPECT_EQ(t.number().value(), EXPECTED);
}

TEST(Token, numberCanReportMultiDigitAsInteger) {
    constexpr unsigned EXPECTED = 179;
    const betza::Token t = { "179", betza::TokenType::NUMBER, 7 };
    ASSERT_TRUE(t.number().has_value());
    EXPECT_EQ(t.number().value(), EXPECTED);
}

class TokenIsTest : public testing::Test {
protected:
    TokenIsTest() :
    t1_({ "", betza::TokenType::LPAREN, 8 }), t2_({ "t", betza::TokenType::LOWER, 9 }) { }
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
