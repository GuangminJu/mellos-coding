#include "Game/Combat.h"

namespace mellos::example
{
Combat::HitResult Combat::Strike(Monster& Foe, Quest& Hunt, HitPoints Blow)
{
    Foe.Health = Foe.Health.Lose(Blow);
    if (!Foe.Health.IsDepleted())
        return HitResult::Wounded;

    Hunt.Done = Hunt.Done.Next();
    return HitResult::Slain;
}
} // namespace mellos::example
