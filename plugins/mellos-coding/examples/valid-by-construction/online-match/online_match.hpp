#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <utility>

namespace mellos::example
{
class Connection
{
public:
    [[nodiscard]] static std::optional<Connection> Open(std::string Host)
    {
        if (Host == "unreachable")
            return std::nullopt;
        return Connection(std::move(Host));
    }

    void Send(const std::string& Message) const { std::cout << Host << " <- " << Message << '\n'; }

private:
    explicit Connection(std::string InHost) : Host(std::move(InHost)) {}

    std::string Host;
};

class Position
{
public:
    explicit Position(int InTile) : Tile(InTile) {}

    [[nodiscard]] Position Next() const { return Position(Tile + 1); }
    [[nodiscard]] bool Reached(Position Goal) const { return Tile >= Goal.Tile; }
    [[nodiscard]] std::string ToString() const { return std::to_string(Tile); }

private:
    int Tile;
};

class Level
{
public:
    Level(std::string InName, Position InSpawn, Position InGoal) : Name(std::move(InName)), Spawn(InSpawn), Goal(InGoal) {}

    [[nodiscard]] const std::string& GetName() const { return Name; }
    [[nodiscard]] Position GetSpawn() const { return Spawn; }
    [[nodiscard]] Position GetGoal() const { return Goal; }

private:
    std::string Name;
    Position Spawn;
    Position Goal;
};

class Player
{
public:
    Player(const Connection& InLink, const Level& Map) : Link(InLink), Location(Map.GetSpawn()) {}

    void Step()
    {
        Location = Location.Next();
        Link.Send("move " + Location.ToString());
    }

    [[nodiscard]] Position GetLocation() const { return Location; }

private:
    const Connection& Link;
    Position Location;
};

class Match
{
public:
    Match(const Connection& Link, Level InMap) : Map(std::move(InMap)), Hero(Link, Map) {}

    void Tick() { Hero.Step(); }

    [[nodiscard]] const Level& GetLevel() const { return Map; }
    [[nodiscard]] const Player& GetPlayer() const { return Hero; }

private:
    Level Map;
    Player Hero;
};

class MatchEnd
{
public:
    [[nodiscard]] static std::optional<MatchEnd> GetResult(const Match& Game)
    {
        if (Game.GetPlayer().GetLocation().Reached(Game.GetLevel().GetGoal()))
            return MatchEnd();
        return std::nullopt;
    }

private:
    MatchEnd() {}
};
} // namespace mellos::example
