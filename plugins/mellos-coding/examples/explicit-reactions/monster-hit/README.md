# Explicit Reactions: Monster Hit

**Applies when:** an event in one object must trigger reactions in other objects or layers, where an observer, event, delegate or callback would be the usual choice.

A hit on a monster must advance a quest and update the HUD. *Observer* keeps the source ignorant of its reactors at the cost of indirection: who reacts, in what order and for how long is decided at runtime. Here the source stays just as ignorant: the mechanism mutates data and returns what happened, and each block above reacts by direct calls, so the call tree is the notification path.

| Block | Files | May include |
|---|---|---|
| Data: state and value semantics only | [Data/Monster.h](Data/Monster.h), [Data/Quest.h](Data/Quest.h) | nothing |
| Game logic: every rule that changes or judges state | [Game/Combat.h](Game/Combat.h), [Game/Combat.cpp](Game/Combat.cpp), [Game/QuestEnd.h](Game/QuestEnd.h) | Data |
| UI logic: reads state, renders outcomes | [Ui/Hud.h](Ui/Hud.h), [Ui/Hud.cpp](Ui/Hud.cpp) | Data, Game |
| App: sequencing only | [main.cpp](main.cpp) | all three |

## Benefits

| Benefit | Where |
|---|---|
| **No callbacks**: every reaction is a direct call on an object the caller holds; nothing is registered, so there is no subscription lifetime, lapsed listener or dangling handler, and every reaction with its order sits on one screen. | [Strike](Game/Combat.cpp#L5-L13), [loop](main.cpp#L16-L24) |
| **Reactions at their own level**: a slain monster credits the quest inside the game mechanism, the HUD shows it from the returned outcome, and the app only sequences the two; no block performs another block's reaction. | [Combat.cpp#L8-L12](Game/Combat.cpp#L8-L12), [ShowHit](Ui/Hud.cpp#L13-L24), [main.cpp#L22](main.cpp#L22) |
| **Dependency Rule**: includes point one way, Data ← Game ← UI ← App; data names no rule or screen, game logic names no HUD, and only the app sees every block. | [Combat.h#L3-L4](Game/Combat.h#L3-L4), [Hud.h#L3-L5](Ui/Hud.h#L3-L5), [main.cpp#L1-L5](main.cpp#L1-L5) |
| **Explicit dependencies**: what an operation touches is a parameter, never a singleton or a held reactor (as `Connection` is in `valid-by-construction/online-match`); what follows from it is a returned outcome for the owner, so nothing reaches upward. | [Strike](Game/Combat.h#L21), [HitResult](Game/Combat.h#L13-L17) |
| **Mechanism Cohesion**: a strike mutates monster and quest and belongs to neither, so it is a mechanism, not a method on either (see `mechanism-cohesion/trade`); the data are plain records. | [Combat](Game/Combat.h#L10-L22), [Monster](Data/Monster.h#L22-L25), [Quest](Data/Quest.h#L18-L22) |
| **Exhaustive outcomes**: `[[nodiscard]]` forbids ignoring a hit, and the switch has no `default`, so with switch warnings as errors (`-Wswitch`, MSVC `/w14062`) a new outcome fails the build at every reaction site. | [Strike](Game/Combat.h#L21), [switch](Ui/Hud.cpp#L15-L23) |
| **Single Source of Truth**: continuous state is pulled from data when drawn, never copied into the HUD, so it cannot go stale; only one-shot facts travel as outcomes. | [Draw](Ui/Hud.cpp#L7-L11), [main.cpp#L21](main.cpp#L21) |
| **End of life by judgement**: `BattleEnd` and `QuestEnd` read data and decide; the app ends the scope, so the next monster is a new object and nothing is struck after death (see `valid-by-construction/online-match`). | [BattleEnd](Game/Combat.h#L24-L36), [QuestEnd](Game/QuestEnd.h#L9-L21), [scopes](main.cpp#L16-L24) |
| **Dependency injection over hardcoding**: the HUD writes to an injected stream, not a global; literals appear only in the demo data. | [Hud](Ui/Hud.h#L14), [#L21](Ui/Hud.h#L21), [main.cpp#L13-L14](main.cpp#L13-L14) |
| **No Primitive Obsession**: health, damage and kill counts are `HitPoints` and `Kills`. | [HitPoints](Data/Monster.h#L5-L20), [Kills](Data/Quest.h#L5-L16) |
| **Self-documenting code**: names, types and outcomes carry the whole contract, so nothing here needs a comment. | [Combat.h](Game/Combat.h#L10-L22) |

Callbacks imposed by a framework (input, collision) stay at the boundary: the adapter calls into the game logic and fans out the returned outcome.

## Illustrative only

Hit points, damage and the kill target are demo data, not rules.
