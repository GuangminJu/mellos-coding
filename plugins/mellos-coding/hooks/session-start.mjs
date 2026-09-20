import { readFileSync } from "node:fs";

const additionalContext = readFileSync(new URL("session-start.md", import.meta.url), "utf8").trim();

process.stdout.write(
  JSON.stringify({ hookSpecificOutput: { hookEventName: "SessionStart", additionalContext } })
);
