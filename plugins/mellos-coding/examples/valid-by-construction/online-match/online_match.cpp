#include "online_match.hpp"

#include <iostream>
#include <vector>

using namespace mellos::example;

int main()
{
    const std::optional<Connection> Link = Connection::Open("game.example");
    if (!Link)
        return 1;

    const std::vector<Level> Playlist{Level{"Arena", Position(0), Position(2)}, Level{"Canyon", Position(3), Position(5)}};
    for (const Level& Map : Playlist)
    {
        Match Game{*Link, Map};
        while (!MatchEnd::GetResult(Game))
            Game.Tick();
        std::cout << Map.GetName() << " cleared\n";
    }
}
