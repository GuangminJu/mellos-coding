import { readdirSync, readFileSync } from "node:fs";
import { join } from "node:path";
import { fileURLToPath } from "node:url";

const examplesRoot = fileURLToPath(new URL("../examples/", import.meta.url));

function listDirectories(path) {
  return readdirSync(path, { withFileTypes: true })
    .filter((entry) => entry.isDirectory())
    .map((entry) => entry.name);
}

function describeCase(topic, name) {
  const readme = readFileSync(join(examplesRoot, topic, name, "README.md"), "utf8");
  const title = readme.match(/^# (.+)$/m);
  const appliesWhen = readme.match(/^\*\*Applies when:\*\* (.+)$/m);
  if (!title || !appliesWhen)
    throw new Error(`${topic}/${name}/README.md needs a "# Title" line and an "**Applies when:**" line`);
  return `- ${topic}/${name}: ${title[1]}. Applies when ${appliesWhen[1]}`;
}

const cases = listDirectories(examplesRoot).flatMap((topic) =>
  listDirectories(join(examplesRoot, topic)).map((name) => describeCase(topic, name)));

const additionalContext = [
  "The user keeps reference code cases showing how they want code designed (Mellos Coding).",
  "Before writing or changing code, consult them. How deep to go is your call: this list may be enough, or read a case's README, or study its code before editing.",
  "",
  `Examples root: ${examplesRoot}`,
  ...cases,
].join("\n");

process.stdout.write(
  JSON.stringify({ hookSpecificOutput: { hookEventName: "SessionStart", additionalContext } })
);
