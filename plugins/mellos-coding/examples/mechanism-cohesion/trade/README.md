# Mechanism Cohesion: Trade

**Applies when:** an operation mutates several objects, or inverse operations come in pairs.

A trade mutates both `Player` and `Shop` and belongs to neither. Splitting it across the two classes leads to *Shotgun Surgery* and *Feature Envy*; here the whole mechanism lives in one `.h/.cpp` pair under one scope.

| Layer | Files |
|---|---|
| Data | [Item.h](Item.h), [Gold.h](Gold.h), [Player.h](Player.h), [Shop.h](Shop.h) |
| Mechanism | [Trade.h](Trade.h), [Trade.cpp](Trade.cpp) |
| Demo | [main.cpp](main.cpp) |

## Benefits

| Benefit | Where |
|---|---|
| **Atomicity**: every precondition is checked before any write, so the commit cannot fail and no compensating action exists. | [Buy](Trade.cpp#L15-L33), [Sell](Trade.cpp#L39-L57) |
| **Locality of Behaviour**: inverse operations sit side by side with mirrored commits, so any asymmetry shows on one screen. | [Trade.cpp#L30-L33](Trade.cpp#L30-L33) ↔ [#L54-L57](Trade.cpp#L54-L57) |
| **Single Source of Truth**: both pricing rules are defined once. | [`BuybackDivisor`](Trade.cpp#L8), [#L24](Trade.cpp#L24), [#L48](Trade.cpp#L48) |
| **Make illegal states unrepresentable**: `Gold` and `Quantity` replace raw numbers and cannot go negative, and every listing carries its price, so plain data exposes no invalid state; only the invariants spanning objects remain, and `Trade` owns them. | [Gold](Gold.h#L7-L19), [Quantity](Shop.h#L11-L28), [Listing](Shop.h#L30-L35) |
| **Parse, don't validate**: `Spend` and `TakeOne` yield what remains or nothing, so each check and the value to commit are one result. | [Spend](Gold.h#L13-L19), [TakeOne](Shop.h#L17-L22), [Trade.cpp#L20-L32](Trade.cpp#L20-L32) |
| **Exhaustive outcomes**: the result enums list every outcome, and `[[nodiscard]]` forbids ignoring failure. | [Trade.h#L17-L38](Trade.h#L17-L38) |
| **Acyclic Dependencies**: `Player` and `Shop` never reference each other, so no forward declaration or indirection hides the structure. | [Player.h#L3-L4](Player.h#L3-L4), [Shop.h#L3-L4](Shop.h#L3-L4) |
| **Common Closure**: rule changes touch only `Trade.cpp`, and each data type keeps a single reason to change. | [Player.h#L10-L15](Player.h#L10-L15), [Shop.h#L37-L42](Shop.h#L37-L42) |
| **Scoped names**: the mechanism name is the scope, so no names leak and call sites reveal ownership. | [Trade.h#L14](Trade.h#L14), [#L33](Trade.h#L33), [main.cpp#L18](main.cpp#L18) |
| **Stable Dependencies**: the volatile mechanism depends on stable data, never the reverse, so data is reusable and the mechanism replaceable. | [Trade.h#L3-L5](Trade.h#L3-L5) |
| **No speculative abstraction**: no interfaces, callbacks or events; cohesion comes from placement alone. | [Trade.h#L14-L39](Trade.h#L14-L39) |

Interactions with other mechanisms belong on the same page as well.

## Illustrative only

Half-price buyback and single-item trades are demo choices, not rules.
