#include "Data/Monster.h"
#include "Data/Quest.h"
#include "Game/Combat.h"
#include "Game/QuestEnd.h"
#include "Ui/Hud.h"

#include <iostream>

using namespace mellos::example;

int main()
{
    const Hud Screen{std::cout};
    Quest Hunt{Kills(0), Kills(2)};

    while (!QuestEnd::GetResult(Hunt))
    {
        Monster Foe{HitPoints(3)};
        while (!BattleEnd::GetResult(Foe))
        {
            Screen.Draw(Foe, Hunt);
            Screen.ShowHit(Combat::Strike(Foe, Hunt, HitPoints(2)));
        }
    }

    Screen.ShowVictory();
}
