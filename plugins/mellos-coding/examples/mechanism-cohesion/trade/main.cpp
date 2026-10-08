#include "Trade.h"

#include <iostream>

using namespace mellos::example;

static void Print(const char* Step, const Player& Customer, const Shop& Store)
{
    std::cout << Step << ": player " << Customer.Purse.GetAmount() << "g/" << Customer.Bag.size()
              << " items, shop " << Store.Till.GetAmount() << "g\n";
}

int main()
{
    Player Customer{Gold(100), {Item::Gem}};
    Shop Store{Gold(20), {{Item::Sword, {Gold(80), Quantity(1)}}, {Item::Potion, {Gold(10), Quantity(5)}}}};

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
