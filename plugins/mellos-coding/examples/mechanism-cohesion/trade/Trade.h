#pragma once

#include "Item.h"
#include "Player.h"
#include "Shop.h"

namespace mellos::example
{
// Trade mechanism: a trade mutates both Player and Shop and belongs to neither,
// so validation, pricing and transfer for both directions live only in this .h/.cpp.
// The mechanism name is the scope; functions and result types do not leak outward.
// Layering: Trade depends on Player/Shop/Item, none of which include Trade.h,
// so dependencies point one way and the data types stay reusable without trading.
class Trade
{
public:
    // One value per outcome: the enums list every way a trade can end.
    enum class BuyResult
    {
        Bought,
        OutOfStock,
        CustomerCannotAfford,
    };

    enum class SellResult
    {
        Sold,
        NotOwned,
        NotTraded,
        StoreCannotAfford,
    };

    Trade() = delete;

    // Customer buys one item at list price. On failure neither side changes.
    [[nodiscard]] static BuyResult Buy(Player& Customer, Shop& Store, Item Wanted);
    // Inverse of Buy: store takes one item back at buyback price. On failure neither side changes.
    [[nodiscard]] static SellResult Sell(Player& Customer, Shop& Store, Item Offered);
};
} // namespace mellos::example
