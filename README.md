# Mellos Coding

Personal reference code cases for Claude Code. At session start a hook lists every case with its title and when it applies; before writing code, the AI consults them as deeply as it judges useful.

## Cases

Each case is a folder `plugins/mellos-coding/examples/<topic>/<case>/` holding the code and a `README.md`. The hook reads two lines from that README, so both are required:

```markdown
# <Topic>: <Case>

**Applies when:** <the situation this case covers>.
```

The rest of the README names the net benefits in established terms, each linked to the lines that embody it, and marks demo-only details as illustrative.

## Install

```sh
claude plugin marketplace add GuangminJu/mellos-coding
claude plugin install mellos-coding@mellos-coding
```

## Publish

Add or edit a case folder, commit, and push to `main`. The manifests carry no version, so the installed version is the commit SHA; after a new commit, `claude plugin update mellos-coding@mellos-coding` (or marketplace auto-update) installs it, and it applies in the next session. Uncommitted edits are not picked up, even from a local-path marketplace.
