#include "Motion.h"
#include "Owners.h"
#include "Units.h"

#include <type_traits>

using namespace mellos::example;

constexpr Position AfterTicks(Journey Trip, Millis Dt, int Ticks)
{
    for (int Done = 0; Done < Ticks; ++Done)
        Trip.Tick(Dt);
    return Trip.GetPosition();
}

constexpr bool PatrolTurnsAtEachEnd()
{
    Patrol Guard{Position(0), Position(200), Speed(100)};
    Guard.Tick(Millis(1000));
    Guard.Tick(Millis(1000));
    const bool ReachedEnd = Guard.GetPosition() == Position(200);
    Guard.Tick(Millis(1000));
    Guard.Tick(Millis(1000));
    return ReachedEnd && Guard.GetPosition() == Position(0);
}

static_assert(std::is_empty_v<Motion>, "The step holds no state");
static_assert(Motion::Approach(Position(0), Position(500), Speed(100), Millis(1000)) == Position(100), "A tick covers speed times delta");
static_assert(Motion::Approach(Position(450), Position(500), Speed(100), Millis(1000)) == Position(500), "A tick never overshoots");
static_assert(Motion::Approach(Position(500), Position(0), Speed(100), Millis(1000)) == Position(400), "The step works in both directions");
static_assert(AfterTicks(Journey{Position(0), Position(500), Speed(100)}, Millis(1000), 3)
                  == Motion::Approach(Position(0), Position(500), Speed(100), Millis(3000)),
              "A preview through the step equals what the owner will do");
static_assert(PatrolTurnsAtEachEnd(), "The turnaround rule lives in the owner, not in the step");
static_assert(!std::is_default_constructible_v<ArrivalEnd>, "Only a judgement creates an arrival");
