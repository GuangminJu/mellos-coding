# 持有即可用

适用：设计对象的创建、依赖、生命周期与阶段切换。

- 能取得的对象即可用，能调用的函数即该调用：不设 `Init`、`IsValid`、半构造或失效状态，依赖全部在构造参数中。
- 可能失败的获取只在边界发生一次，返回可空结果；取得后不再检查。
- 被借用者的作用域包住借用者，以引用持有；成员声明顺序即构造顺序，析构自动逆序。
- 阶段切换靠构造下一阶段的对象，不靠标志位或调用顺序约定。
- 使对象失去意义的运行事实由 End 判定（[多状态设计](multi-state.md)），所有者据此结束作用域。

按需查看：[参考实现](../assets/examples/valid-by-construction/online-match/online_match.hpp) · [调用示例](../assets/examples/valid-by-construction/online-match/online_match.cpp)。示例中的 `unreachable` 判定和关卡数据只是演示，不构成业务规则。
