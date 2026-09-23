#pragma once

#include <optional>

namespace mellos::example
{
struct Begin
{
    constexpr explicit Begin(int InTotal) : Total(InTotal) {}

    const int Total;
};

class Running
{
public:
    constexpr explicit Running(const Begin& Request) : Total(Request.Total) {}

    constexpr void Advance() { ++Current; }
    [[nodiscard]] constexpr int GetCurrent() const { return Current; }
    [[nodiscard]] constexpr int GetTotal() const { return Total; }

private:
    int Current = 0;
    const int Total;
};

class HalfEnd
{
public:
    [[nodiscard]] static constexpr std::optional<HalfEnd> GetResult(const Running& Work)
    {
        if (Work.GetCurrent() >= Work.GetTotal() / 2)
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
        if (Work.GetCurrent() >= Work.GetTotal())
            return CompletedEnd();
        return std::nullopt;
    }

private:
    constexpr CompletedEnd() {}
};
} // namespace mellos::example
