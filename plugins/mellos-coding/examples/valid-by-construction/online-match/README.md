# Valid by Construction: Online Match

**Applies when:** designing how objects are created, what they depend on, how long they live, and how phases change.

A client connects once, then plays a list of levels. Every object is usable from the moment it exists: no `Init`, `IsValid`, half-built or invalidated state, nullable members or call-order conventions.

| Role | Files |
|---|---|
| HostName, Network, Position, Connection, LevelName, Level, Player, Match, MatchEnd | [online_match.hpp](online_match.hpp) |
| Orchestration | [online_match.cpp](online_match.cpp) |

## Benefits

| Benefit | Where |
|---|---|
| **Valid by construction**: every dependency is a constructor parameter, so holding an object means it is ready to use. | [Player](online_match.hpp#L95), [Match](online_match.hpp#L113) |
| **Fail once at the boundary**: the only fallible acquisition returns `std::optional` and is checked once; holders never recheck. | [Open](online_match.hpp#L51-L56), [check](online_match.cpp#L11-L13) |
| **Scoped borrowing**: the lender's scope encloses the borrower, so dependencies are held by reference, never by nullable pointer. | [Player::Link](online_match.hpp#L106), [lifetimes](online_match.cpp#L10-L22) |
| **Deterministic initialization order**: member declaration order is construction order, and destruction runs in reverse automatically. | [Match](online_match.hpp#L113), [#L121-L122](online_match.hpp#L121-L122) |
| **Phase change by construction**: the next match is a new object, not a reset flag or reused instance. | [online_match.cpp#L16-L22](online_match.cpp#L16-L22) |
| **End of life by judgement**: `MatchEnd` decides when a match has served its purpose, and the owner ends the scope (see `multi-state/progress-work`). | [MatchEnd](online_match.hpp#L125-L137), [loop](online_match.cpp#L19-L20) |
| **No Primitive Obsession**: hosts, level names and tiles are `HostName`, `LevelName` and `Position`, and wire encoding stays inside `Connection`, so callers pass domain values. | [HostName](online_match.hpp#L11-L21), [Position](online_match.hpp#L35-L46), [LevelName](online_match.hpp#L66-L75), [SendMove](online_match.hpp#L58) |
| **Dependency injection over hardcoding**: which hosts are reachable comes from an injected `Network`; literals appear only in the demo data. | [Network](online_match.hpp#L23-L33), [Open](online_match.hpp#L51), [demo](online_match.cpp#L10-L11) |
| **Comments only for what code cannot say**: the single comment states that reachability is decided outside the program. | [#L23](online_match.hpp#L23) |
| **Composition over inheritance**: `Match` is composed of a `Level` and a `Player`; nothing is reused through inheritance. | [Match](online_match.hpp#L121-L122) |

## Illustrative only

The network contents and the level data are demo choices, not business rules.
