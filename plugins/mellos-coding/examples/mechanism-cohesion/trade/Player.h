#pragma once

#include "Item.h"

#include <set>

namespace mellos::example
{
// Data only. Knows nothing about Trade, which is layered on top of it.
struct Player
{
    unsigned Gold = 0;
    std::multiset<Item> Bag;
};
} // namespace mellos::example
