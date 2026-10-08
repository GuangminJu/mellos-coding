#pragma once

#include "Gold.h"
#include "Item.h"

#include <set>

namespace mellos::example
{
struct Player
{
    Gold Purse;
    std::multiset<Item> Bag;
};
} // namespace mellos::example
