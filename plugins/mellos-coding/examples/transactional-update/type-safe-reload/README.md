# Transactional Update: Type-Safe Reload

**Applies when:** replacing or updating state or resources an object already holds.

An object replaces a held resource through Verify (read-only) → Prepare (build locally) → Commit (no-fail swap). In the revision, `Resource::Load` performs Verify and Prepare, so `Reload` accepts only a finished `Resource` and can do nothing but commit.

| Role | Files |
|---|---|
| Revision (reference) | [revised.cpp](revised.cpp) |
| Original | [Type-Safe_Transactional_Update.cpp](Type-Safe_Transactional_Update.cpp): all three steps inside `Reload`, and the object may hold no resource |

## Benefits

| Benefit | Where |
|---|---|
| **Strong exception guarantee**: failure returns empty before any holder is touched, so the original state stays intact. | [Load](revised.cpp#L43-L48), [demo](revised.cpp#L87-L89) |
| **No-fail commit**: `Reload` is a `noexcept` swap whose parameter type proves Verify and Prepare are done. | [Reload](revised.cpp#L63) |
| **Valid by construction**: only `Load` can create a `Resource`, and an `Object` always holds one; there is no empty state to check. | [Resource](revised.cpp#L53), [Object](revised.cpp#L61), [#L68](revised.cpp#L68) |
| **RAII ownership**: the old resource is released with the local after the swap. | [Reload](revised.cpp#L63) |
| **Parse, don't validate**: `NonEmptyString` rejects empty literals at compile time, so nothing rechecks it; runtime strings stay the caller's business. | [NonEmptyString](revised.cpp#L7-L26), [counter-example](revised.cpp#L86) |
| **No Primitive Obsession**: `Resource` stores and returns its `NonEmptyString`, so no raw string crosses its interface. | [Resource](revised.cpp#L50), [#L55](revised.cpp#L55) |
| **Dependency injection over hardcoding**: which resources exist comes from an injected `Storage`; literals appear only in the demo data. | [Storage](revised.cpp#L28-L38), [Load](revised.cpp#L43-L46), [demo](revised.cpp#L73) |
| **Runtime checks for runtime facts only**: `Load` asks only whether storage holds the resource, and failure is returned, not defaulted. | [Load](revised.cpp#L45-L46) |
| **Comments only for what code cannot say**: one comment states that storage contents are decided outside the program, and one shows a call that cannot compile. | [#L28](revised.cpp#L28), [#L86](revised.cpp#L86) |

## Illustrative only

The storage contents are demo data, not a business rule.
