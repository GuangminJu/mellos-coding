#pragma once

#include <optional>

namespace mellos::example
{
class Steps
{
public:
    constexpr explicit Steps(int InCount) : Count(InCount) {}

    [[nodiscard]] constexpr Steps Next() const { return Steps(Count + 1); }
    [[nodiscard]] constexpr Steps Half() const { return Steps(Count / 2); }
    [[nodiscard]] constexpr bool Reached(Steps Target) const { return Count >= Target.Count; }
    [[nodiscard]] constexpr bool operator==(Steps Other) const { return Count == Other.Count; }

private:
    int Count;
};

struct Begin
{
    constexpr explicit Begin(Steps InTotal) : Total(InTotal) {}

    const Steps Total;
};

class Running
{
public:
    constexpr explicit Running(const Begin& Request) : Total(Request.Total) {}

    constexpr void Advance() { Current = Current.Next(); }
    [[nodiscard]] constexpr Steps GetCurrent() const { return Current; }
    [[nodiscard]] constexpr Steps GetTotal() const { return Total; }

private:
    Steps Current = Steps(0);
    const Steps Total;
};

class HalfEnd
{
public:
    [[nodiscard]] static constexpr std::optional<HalfEnd> GetResult(const Running& Work)
    {
        if (Work.GetCurrent().Reached(Work.GetTotal().Half()))
            return HalfEnd();
        return std::nullopt;
    }

private:
    constexpr HalfEnd() {}
};

class CompletedEnd
{
public:
    [[nodiscard]] static constexpr std::optional<CompletedEnd> GetResult(const Running& Work)
    {
        if (Work.GetCurrent().Reached(Work.GetTotal()))
            return CompletedEnd();
        return std::nullopt;
    }

private:
    constexpr CompletedEnd() {}
};
} // namespace mellos::example
