# 事务式更新

适用：替换或更新对象已持有的状态、资源。

- **Verify**：只读检查运行时事实，失败即返回；编译期可确定的约束由参数类型保证，此处不重复。
- **Prepare**：在局部完整构造新状态，不触碰现有状态；失败时原状态不变。
- **Commit**：只做不会失败的交换（swap/move），不含检查；旧状态随局部对象释放。

按需查看：[参考实现](../assets/examples/transactional-update/type-safe-reload/Type-Safe_Transactional_Update.cpp)。示例中的 `Invalid` 判定只是演示，不构成业务规则。
