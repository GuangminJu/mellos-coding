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
| **Atomicity**: every precondition is checked before any write, so the commit cannot fail and no compensating action exists. | [Buy](Trade.cpp#L12-L29), [Sell](Trade.cpp#L35-L52) |
| **Locality of Behaviour**: inverse operations sit side by side with mirrored commits, so any asymmetry shows on one screen. | [Trade.cpp#L26-L29](Trade.cpp#L26-L29) ↔ [#L49-L52](Trade.cpp#L49-L52) |
| **Single Source of Truth**: both pricing rules are defined once. | [`BuybackDivisor`](Trade.cpp#L7), [#L21](Trade.cpp#L21), [#L44](Trade.cpp#L44) |
| **Make illegal states unrepresentable**: `Gold` and `Quantity` replace raw numbers and cannot go negative, and every listing carries its price, so plain data exposes no invalid state; only the invariants spanning objects remain, and `Trade` owns them. | [Gold](Gold.h#L7-L25), [Quantity](Shop.h#L11-L27), [Listing](Shop.h#L29-L33) |
| **Parse, don't validate**: `Spend` and `TakeOne` yield what remains or nothing, so each check and the value to commit are one result. | [Spend](Gold.h#L12-L17), [TakeOne](Shop.h#L16-L21), [Trade.cpp#L17-L28](Trade.cpp#L17-L28) |
| **Exhaustive outcomes**: the result enums list every outcome, and `[[nodiscard]]` forbids ignoring failure. | [Trade.h#L12-L30](Trade.h#L12-L30) |
| **Acyclic Dependencies**: `Player` and `Shop` never reference each other, so no forward declaration or indirection hides the structure. | [Player.h#L3-L4](Player.h#L3-L4), [Shop.h#L3-L4](Shop.h#L3-L4) |
| **Common Closure**: rule changes touch only `Trade.cpp`, and each data type keeps a single reason to change. | [Player.h#L10-L14](Player.h#L10-L14), [Shop.h#L35-L39](Shop.h#L35-L39) |
| **Scoped names**: the mechanism name is the scope, so no names leak and call sites reveal ownership. | [Trade.h#L9](Trade.h#L9), [#L27](Trade.h#L27), [main.cpp#L18](main.cpp#L18) |
| **Stable Dependencies**: the volatile mechanism depends on stable data, never the reverse, so data is reusable and the mechanism replaceable. | [Trade.h#L3-L5](Trade.h#L3-L5) |
| **No speculative abstraction**: no interfaces, callbacks or events; cohesion comes from placement alone. | [Trade.h#L9-L31](Trade.h#L9-L31) |
| **Self-documenting code**: names, types and result enums carry the whole contract, so nothing here needs a comment. | [Trade.h#L9-L31](Trade.h#L9-L31) |

Interactions with other mechanisms belong on the same page as well.

## Illustrative only

Half-price buyback and single-item trades are demo choices, not rules.
