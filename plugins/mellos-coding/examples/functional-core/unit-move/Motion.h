#pragma once

#include "Units.h"

namespace mellos::example
{
class Motion
{
public:
    Motion() = delete;

    [[nodiscard]] static constexpr Position Approach(Position From, Position Toward, Speed Rate, Millis Dt)
    {
        const int Reach = Rate.Over(Dt);
        const int Gap = From.DistanceTo(Toward);
        if (Gap > Reach)
            return From.MovedBy(Reach);
        if (Gap < -Reach)
            return From.MovedBy(-Reach);
        return Toward;
    }
};
} // namespace mellos::example
