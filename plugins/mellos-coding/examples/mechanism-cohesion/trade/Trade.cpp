#include "Trade.h"

namespace mellos::example
{
namespace
{
constexpr unsigned BuybackDivisor = 2;
}

Trade::BuyResult Trade::Buy(Player& Customer, Shop& Store, Item Wanted)
{
    const auto Found = Store.Listings.find(Wanted);
    if (Found == Store.Listings.end())
        return BuyResult::OutOfStock;

    Listing& Offer = Found->second;
    const std::optional<Quantity> StockLeft = Offer.Stock.TakeOne();
    if (!StockLeft)
        return BuyResult::OutOfStock;

    const Gold Price = Offer.Price;
    const std::optional<Gold> CustomerLeft = Customer.Purse.Spend(Price);
    if (!CustomerLeft)
        return BuyResult::CustomerCannotAfford;

    Customer.Purse = *CustomerLeft;
    Store.Till = Store.Till + Price;
    Offer.Stock = *StockLeft;
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
    const Gold Price = Offer.Price / BuybackDivisor;
    const std::optional<Gold> StoreLeft = Store.Till.Spend(Price);
    if (!StoreLeft)
        return SellResult::StoreCannotAfford;

    Store.Till = *StoreLeft;
    Customer.Purse = Customer.Purse + Price;
    Offer.Stock = Offer.Stock.AddOne();
    Customer.Bag.erase(Owned);
    return SellResult::Sold;
}
} // namespace mellos::example
