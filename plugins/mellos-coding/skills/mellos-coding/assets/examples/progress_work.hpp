#pragma once

#include <optional>

namespace mellos::example
{
struct Begin
{
    int Total = 100;
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

struct HalfEnd
{
    [[nodiscard]] static constexpr std::optional<HalfEnd> GetResult(const Running& Work)
    {
        if (Work.GetCurrent() >= Work.GetTotal() / 2)
            return HalfEnd{};
        return std::nullopt;
    }
};

struct CompletedEnd
{
    [[nodiscard]] static constexpr std::optional<CompletedEnd> GetResult(const Running& Work)
    {
        if (Work.GetCurrent() >= Work.GetTotal())
            return CompletedEnd{};
        return std::nullopt;
    }
};
} // namespace mellos::example
