#pragma once

#include "Data/Quest.h"

#include <optional>

namespace mellos::example
{
class QuestEnd
{
public:
    [[nodiscard]] static std::optional<QuestEnd> GetResult(const Quest& Hunt)
    {
        if (Hunt.Done.Reached(Hunt.Required))
            return QuestEnd();
        return std::nullopt;
    }

private:
    QuestEnd() {}
};
} // namespace mellos::example
