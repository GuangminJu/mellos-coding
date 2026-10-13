#pragma once

#include "Data/Monster.h"
#include "Data/Quest.h"

#include <optional>

namespace mellos::example
{
class Combat
{
public:
    enum class HitResult
    {
        Wounded,
        Slain,
    };

    Combat() = delete;

    [[nodiscard]] static HitResult Strike(Monster& Foe, Quest& Hunt, HitPoints Blow);
};

class BattleEnd
{
public:
    [[nodiscard]] static std::optional<BattleEnd> GetResult(const Monster& Foe)
    {
        if (Foe.Health.IsDepleted())
            return BattleEnd();
        return std::nullopt;
    }

private:
    BattleEnd() {}
};
} // namespace mellos::example
