#pragma once

#include <optional>
#include <string_view>

namespace mellos::example
{
class Port
{
public:
    [[nodiscard]] static constexpr std::optional<Port> Parse(std::string_view Text)
    {
        if (Text.empty())
            return std::nullopt;

        unsigned Number = 0;
        for (const char Digit : Text)
        {
            if (Digit < '0' || Digit > '9')
                return std::nullopt;
            Number = Number * 10 + static_cast<unsigned>(Digit - '0');
            if (Number > Highest)
                return std::nullopt;
        }
        if (Number < Lowest)
            return std::nullopt;
        return Port(Number);
    }

    [[nodiscard]] constexpr unsigned Get() const { return Number; }

private:
    static constexpr unsigned Lowest = 1;
    static constexpr unsigned Highest = 65535;

    constexpr explicit Port(unsigned InNumber) : Number(InNumber) {}

    unsigned Number;
};
} // namespace mellos::example
