#pragma once

#include "Item.h"

#include <map>

namespace mellos::example
{
struct Listing
{
    unsigned Price = 0;
    unsigned Stock = 0;
};

// Data only. Knows nothing about Trade, which is layered on top of it.
struct Shop
{
    unsigned Gold = 0;
    std::map<Item, Listing> Listings;
};
} // namespace mellos::example
