#include "online_match.hpp"

#include <iostream>
#include <vector>

using namespace mellos::example;

int main()
{
    const Network Internet{{HostName("game.example")}};
    const std::optional<Connection> Link = Connection::Open(Internet, HostName("game.example"));
    if (!Link)
        return 1;

    const std::vector<Level> Playlist{Level{LevelName("Arena"), Position(0), Position(2)}, Level{LevelName("Canyon"), Position(3), Position(5)}};
    for (const Level& Map : Playlist)
    {
        Match Game{*Link, Map};
        while (!MatchEnd::GetResult(Game))
            Game.Tick();
        std::cout << Map.GetName().Get() << " cleared\n";
    }
}
