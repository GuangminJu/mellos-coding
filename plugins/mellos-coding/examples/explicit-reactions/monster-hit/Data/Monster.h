#pragma once

namespace mellos::example
{
class HitPoints
{
public:
    constexpr explicit HitPoints(unsigned InAmount) : Amount(InAmount) {}

    [[nodiscard]] constexpr HitPoints Lose(HitPoints Damage) const
    {
        return HitPoints(Amount > Damage.Amount ? Amount - Damage.Amount : 0);
    }

    [[nodiscard]] constexpr bool IsDepleted() const { return Amount == 0; }
    [[nodiscard]] constexpr unsigned GetAmount() const { return Amount; }

private:
    unsigned Amount;
};

struct Monster
{
    HitPoints Health;
};
} // namespace mellos::example
