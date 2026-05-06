# custom_fee

`custom_fee` 是一个面向嵌入式场景的固定逻辑块 Flash EEPROM Emulation
（FEE）组件。它针对的是可预测的块存储，而不是通用 KV 数据库，核心目标是
提供追加写、基于 checkpoint 的快速恢复，以及后台 GC 整理能力。

## 当前已实现范围

当前代码树已经包含该组件的主要控制流程和数据模型骨架：

- [fee_api.h](./fee_api.h) / [fee_api.c](./fee_api.c)：对外 API 入口
- [fee_sched.c](./fee_sched.c)：请求分级和前后台调度
- [fee_core.c](./fee_core.c)：读、写、失效、回滚和记录校验
- [fee_cache.c](./fee_cache.c) / [fee_ckpt.c](./fee_ckpt.c)：RAM cache 与 checkpoint
- [fee_recovery.c](./fee_recovery.c)：上电恢复、tail scan、GC 中断恢复
- [fee_gc.c](./fee_gc.c)：增量 GC 状态推进
- [fee_onflash.h](./fee_onflash.h) / [fee_onflash.c](./fee_onflash.c)：落盘格式辅助逻辑
- [fee_cfg.h](./fee_cfg.h) / [fee_cfg.c](./fee_cfg.c)：静态 block 和 lane 配置

## 组件功能特征

当前实现围绕以下能力展开：

- 基于 `block_id` 的块访问模型
- 同步读，异步排队的写入、失效和回滚
- 当前副本与上一副本并存，支持回滚和容错恢复
- 初始化完成后优先走 RAM cache，而不是每次读都全盘扫描
- 通过 checkpoint 缩短启动恢复时间
- `FAST` / `NORMAL` / `BULK` lane 隔离
- 通过 `fee_mainfunction()` 推进后台 GC 和 checkpoint
- 结合提交标记和 CRC 做掉电一致性判定

## 对外 API

当前对业务层暴露的接口定义在 [fee_api.h](./fee_api.h)：

```c
fee_ret_t fee_init(void);
fee_ret_t fee_read(uint16_t block_id, uint16_t offset, uint8_t *dst, uint16_t len);
fee_ret_t fee_write(uint16_t block_id, const uint8_t *src, uint16_t len);
fee_ret_t fee_invalidate(uint16_t block_id);
fee_ret_t fee_get_status(uint16_t block_id, fee_block_status_t *status);
fee_ret_t fee_rollback(uint16_t block_id);
void fee_mainfunction(void);

fee_status_t fee_get_memif_status(void);
fee_job_result_t fee_get_job_result(void);
fee_init_state_t fee_get_init_state(void);
```

## 文档入口

- [doc/README.md](./doc/README.md)：文档总索引
- [doc/zh/README.md](./doc/zh/README.md)：中文版文档
- [doc/en/README.md](./doc/en/README.md)：英文版文档

建议从以下文档开始阅读：

- 架构与总体设计：
  [doc/zh/fee_redesign.md](./doc/zh/fee_redesign.md)
- 对外接口与接入方式：
  [doc/zh/fee_API.md](./doc/zh/fee_API.md)
- 诊断测试与结果解读：
  [doc/zh/fee_diag_test.md](./doc/zh/fee_diag_test.md)

## 当前仓库状态

当前仓库更接近一个可集成的实现集合，还不是可直接量产落地的完整版本。

- 核心 FEE 逻辑和设计文档已经具备。
- 文档中约定了 `fee_port` 适配层和测试后端的集成方式。
- 相关适配层与测试源文件目前不在这个快照里，实际接板仍需要项目侧补齐。

## 快速接入建议

1. 在 [Kconfig](./Kconfig) 中打开组件。
2. 根据目标平台配置 block 表和底层 flash 能力参数。
3. 系统启动时调用 `fee_init()`。
4. 周期性调用 `fee_mainfunction()`。
5. 将 `fee_write()`、`fee_invalidate()`、`fee_rollback()` 视为异步请求，
   并通过状态接口查询最终结果。
