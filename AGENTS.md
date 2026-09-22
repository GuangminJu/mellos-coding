# Mellos Coding

这是可扩充的通用 AI 编码规范库，每页负责一类场景。

- **提示词必须极简**：仅保留适用条件、必要约束和案例链接；不写教程、重复解释或通用常识。`hooks/session-start.md` 是会话启动注入的那段话，同样极简，只说"先加载哪个技能"。
- 启动触发按宿主各用一套：Claude Code 靠 `hooks/`，Codex 靠 `agents/openai.yaml` 的 `allow_implicit_invocation`；不要互相复制。
- 先读项目；业务含义不清时确认。重视分层、组合、复用和业务解耦。
- 编码遵循 `plugins/mellos-coding/skills/mellos-coding/references/error-design.md`：可静态确定的错误前置，不擅加兜底，函数主流程清晰。
- 类内多状态遵循 `plugins/mellos-coding/skills/mellos-coding/references/multi-state.md`。
- 替换或更新已持有的状态、资源遵循 `plugins/mellos-coding/skills/mellos-coding/references/transactional-update.md`。
- 插件只读取规范；新增规范或案例按 `docs/rule-authoring.md` 在本仓库完成并发布。
- 只改开发源码；验证后按宿主运行 `scripts/update-claude-plugin.ps1`（Claude Code）或 `scripts/update-plugin.ps1`（Codex）同步已授权的安装，不改缓存。
- 版本号是插件内容的唯一标识，`.claude-plugin/plugin.json`、`.claude-plugin/marketplace.json` 与 `.codex-plugin/plugin.json` 必须一致；同步脚本负责推进它，不要手改。
- 优先文件、命令行与专用工具，仅必要时使用 Computer Use；如实报告验证范围。
