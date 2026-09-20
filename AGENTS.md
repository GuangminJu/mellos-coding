# Mellos Coding

这是可扩充的通用 AI 编码规范库，每页负责一类场景。

- **提示词必须极简**：仅保留适用条件、必要约束和案例链接；不写教程、重复解释或通用常识。
- 先读项目；业务含义不清时确认。重视分层、组合、复用和业务解耦。
- 编码遵循 `plugins/mellos-coding/skills/mellos-coding/references/error-design.md`：可静态确定的错误前置，不擅加兜底，函数主流程清晰。
- 类内多状态遵循 `plugins/mellos-coding/skills/mellos-coding/references/multi-state.md`。
- 用户明确要求收录案例时使用 `plugins/mellos-coding/skills/add-code-example/SKILL.md`，保留原文，勿将示例细节变为通用规则。
- 只改开发源码；验证后运行 `scripts/update-plugin.ps1` 同步已授权的安装，不改缓存。
- 优先文件、命令行与专用工具，仅必要时使用 Computer Use；如实报告验证范围。
