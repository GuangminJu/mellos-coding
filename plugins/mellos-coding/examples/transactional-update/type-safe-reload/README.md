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
| **Strong exception guarantee**: failure returns empty before any holder is touched, so the original state stays intact. | [Load](revised.cpp#L28-L34), [demo](revised.cpp#L72-L74) |
| **No-fail commit**: `Reload` is a `noexcept` swap whose parameter type proves Verify and Prepare are done. | [Reload](revised.cpp#L49-L50) |
| **Valid by construction**: only `Load` can create a `Resource`, and an `Object` always holds one; there is no empty state to check. | [Resource](revised.cpp#L39), [Object](revised.cpp#L47), [#L55](revised.cpp#L55) |
| **RAII ownership**: the old resource is released with the local after the swap. | [Reload](revised.cpp#L50) |
| **Parse, don't validate**: `NonEmptyString` rejects empty literals at compile time, so nothing rechecks it; runtime strings stay the caller's business. | [NonEmptyString](revised.cpp#L6-L23), [counter-example](revised.cpp#L71) |
| **No Primitive Obsession**: `Resource` stores and returns its `NonEmptyString`, so no raw string crosses its interface. | [Resource](revised.cpp#L36), [#L41](revised.cpp#L41) |
| **Runtime checks for runtime facts only**: `Load` checks only dynamic conditions, and failure is returned, not defaulted. | [Load](revised.cpp#L31-L32) |

## Illustrative only

The `Invalid` check is a demo choice, not a business rule.
