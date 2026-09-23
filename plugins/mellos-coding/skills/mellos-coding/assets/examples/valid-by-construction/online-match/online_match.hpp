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

class Level
{
public:
    Level(std::string InName, int InSpawn, int InGoal) : Name(std::move(InName)), Spawn(InSpawn), Goal(InGoal) {}

    [[nodiscard]] const std::string& GetName() const { return Name; }
    [[nodiscard]] int GetSpawn() const { return Spawn; }
    [[nodiscard]] int GetGoal() const { return Goal; }

private:
    std::string Name;
    int Spawn;
    int Goal;
};

class Player
{
public:
    Player(const Connection& InLink, const Level& Map) : Link(InLink), Position(Map.GetSpawn()) {}

    void Step()
    {
        ++Position;
        Link.Send("move " + std::to_string(Position));
    }

    [[nodiscard]] int GetPosition() const { return Position; }

private:
    const Connection& Link;
    int Position;
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
        if (Game.GetPlayer().GetPosition() >= Game.GetLevel().GetGoal())
            return MatchEnd();
        return std::nullopt;
    }

private:
    MatchEnd() {}
};
} // namespace mellos::example
