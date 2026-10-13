#pragma once

namespace mellos::example
{
class Millis
{
public:
    constexpr explicit Millis(int InCount) : Count(InCount) {}

    [[nodiscard]] constexpr int GetCount() const { return Count; }

private:
    int Count;
};

class Speed
{
public:
    constexpr explicit Speed(int InCmPerSecond) : CmPerSecond(InCmPerSecond) {}

    [[nodiscard]] constexpr int Over(Millis Dt) const { return CmPerSecond * Dt.GetCount() / 1000; }

private:
    int CmPerSecond;
};

class Position
{
public:
    constexpr explicit Position(int InCm) : Cm(InCm) {}

    [[nodiscard]] constexpr Position MovedBy(int Offset) const { return Position(Cm + Offset); }
    [[nodiscard]] constexpr int DistanceTo(Position Other) const { return Other.Cm - Cm; }
    [[nodiscard]] constexpr bool operator==(Position Other) const { return Cm == Other.Cm; }
    [[nodiscard]] constexpr int GetCm() const { return Cm; }

private:
    int Cm;
};
} // namespace mellos::example
