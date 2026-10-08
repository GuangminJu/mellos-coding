#pragma once

#include "Gold.h"
#include "Item.h"

#include <map>

namespace mellos::example
{
// Each listing carries its own price, so no stocked item can lack one.
struct Listing
{
    Gold Price;
    unsigned Stock;
};

// Data only: every representable state is valid. Knows nothing about Trade, which is layered on top of it.
struct Shop
{
    Gold Till;
    std::map<Item, Listing> Listings;
};
} // namespace mellos::example
