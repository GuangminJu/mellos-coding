#pragma once

#include <optional>

namespace mellos::example
{
// Every value is a valid amount: spending can only yield what remains, never a negative balance.
class Gold
{
public:
    constexpr explicit Gold(unsigned InAmount) : Amount(InAmount) {}

    // What remains after paying Price; empty when this amount cannot cover it.
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
