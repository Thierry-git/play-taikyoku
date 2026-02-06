#include "token.hh"

#include <charconv>

using namespace betza;

char Token::ch() const {
    return text.empty() ? '\0' : text[0];
}

std::optional<unsigned> Token::number() const {
    if (type != TokenType::NUMBER || text.empty()) return std::nullopt;
    unsigned value = 0;
    auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), value);
    if (ec != std::errc{} || ptr != text.data() + text.size()) return std::nullopt;
    return value;
}

bool Token::is(const TokenType t) const {
    return type == t;
}

bool Token::is(const TokenType t, const char c) const {
    return is(t) && ch() == c;
}
