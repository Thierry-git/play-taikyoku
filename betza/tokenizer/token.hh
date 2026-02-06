#pragma once

#include <optional>
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
    unsigned position; // for error reporting

    char ch() const;
    std::optional<unsigned> number() const;

    bool is(const TokenType t) const;
    bool is(const TokenType t, const char c) const;
};

} // namespace betza
