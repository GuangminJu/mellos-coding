#include "progress_work.hpp"

#include <type_traits>

using namespace mellos::example;

constexpr bool ResultsAreIndependent()
{
    Running Work(Begin{Steps(4)});
    if (HalfEnd::GetResult(Work) || CompletedEnd::GetResult(Work))
        return false;

    Work.Advance();
    Work.Advance();
    if (!HalfEnd::GetResult(Work) || CompletedEnd::GetResult(Work))
        return false;

    const bool RepeatedHalf = HalfEnd::GetResult(Work).has_value();
    if (!RepeatedHalf || !(Work.GetCurrent() == Steps(2)))
        return false;

    Work.Advance();
    Work.Advance();
    return HalfEnd::GetResult(Work) && CompletedEnd::GetResult(Work)
        && CompletedEnd::GetResult(Work) && Work.GetCurrent() == Steps(4);
}

constexpr bool OriginalHalfwayRuleIsPreserved()
{
    Running Work(Begin{Steps(3)});
    Work.Advance();
    return HalfEnd::GetResult(Work) && !CompletedEnd::GetResult(Work);
}

static_assert(ResultsAreIndependent(), "Results must coexist and remain repeatable without advancing work");
static_assert(OriginalHalfwayRuleIsPreserved(), "Preserve the original Total / 2 rule");
static_assert(!std::is_default_constructible_v<Begin> && !std::is_default_constructible_v<HalfEnd>
                  && !std::is_default_constructible_v<CompletedEnd>,
              "Only a request creates Begin and only a judgement creates a result");
