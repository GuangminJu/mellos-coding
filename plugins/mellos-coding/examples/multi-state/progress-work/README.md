# Multi-State: Progress Work

**Applies when:** a class holds multiple states, including mutually exclusive or re-entered ones.

A task must answer both "half done?" and "complete?". Instead of one class driven by a state enum or flags, responsibilities are split: `Begin` (input), `Running` (data, execution and cleanup), independent read-only `End` predicates, and external orchestration.

| Role | Files |
|---|---|
| Steps, Begin, Running, End | [progress_work.hpp](progress_work.hpp) |
| Orchestration | [progress_work.cpp](progress_work.cpp) |
| Verification | [progress_work_compile.cpp](progress_work_compile.cpp) |

## Benefits

| Benefit | Where |
|---|---|
| **Open–Closed**: a new outcome is a new `End` type, and `Running` stays untouched. | [Running](progress_work.hpp#L28-L40) |
| **Command–Query Separation**: `End` reads `const Running&`, so queries are idempotent and never advance work. | [HalfEnd](progress_work.hpp#L42-L54), [verification](progress_work_compile.cpp#L18-L20) |
| **Non-exclusive outcomes**: outcomes may hold at the same time without overwriting each other, and a holding outcome does not stop the run. | [Ends](progress_work.hpp#L42-L68), [verification](progress_work_compile.cpp#L24-L25) |
| **Valid by construction**: only a request builds `Begin`, and only an `End`'s own judgement can create its result. | [Begin](progress_work.hpp#L23), [private constructor](progress_work.hpp#L52-L53), [verification](progress_work_compile.cpp#L37-L39) |
| **No Primitive Obsession**: progress is `Steps`, exposing only `Next`, `Half` and `Reached`. | [Steps](progress_work.hpp#L7-L19) |
| **Separation of concerns**: scheduling and once-per-run notification live in the orchestration, not in hidden state. | [progress_work.cpp#L11-L21](progress_work.cpp#L11-L21) |
| **No speculative fallbacks**: no negative-value guards, saturation or rounding beyond the requirement; `Half` keeps the integer `Total / 2` as specified. | [Half](progress_work.hpp#L13), [HalfEnd](progress_work.hpp#L47) |
| **Compile-time verification**: everything is `constexpr`, so behaviour is pinned by `static_assert`, kept apart from the demo. | [progress_work_compile.cpp#L35-L39](progress_work_compile.cpp#L35-L39) |

Under concurrent access, `End` reads must be consistent and result and resource lifetimes must stay valid.

## Illustrative only

The `Total / 2` threshold is a demo choice, not a business rule.
