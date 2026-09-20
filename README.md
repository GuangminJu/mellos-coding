# Mellos Coding

可扩充的通用 AI 编码规范插件。规范极简，代码案例独立存放、按需读取。

- [编码入口](plugins/mellos-coding/skills/mellos-coding/SKILL.md)
- [分层与组合](plugins/mellos-coding/skills/mellos-coding/references/layering.md)
- [错误与函数可读性](plugins/mellos-coding/skills/mellos-coding/references/error-design.md)
- [多状态设计](plugins/mellos-coding/skills/mellos-coding/references/multi-state.md)
- [收录案例](plugins/mellos-coding/skills/add-code-example/SKILL.md)
- [维护约定](docs/rule-authoring.md)

## 安装

安装 Codex CLI 后执行：

```sh
codex plugin marketplace add GuangminJu/mellos-coding --ref main
codex plugin add mellos-coding@mellos-coding
```

新任务使用 `$mellos-coding`。

## 更新

```sh
codex plugin marketplace upgrade mellos-coding
codex plugin add mellos-coding@mellos-coding
```

更新后新建任务使用。

## 维护

提供代码并说“加入 Mellos Coding”，在可写的开发源码中收录案例、更新规范。对外发布时将验证后的变更提交并推送到 `main`；使用者按上面的命令获取更新。

维护者已有个人市场指向本地源码时，用以下命令更新本机安装：

```powershell
.\scripts\update-plugin.ps1
```

此脚本仅用于本地开发，不负责发布 GitHub；需要 Codex CLI、Python 及插件/技能辅助工具。

`progress_work.cpp` 只演示业务流程；开发期验证独立放在 `tests/progress_work_compile.cpp`，通过 C++17 编译时的 `static_assert` 执行。
