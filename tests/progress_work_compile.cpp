#include "../plugins/mellos-coding/skills/mellos-coding/assets/examples/multi-state/progress-work/progress_work.hpp"

#include <type_traits>

using namespace mellos::example;

constexpr bool ResultsAreIndependent()
{
    Running Work(Begin{4});
    if (HalfEnd::GetResult(Work) || CompletedEnd::GetResult(Work))
        return false;

    Work.Advance();
    Work.Advance();
    if (!HalfEnd::GetResult(Work) || CompletedEnd::GetResult(Work))
        return false;

    const bool RepeatedHalf = HalfEnd::GetResult(Work).has_value();
    if (!RepeatedHalf || Work.GetCurrent() != 2)
        return false;

    Work.Advance();
    Work.Advance();
    return HalfEnd::GetResult(Work) && CompletedEnd::GetResult(Work)
        && CompletedEnd::GetResult(Work) && Work.GetCurrent() == 4;
}

constexpr bool OriginalHalfwayRuleIsPreserved()
{
    Running Work(Begin{3});
    Work.Advance();
    return HalfEnd::GetResult(Work) && !CompletedEnd::GetResult(Work);
}

static_assert(ResultsAreIndependent(), "Results must coexist and remain repeatable without advancing work");
static_assert(OriginalHalfwayRuleIsPreserved(), "Preserve the original Total / 2 rule");
static_assert(!std::is_default_constructible_v<Begin> && !std::is_default_constructible_v<HalfEnd>
                  && !std::is_default_constructible_v<CompletedEnd>,
              "Only a request creates Begin and only a judgement creates a result");
