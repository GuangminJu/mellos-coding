# Valid by Construction: Online Match

**Applies when:** designing how objects are created, what they depend on, how long they live, and how phases change.

A client connects once, then plays a list of levels. Every object is usable from the moment it exists: no `Init`, `IsValid`, half-built or invalidated state, nullable members or call-order conventions.

| Role | Files |
|---|---|
| HostName, Position, Connection, LevelName, Level, Player, Match, MatchEnd | [online_match.hpp](online_match.hpp) |
| Orchestration | [online_match.cpp](online_match.cpp) |

## Benefits

| Benefit | Where |
|---|---|
| **Valid by construction**: every dependency is a constructor parameter, so holding an object means it is ready to use. | [Player](online_match.hpp#L82), [Match](online_match.hpp#L100) |
| **Fail once at the boundary**: the only fallible acquisition returns `std::optional` and is checked once; holders never recheck. | [Open](online_match.hpp#L37-L42), [check](online_match.cpp#L10-L12) |
| **Scoped borrowing**: the lender's scope encloses the borrower, so dependencies are held by reference, never by nullable pointer. | [Player::Link](online_match.hpp#L93), [lifetimes](online_match.cpp#L10-L21) |
| **Deterministic initialization order**: member declaration order is construction order, and destruction runs in reverse automatically. | [Match](online_match.hpp#L100), [#L108-L109](online_match.hpp#L108-L109) |
| **Phase change by construction**: the next match is a new object, not a reset flag or reused instance. | [online_match.cpp#L15-L21](online_match.cpp#L15-L21) |
| **End of life by judgement**: `MatchEnd` decides when a match has served its purpose, and the owner ends the scope (see `multi-state/progress-work`). | [MatchEnd](online_match.hpp#L112-L124), [loop](online_match.cpp#L18-L19) |
| **No Primitive Obsession**: hosts, level names and tiles are `HostName`, `LevelName` and `Position`, and wire encoding stays inside `Connection`, so callers pass domain values. | [HostName](online_match.hpp#L10-L19), [Position](online_match.hpp#L21-L32), [LevelName](online_match.hpp#L53-L62), [SendMove](online_match.hpp#L44-L45) |
| **Composition over inheritance**: `Match` is composed of a `Level` and a `Player`; nothing is reused through inheritance. | [Match](online_match.hpp#L108-L109) |

## Illustrative only

The `unreachable` check and the level data are demo choices, not business rules.
