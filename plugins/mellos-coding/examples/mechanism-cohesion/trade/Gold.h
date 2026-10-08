#pragma once

#include <optional>

namespace mellos::example
{
class Gold
{
public:
    constexpr explicit Gold(unsigned InAmount) : Amount(InAmount) {}

    [[nodiscard]] constexpr std::optional<Gold> Spend(Gold Price) const
    {
        if (Amount < Price.Amount)
            return std::nullopt;
        return Gold(Amount - Price.Amount);
    }

    [[nodiscard]] constexpr Gold operator+(Gold Income) const { return Gold(Amount + Income.Amount); }
    [[nodiscard]] constexpr Gold operator/(unsigned Divisor) const { return Gold(Amount / Divisor); }
    [[nodiscard]] constexpr unsigned GetAmount() const { return Amount; }

private:
    unsigned Amount;
};
} // namespace mellos::example
