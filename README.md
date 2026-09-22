# Mellos Coding

可扩充的通用 AI 编码规范插件。规范极简，代码案例独立存放、按需读取。

- [编码入口](plugins/mellos-coding/skills/mellos-coding/SKILL.md)
- [分层与组合](plugins/mellos-coding/skills/mellos-coding/references/layering.md)
- [错误与函数可读性](plugins/mellos-coding/skills/mellos-coding/references/error-design.md)
- [多状态设计](plugins/mellos-coding/skills/mellos-coding/references/multi-state.md)
- [事务式更新](plugins/mellos-coding/skills/mellos-coding/references/transactional-update.md)
- [收录案例](plugins/mellos-coding/skills/add-code-example/SKILL.md)
- [维护约定](docs/rule-authoring.md)

## 安装

Claude Code：

```sh
claude plugin marketplace add GuangminJu/mellos-coding
claude plugin install mellos-coding@mellos-coding
```

新会话使用 `/mellos-coding:mellos-coding`，收录案例用 `/mellos-coding:add-code-example`。会话启动时插件会注入 `plugins/mellos-coding/hooks/session-start.md` 一段话，要求编码前先加载规范技能；规范正文仍按需读取。

Codex：

```sh
codex plugin marketplace add GuangminJu/mellos-coding --ref main
codex plugin add mellos-coding@mellos-coding
```

新任务使用 `$mellos-coding`。

## 更新

Claude Code：

```sh
claude plugin marketplace update mellos-coding
claude plugin update mellos-coding
```

Codex：

```sh
codex plugin marketplace upgrade mellos-coding
codex plugin add mellos-coding@mellos-coding
```

更新后新建会话使用。

## 维护

提供代码并说“加入 Mellos Coding”，在可写的开发源码中收录案例、更新规范。对外发布时将验证后的变更提交并推送到 `main`；使用者按上面的命令获取更新。

维护者把本地市场指向开发源码后，用对应宿主的脚本更新本机安装：

```powershell
.\scripts\update-claude-plugin.ps1   # Claude Code，只需 Claude Code CLI
.\scripts\update-plugin.ps1          # Codex，需要 Codex CLI、Python 及插件/技能辅助工具
```

两个脚本都只用于本地开发，不负责发布 GitHub。版本号是插件内容的唯一标识，三个清单（`.claude-plugin/plugin.json`、`.claude-plugin/marketplace.json`、`.codex-plugin/plugin.json`）必须一致，由脚本推进；Claude Code 只在版本变化时才重新拷贝插件。

Claude Code 首次指向开发源码：

```powershell
claude plugin marketplace add <本仓库路径>
claude plugin install mellos-coding@mellos-coding
```

`progress_work.cpp` 只演示业务流程；开发期验证独立放在 `tests/progress_work_compile.cpp`，通过 C++17 编译时的 `static_assert` 执行。
