# Boundary Parsing: Server Config

**Applies when:** values from outside the program (config, files, network, command line) enter it, including values that must stay secret.

Config text is parsed once, at the boundary, into typed values or a named error. Everything inside takes `Config` and trusts it: no rechecks, no raw strings, and the secret has no text form, so it cannot be logged.

| Role | Files |
|---|---|
| Values | [Address.h](Address.h), [Port.h](Port.h), [Token.h](Token.h), [Config.h](Config.h) |
| Boundary | [ConfigReader.h](ConfigReader.h) |
| Interior | [Server.h](Server.h) |
| Demo, reporting | [main.cpp](main.cpp) |
| Verification | [server_config_compile.cpp](server_config_compile.cpp) |

## Benefits

| Benefit | Where |
|---|---|
| **Parse, don't validate**: raw text exists only in the reader, and each value type yields itself or nothing, so the check and the value are one result (see `mechanism-cohesion/trade`). | [Parse](ConfigReader.h#L26-L72), [Port::Parse](Port.h#L11-L28), [Token::Parse](Token.h#L11-L16) |
| **Validate at the boundary only**: the reader returns `Config` or a named `Error`; the interior never validates, because every field type already carries its invariant. | [Server](Server.h#L19-L27), [Config](Config.h#L9-L14) |
| **Fail once, with a reason**: a config error names the key at fault, is reported where the sink is, and ends the program before any state exists; a bare `optional` suffices only when there is one way to fail (see `valid-by-construction/online-match`). | [Error](ConfigReader.h#L15-L22), [main.cpp#L37-L43](main.cpp#L37-L43) |
| **Never log secrets**: `Token` exposes only `Matches`; it has no accessor and no stream operator, so a log statement with the secret does not compile, and the compile check pins that. | [Token](Token.h#L8-L24), [counter-example](main.cpp#L48), [check](server_config_compile.cpp#L37) |
| **Configuration externalized and documented**: every environment value comes from the config text, which stands in for a file; the `Config` struct documents each key and its type; literals appear only in the demo data. | [ConfigFile](main.cpp#L10-L11), [Config](Config.h#L9-L14) |
| **No global state**: the config and the log sink are parameters, never a `Config::Get()` or `Logger::Instance()`, so each signature lists what it touches. | [Server](Server.h#L19), [Report](main.cpp#L13), [main.cpp#L40](main.cpp#L40), [#L45](main.cpp#L45) |
| **Exhaustive outcomes**: the error enum lists every way parsing fails, and the report switch has no `default` and returns nothing, so no placeholder value exists (compiler flags: see `explicit-reactions/monster-hit`). | [Error](ConfigReader.h#L15-L22), [Report](main.cpp#L15-L32) |
| **Tests as specification**: each check is named by the behaviour it guarantees, including the negative one that a secret has no text form; all run at compile time. | [server_config_compile.cpp#L11-L39](server_config_compile.cpp#L11-L39) |
| **Scoped borrowing**: `Config` views the text and `Server` views `Config`; each lender outlives its borrower inside `main` (see `valid-by-construction/online-match`). | [Address.h#L23](Address.h#L23), [Server.h#L30](Server.h#L30), [main.cpp#L37-L45](main.cpp#L37-L45) |
| **No Primitive Obsession**: host, port and secret are `Address`, `Port` and `Token`; a raw string never crosses the boundary inward. | [Address](Address.h#L8-L24), [Port](Port.h#L8-L39), [Token](Token.h#L8-L24) |
| **Comments only for what code cannot say**: one states that the text stands in for a file, one shows a line that cannot compile. | [#L10](main.cpp#L10), [#L48](main.cpp#L48) |

## Illustrative only

The `key=value` format, the three keys and the plain comparison of tokens are demo choices; real secrets need constant-time comparison, and real files are read at the same boundary.
