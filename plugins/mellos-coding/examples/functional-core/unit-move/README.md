# Functional Core: Unit Move

**Applies when:** writing the lowest layer of a behaviour (movement, damage, pricing), and when the same step must serve several owners, be previewed without side effects, or run for many instances.

The natural design makes the unit an entity that moves itself: position, target and `Update` in one class, never copied. Here the unit is a value and nothing moves itself: the step is a pure function of values, and whoever owns a position decides when to call it and when it has arrived. The split feels wrong and composes freely; the entity feels right and composes once.

| Role | Files |
|---|---|
| Values | [Units.h](Units.h) |
| Functional core: the step | [Motion.h](Motion.h) |
| Imperative shell: owners and judgement | [Owners.h](Owners.h) |
| Demo, including a preview | [main.cpp](main.cpp) |
| Verification | [unit_move_compile.cpp](unit_move_compile.cpp) |
| Natural counter-example | [natural_mover.cpp](natural_mover.cpp): an entity that moves itself; it is tidy, and the uses below have no clean answer |

## Benefits

| Benefit | Where |
|---|---|
| **Functional core**: the step takes values and returns a value; it holds nothing, so it is the same step for every owner, every instance and every hypothetical. | [Approach](Motion.h#L12-L21), [no state](unit_move_compile.cpp#L27) |
| **Units are values, not entities**: an owner is built from values and a pure step, so it has no identity to protect; it can be copied and ticked ahead, and a forecast and the real run are provably the same. The entity forbids exactly this. | [AfterTicks](unit_move_compile.cpp#L9-L14), [#L31-L33](unit_move_compile.cpp#L31-L33), [deleted copy](natural_mover.cpp#L9) |
| **State at the top**: position, destination and the turnaround rule live in the owners; the step never knows whose position it moves. | [Journey](Owners.h#L10-L27), [Patrol::Tick](Owners.h#L51-L56) |
| **Free composition**: `Journey` and `Patrol` are the same step assembled two ways, and `Motion` did not change; the entity needs a target setter, a direction flag and a second branch in `Update` for the patrol. | [Owners.h#L18](Owners.h#L18), [#L53-L55](Owners.h#L53-L55), [Update](natural_mover.cpp#L11-L21) |
| **Preview without side effects**: "where in three seconds" is the step called with a hypothetical delta; nothing moves, nothing is copied or undone. The entity's `Update` can only answer by moving the unit, and the entity cannot be copied. | [main.cpp#L16](main.cpp#L16), [counter-example](natural_mover.cpp#L32) |
| **End of life by judgement**: `ArrivalEnd` reads the journey and the owner ends the scope (see `valid-by-construction/online-match`); `Patrol` has no end and needs none. | [ArrivalEnd](Owners.h#L29-L41), [loop](main.cpp#L17-L21) |
| **Determinism**: the physics is pinned at compile time without constructing a unit: one tick, no overshoot, both directions. | [unit_move_compile.cpp#L28-L30](unit_move_compile.cpp#L28-L30) |
| **No Primitive Obsession**: `Position`, `Speed` and `Millis` carry the units, so a step cannot mix seconds with milliseconds. | [Units.h#L5-L39](Units.h#L5-L39) |
| **Tests as specification**: each check is named by the guarantee it pins, including that the turnaround rule lives in the owner. | [unit_move_compile.cpp#L27-L35](unit_move_compile.cpp#L27-L35) |
| **Self-documenting code**: the step's signature is the whole contract, so nothing here needs a comment. | [Motion.h#L7-L22](Motion.h#L7-L22) |

`Player` in `valid-by-construction/online-match` and `Running` in `multi-state/progress-work` are owners in this sense: each composes a pure step (`Position::Next`, `Steps::Next`) with what it holds.

## Illustrative only

Movement along one axis in whole centimetres is a demo choice; a real step normalises a direction and takes floating-point time at the same layer.
