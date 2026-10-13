#pragma once

#include "Motion.h"
#include "Units.h"

#include <optional>

namespace mellos::example
{
class Journey
{
public:
    constexpr Journey(Position InStart, Position InDestination, Speed InRate)
        : Here(InStart), Destination(InDestination), Rate(InRate)
    {
    }

    constexpr void Tick(Millis Dt) { Here = Motion::Approach(Here, Destination, Rate, Dt); }

    [[nodiscard]] constexpr Position GetPosition() const { return Here; }
    [[nodiscard]] constexpr Position GetDestination() const { return Destination; }

private:
    Position Here;
    Position Destination;
    Speed Rate;
};

class ArrivalEnd
{
public:
    [[nodiscard]] static constexpr std::optional<ArrivalEnd> GetResult(const Journey& Trip)
    {
        if (Trip.GetPosition() == Trip.GetDestination())
            return ArrivalEnd();
        return std::nullopt;
    }

private:
    constexpr ArrivalEnd() {}
};

class Patrol
{
public:
    constexpr Patrol(Position InStart, Position InEnd, Speed InRate)
        : Here(InStart), Start(InStart), End(InEnd), Toward(InEnd), Rate(InRate)
    {
    }

    constexpr void Tick(Millis Dt)
    {
        Here = Motion::Approach(Here, Toward, Rate, Dt);
        if (Here == Toward)
            Toward = Toward == End ? Start : End;
    }

    [[nodiscard]] constexpr Position GetPosition() const { return Here; }

private:
    Position Here;
    Position Start;
    Position End;
    Position Toward;
    Speed Rate;
};
} // namespace mellos::example
