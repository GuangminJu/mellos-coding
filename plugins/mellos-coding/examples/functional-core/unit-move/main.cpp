#include "Motion.h"
#include "Owners.h"
#include "Units.h"

#include <iostream>

using namespace mellos::example;

int main()
{
    constexpr Position Camp{0};
    constexpr Position Gate{500};
    constexpr Speed March{100};

    Journey Trip{Camp, Gate, March};
    std::cout << "preview: in 3 s the unit would be at " << Motion::Approach(Trip.GetPosition(), Gate, March, Millis(3000)).GetCm() << " cm\n";
    while (!ArrivalEnd::GetResult(Trip))
    {
        Trip.Tick(Millis(1000));
        std::cout << "unit at " << Trip.GetPosition().GetCm() << " cm\n";
    }

    Patrol Guard{Camp, Position(200), March};
    for (int Tick = 0; Tick < 4; ++Tick)
    {
        Guard.Tick(Millis(1000));
        std::cout << "guard at " << Guard.GetPosition().GetCm() << " cm\n";
    }
}
