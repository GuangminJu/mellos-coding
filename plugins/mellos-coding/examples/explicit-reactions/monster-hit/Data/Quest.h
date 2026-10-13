#pragma once

namespace mellos::example
{
class Kills
{
public:
    constexpr explicit Kills(unsigned InCount) : Count(InCount) {}

    [[nodiscard]] constexpr Kills Next() const { return Kills(Count + 1); }
    [[nodiscard]] constexpr bool Reached(Kills Target) const { return Count >= Target.Count; }
    [[nodiscard]] constexpr unsigned GetCount() const { return Count; }

private:
    unsigned Count;
};

struct Quest
{
    Kills Done;
    Kills Required;
};
} // namespace mellos::example
