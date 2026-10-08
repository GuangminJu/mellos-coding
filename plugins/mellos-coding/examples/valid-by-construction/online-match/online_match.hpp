#pragma once

#include <iostream>
#include <optional>
#include <set>
#include <string>
#include <utility>

namespace mellos::example
{
class HostName
{
public:
    explicit HostName(std::string InValue) : Value(std::move(InValue)) {}

    [[nodiscard]] const std::string& Get() const { return Value; }
    [[nodiscard]] bool operator<(const HostName& Other) const { return Value < Other.Value; }

private:
    std::string Value;
};

// Stands in for the real network: which hosts answer is decided outside the program.
class Network
{
public:
    explicit Network(std::set<HostName> InReachable) : Reachable(std::move(InReachable)) {}

    [[nodiscard]] bool CanReach(const HostName& Host) const { return Reachable.count(Host) > 0; }

private:
    std::set<HostName> Reachable;
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

class Connection
{
public:
    [[nodiscard]] static std::optional<Connection> Open(const Network& Net, HostName Host)
    {
        if (!Net.CanReach(Host))
            return std::nullopt;
        return Connection(std::move(Host));
    }

    void SendMove(Position To) const { std::cout << Host.Get() << " <- move " << To.ToString() << '\n'; }

private:
    explicit Connection(HostName InHost) : Host(std::move(InHost)) {}

    HostName Host;
};

class LevelName
{
public:
    explicit LevelName(std::string InValue) : Value(std::move(InValue)) {}

    [[nodiscard]] const std::string& Get() const { return Value; }

private:
    std::string Value;
};

class Level
{
public:
    Level(LevelName InName, Position InSpawn, Position InGoal) : Name(std::move(InName)), Spawn(InSpawn), Goal(InGoal) {}

    [[nodiscard]] const LevelName& GetName() const { return Name; }
    [[nodiscard]] Position GetSpawn() const { return Spawn; }
    [[nodiscard]] Position GetGoal() const { return Goal; }

private:
    LevelName Name;
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
        Link.SendMove(Location);
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
