#pragma once

#include "Gold.h"
#include "Item.h"

#include <map>
#include <optional>

namespace mellos::example
{
// A stock count that cannot drop below zero: taking one yields what remains or nothing.
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

// Each listing carries its own price, so no stocked item can lack one.
struct Listing
{
    Gold Price;
    Quantity Stock;
};

// Data only: every representable state is valid. Knows nothing about Trade, which is layered on top of it.
struct Shop
{
    Gold Till;
    std::map<Item, Listing> Listings;
};
} // namespace mellos::example
