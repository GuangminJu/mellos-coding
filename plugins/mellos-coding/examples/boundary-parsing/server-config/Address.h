#pragma once

#include <optional>
#include <string_view>

namespace mellos::example
{
class Address
{
public:
    [[nodiscard]] static constexpr std::optional<Address> Parse(std::string_view Text)
    {
        if (Text.empty())
            return std::nullopt;
        return Address(Text);
    }

    [[nodiscard]] constexpr std::string_view Get() const { return Value; }

private:
    constexpr explicit Address(std::string_view InValue) : Value(InValue) {}

    std::string_view Value;
};
} // namespace mellos::example
