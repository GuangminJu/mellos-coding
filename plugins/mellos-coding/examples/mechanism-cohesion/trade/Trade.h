#pragma once

#include "Item.h"
#include "Player.h"
#include "Shop.h"

namespace mellos::example
{
class Trade
{
public:
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

    [[nodiscard]] static BuyResult Buy(Player& Customer, Shop& Store, Item Wanted);
    [[nodiscard]] static SellResult Sell(Player& Customer, Shop& Store, Item Offered);
};
} // namespace mellos::example
