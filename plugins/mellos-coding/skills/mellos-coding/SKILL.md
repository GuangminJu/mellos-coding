---
name: mellos-coding
description: "按 Mellos 规范设计、实现、重构和审查代码，只加载适用规则。"
---

# Mellos Coding

先读项目，业务含义不清时确认。按场景读取：

- 编码与审查：[分层与组合](references/layering.md)。
- 错误处理与可读性：[错误前置、禁止擅加兜底](references/error-design.md)。
- 涉及类内多状态：[多状态设计](references/multi-state.md)，必须遵循。
- 替换或更新已持有的状态、资源：[事务式更新](references/transactional-update.md)，必须遵循。

只做当前需求，验证改动并简述结果。案例按需读取，不把单个案例推广为全局要求。
