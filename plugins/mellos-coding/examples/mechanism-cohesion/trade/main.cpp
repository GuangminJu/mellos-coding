#include "Trade.h"

#include <iostream>

using namespace mellos::example;

static void Print(const char* Step, const Player& Customer, const Shop& Store)
{
    std::cout << Step << ": player " << Customer.Gold << "g/" << Customer.Bag.size()
              << " items, shop " << Store.Gold << "g\n";
}

int main()
{
    Player Customer{100, {Item::Gem}};
    Shop Store{20, {{Item::Sword, {80, 1}}, {Item::Potion, {10, 5}}}};

    std::cout << "Buy sword: " << (Trade::Buy(Customer, Store, Item::Sword) == Trade::BuyResult::Bought) << '\n';
    Print("After buy", Customer, Store);

    std::cout << "Buy sword again, out of stock: "
              << (Trade::Buy(Customer, Store, Item::Sword) == Trade::BuyResult::OutOfStock) << '\n';

    std::cout << "Sell gem, not traded: "
              << (Trade::Sell(Customer, Store, Item::Gem) == Trade::SellResult::NotTraded) << '\n';

    std::cout << "Sell sword back at half price: "
              << (Trade::Sell(Customer, Store, Item::Sword) == Trade::SellResult::Sold) << '\n';
    Print("After sell", Customer, Store);
}
