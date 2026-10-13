#pragma once

#include <optional>
#include <string_view>

namespace mellos::example
{
class Token
{
public:
    [[nodiscard]] static constexpr std::optional<Token> Parse(std::string_view Text)
    {
        if (Text.empty())
            return std::nullopt;
        return Token(Text);
    }

    [[nodiscard]] constexpr bool Matches(std::string_view Presented) const { return Presented == Value; }

private:
    constexpr explicit Token(std::string_view InValue) : Value(InValue) {}

    std::string_view Value;
};
} // namespace mellos::example
