# custom_fee 中文文档

本目录存放 `custom_fee` 的中文文档集。

## 建议阅读顺序

1. [fee_redesign.md](./fee_redesign.md)
2. [fee_API.md](./fee_API.md)
3. [fee_onflash_format.md](./fee_onflash_format.md)
4. [fee_boot_recovery.md](./fee_boot_recovery.md)
5. [fee_scheduler_gc.md](./fee_scheduler_gc.md)
6. [fee_cache_checkpoint.md](./fee_cache_checkpoint.md)
7. [fee_cfg_rules.md](./fee_cfg_rules.md)
8. [fee_port_adapter.md](./fee_port_adapter.md)
9. [fee_diag_test.md](./fee_diag_test.md)

## 文档说明

- `fee_redesign.md`：总设计、目标、架构和实施阶段建议
- `fee_API.md`：对外 API 语义、接入方式和常见误区
- `fee_onflash_format.md`：sector / record / checkpoint 落盘格式
- `fee_boot_recovery.md`：启动恢复、checkpoint 恢复和 tail scan
- `fee_scheduler_gc.md`：请求调度、`BUSY_INTERNAL` 语义和 GC 策略
- `fee_cache_checkpoint.md`：RAM cache、checkpoint 触发和 tail 上界
- `fee_cfg_rules.md`：block 配置、lane 映射和容量规划规则
- `fee_port_adapter.md`：底层 flash 适配边界
- `fee_diag_test.md`：诊断测试、dump 解读和性能观察
