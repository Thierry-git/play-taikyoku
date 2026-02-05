#pragma once

#include <string_view>

namespace betza {

enum class TokenType {
    UPPER,
    LOWER,
    NUMBER,
    HYPHEN,
    PLUS,
    LPAREN,
    RPAREN,
    COMMA,
    END,
    ERROR
};

struct Token {
    std::string_view text;
    TokenType type;
    int position; // for error reporting

    char ch() const;
    int number() const; // throws std::logic_error if not a number

    bool is(const TokenType t) const;
    bool is(const TokenType t, const char c) const;
};

} // namespace betza
