# Ownership Transfer: Background Bake

**Applies when:** work runs on another thread, and data or results must cross between threads.

A lightmap is baked on a worker thread. The scene is given to the worker by value, the result comes back by value, and nothing is ever held by two threads at once, so there is no shared mutable state and no lock.

| Role | Files |
|---|---|
| Data | [Lightmap.h](Lightmap.h) |
| Mechanism | [Baker.h](Baker.h), [Baker.cpp](Baker.cpp) |
| Demo | [main.cpp](main.cpp) |
| Verification | [background_bake_compile.cpp](background_bake_compile.cpp) |

## Benefits

| Benefit | Where |
|---|---|
| **Explicit threading model**: the name and the launch policy say where the work runs; the synchronous `Bake` is the whole computation and knows nothing about threads. | [BakeOnWorkerThread](Baker.cpp#L15-L18), [Bake](Baker.cpp#L7-L13) |
| **Ownership in, value out**: `Bake` takes `Scene` by value and `Scene` cannot be copied, so calling it means giving the scene away; the result is a plain value collected once through the future. | [Scene](Lightmap.h#L13-L27), [Baker.h#L14-L15](Baker.h#L14-L15), [get](main.cpp#L14) |
| **No shared mutable state**: neither thread can reach the other's data, so there is no mutex, atomic or condition variable to get wrong; the single synchronisation point is `get`. | [main.cpp#L10-L15](main.cpp#L10-L15) |
| **Make illegal states unrepresentable**: sharing is ruled out by the deleted copy, not by discipline, and the compile check pins it. | [Lightmap.h#L18-L21](Lightmap.h#L18-L21), [check](background_bake_compile.cpp#L9-L10) |
| **State stays with its owner thread**: the main thread keeps its own work while the bake runs; the worker owns only its input and its output, and the result is installed by whoever collects it. | [main.cpp#L12-L15](main.cpp#L12-L15) |
| **Callbacks at the boundary only**: the thread entry is the one function handed to the runtime, inside the mechanism; callers see objects and values (see `explicit-reactions/monster-hit`). | [Baker.cpp#L17](Baker.cpp#L17) |
| **Tests as specification**: each check names the guarantee it pins: one owner, a value result, a single collection. | [background_bake_compile.cpp#L9-L13](background_bake_compile.cpp#L9-L13) |
| **Self-documenting code**: the two signatures state the whole contract, so nothing here needs a comment. | [Baker.h#L9-L16](Baker.h#L9-L16) |

The future's destructor waits for the worker, so a dropped result still joins; blocking there is the price of never leaking a thread.

## Illustrative only

Summing lumens stands in for a real bake, and one thread per call is a demo choice, not a scheduling policy.
