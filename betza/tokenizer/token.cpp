#include "token.hpp"

#include <stdexcept>

using namespace betza;

char Token::ch() const {
    return text.empty() ? '\0' : text[0];
}

int Token::number() const {
    if (type != TokenType::NUMBER) throw std::logic_error("Token is not a number");
    return text.empty() ? -1 : atoi(text.data());
}

bool Token::is(const TokenType t) const { return type == t; }

bool Token::is(const TokenType t, const char c) const { return is(t) && ch() == c; }
