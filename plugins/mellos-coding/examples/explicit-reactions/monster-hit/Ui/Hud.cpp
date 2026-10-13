#include "Ui/Hud.h"

#include <ostream>

namespace mellos::example
{
void Hud::Draw(const Monster& Foe, const Quest& Hunt) const
{
    Display << "HP " << Foe.Health.GetAmount() << ", kills " << Hunt.Done.GetCount() << '/'
            << Hunt.Required.GetCount() << '\n';
}

void Hud::ShowHit(Combat::HitResult Result) const
{
    switch (Result)
    {
    case Combat::HitResult::Wounded:
        Display << "  hit\n";
        break;
    case Combat::HitResult::Slain:
        Display << "  slain\n";
        break;
    }
}

void Hud::ShowVictory() const { Display << "Quest complete\n"; }
} // namespace mellos::example
