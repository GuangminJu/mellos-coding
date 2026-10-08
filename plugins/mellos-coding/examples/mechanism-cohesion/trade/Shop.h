#pragma once

#include "Gold.h"
#include "Item.h"

#include <map>
#include <optional>

namespace mellos::example
{
class Quantity
{
public:
    constexpr explicit Quantity(unsigned InCount) : Count(InCount) {}

    [[nodiscard]] constexpr std::optional<Quantity> TakeOne() const
    {
        if (Count == 0)
            return std::nullopt;
        return Quantity(Count - 1);
    }

    [[nodiscard]] constexpr Quantity AddOne() const { return Quantity(Count + 1); }

private:
    unsigned Count;
};

struct Listing
{
    Gold Price;
    Quantity Stock;
};

struct Shop
{
    Gold Till;
    std::map<Item, Listing> Listings;
};
} // namespace mellos::example
