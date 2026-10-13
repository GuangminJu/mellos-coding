#pragma once

#include "Data/Monster.h"
#include "Data/Quest.h"
#include "Game/Combat.h"

#include <iosfwd>

namespace mellos::example
{
class Hud
{
public:
    explicit Hud(std::ostream& InDisplay) : Display(InDisplay) {}

    void Draw(const Monster& Foe, const Quest& Hunt) const;
    void ShowHit(Combat::HitResult Result) const;
    void ShowVictory() const;

private:
    std::ostream& Display;
};
} // namespace mellos::example
