# 规范维护

- **必须极简**：每页只写适用条件、必要约束和案例链接，不写教程、重复解释或通用常识。
- 同主题补已有页，新主题放主技能的 `references/<topic>.md` 并添加入口链接；正文只维护一份。
- [收录案例](../plugins/mellos-coding/skills/add-code-example/SKILL.md)时保留原文，区分推荐写法、反例和修正版；未确认的解释不设为强制规则。
- 代码独立存放，按需读取；只验证受影响的内容。
- 验证后运行 `scripts/update-plugin.ps1` 更新 Codex，确认安装状态；不编辑缓存。
