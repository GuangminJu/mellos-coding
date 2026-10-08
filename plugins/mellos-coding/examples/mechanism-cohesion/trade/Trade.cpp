#include "Trade.h"

namespace mellos::example
{
namespace
{
// The only definition of buyback vs. list price; both pricing rules live on this page.
constexpr unsigned BuybackDivisor = 2;
}

// Buy and Sell sit together with the same shape: verify both sides -> price -> commit.
// Their commit lines mirror each other: gold, stock and bag flow in opposite directions.
Trade::BuyResult Trade::Buy(Player& Customer, Shop& Store, Item Wanted)
{
    const auto Found = Store.Listings.find(Wanted);
    if (Found == Store.Listings.end() || Found->second.Stock == 0)
        return BuyResult::OutOfStock;

    Listing& Offer = Found->second;
    const unsigned Price = Offer.Price;
    if (Customer.Gold < Price)
        return BuyResult::CustomerCannotAfford;

    // Both sides are verified, so the commit cannot fail and no half-done trade exists.
    Customer.Gold -= Price;
    Store.Gold += Price;
    --Offer.Stock;
    Customer.Bag.insert(Wanted);
    return BuyResult::Bought;
}

Trade::SellResult Trade::Sell(Player& Customer, Shop& Store, Item Offered)
{
    const auto Owned = Customer.Bag.find(Offered);
    if (Owned == Customer.Bag.end())
        return SellResult::NotOwned;

    const auto Found = Store.Listings.find(Offered);
    if (Found == Store.Listings.end())
        return SellResult::NotTraded;

    Listing& Offer = Found->second;
    const unsigned Price = Offer.Price / BuybackDivisor;
    if (Store.Gold < Price)
        return SellResult::StoreCannotAfford;

    // Line-by-line inverse of Buy's commit.
    Store.Gold -= Price;
    Customer.Gold += Price;
    ++Offer.Stock;
    Customer.Bag.erase(Owned);
    return SellResult::Sold;
}
} // namespace mellos::example
