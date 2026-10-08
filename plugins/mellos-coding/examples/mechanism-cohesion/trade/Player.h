#pragma once

#include "Gold.h"
#include "Item.h"

#include <set>

namespace mellos::example
{
// Data only: every representable state is valid. Knows nothing about Trade, which is layered on top of it.
struct Player
{
    Gold Purse;
    std::multiset<Item> Bag;
};
} // namespace mellos::example
