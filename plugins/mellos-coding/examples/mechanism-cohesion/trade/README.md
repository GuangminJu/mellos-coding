# Mechanism Cohesion: Trade

**Applies when:** an operation mutates several objects, or inverse operations come in pairs.

A trade mutates both `Player` and `Shop` and belongs to neither. Splitting it across the two classes leads to *Shotgun Surgery* and *Feature Envy*; here the whole mechanism lives in one `.h/.cpp` pair under one scope.

| Layer | Files |
|---|---|
| Data | [Item.h](Item.h), [Player.h](Player.h), [Shop.h](Shop.h) |
| Mechanism | [Trade.h](Trade.h), [Trade.cpp](Trade.cpp) |
| Demo | [main.cpp](main.cpp) |

## Benefits

| Benefit | Where |
|---|---|
| **Atomicity**: every precondition is checked before any write, so the commit cannot fail and no compensating action exists. | [Buy](Trade.cpp#L15-L28), [Sell](Trade.cpp#L34-L51) |
| **Locality of Behaviour**: inverse operations sit side by side with mirrored commits, so any asymmetry shows on one screen. | [Trade.cpp#L25-L28](Trade.cpp#L25-L28) ↔ [#L48-L51](Trade.cpp#L48-L51) |
| **Single Source of Truth**: both pricing rules are defined once. | [`BuybackDivisor`](Trade.cpp#L8), [#L20](Trade.cpp#L20), [#L43](Trade.cpp#L43) |
| **Exhaustive outcomes**: the result enums list every outcome, and `[[nodiscard]]` forbids ignoring failure. | [Trade.h#L17-L38](Trade.h#L17-L38) |
| **Acyclic Dependencies**: `Player` and `Shop` never reference each other, so no forward declaration or indirection hides the structure. | [Player.h#L3](Player.h#L3), [Shop.h#L3](Shop.h#L3) |
| **Common Closure**: rule changes touch only `Trade.cpp`, and each data type keeps a single reason to change. | [Player.h#L9-L14](Player.h#L9-L14), [Shop.h#L15-L20](Shop.h#L15-L20) |
| **Scoped names**: the mechanism name is the scope, so no names leak and call sites reveal ownership. | [Trade.h#L14](Trade.h#L14), [#L33](Trade.h#L33), [main.cpp#L18](main.cpp#L18) |
| **Stable Dependencies**: the volatile mechanism depends on stable data, never the reverse, so data is reusable and the mechanism replaceable. | [Trade.h#L3-L5](Trade.h#L3-L5) |
| **No speculative abstraction**: no interfaces, callbacks or events; cohesion comes from placement alone. | [Trade.h#L14-L39](Trade.h#L14-L39) |

Interactions with other mechanisms belong on the same page as well.

## Illustrative only

Half-price buyback, single-item trades and `unsigned` gold are demo choices, not rules.
