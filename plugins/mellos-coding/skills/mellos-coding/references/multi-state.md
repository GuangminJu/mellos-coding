# 类内多状态

适用：所有类内多状态设计，包括互斥或反复进入的状态。

- **Begin**：启动输入。
- **Running**：运行数据、执行和资源收尾；不依赖具体 End。
- **End**：独立、只读地判断 Running；满足返回结果（只能由该判定产生），否则返回空。查询可重复且无副作用，多个 End 可同时成立，结果成立不自动结束运行。
- **外部编排**：负责调度、切换及结果消费；一次性通知按每轮运行去重。
- 已有运行事实足够时，新增 End 不修改 Running。不得用单体枚举或标志分支代替职责分离。
- 强制职责分离；命名、指针和调度可适配，保留业务语义。并发读取须一致，结果及资源生命周期须有效。

按需查看：[参考实现](../assets/examples/multi-state/progress-work/progress_work.hpp) · [调用示例](../assets/examples/multi-state/progress-work/progress_work.cpp)。示例阈值不构成通用业务规则。
