# FEE Scheduler And GC 设计

## 1. 目的

本文档冻结 FEE 的请求调度、后台 GC 和 `BUSY_INTERNAL` 语义。

目标是同时满足：

- `FAST` 请求低尾时延
- `Read/Write/Invalidate` 在 `BUSY_INTERNAL` 下可受理
- checkpoint 与 GC 都是后台任务，不抢走读请求的确定性

## 2. 调度原则

1. 同一时刻只允许 1 个底层 flash job 在执行。
2. `FAST` 用户请求优先于后台任务。
3. cache 已命中的 `read` 优先于 checkpoint 与 GC。
4. checkpoint 与 GC 都属于背景流量，只能在没有更高优先级用户请求时推进。
5. 多 lane GC 采用 round-robin，避免饥饿。

## 3. 请求分级

建议把请求分成四类，而不是把所有内容塞进一个 normal queue。

| 级别 | 类型 | 说明 |
| --- | --- | --- |
| `READ_FAST_PATH` | cache 已命中读 | 优先于 checkpoint / GC |
| `URGENT_QUEUE` | `FAST` write / invalidate / rollback | immediate 语义 |
| `NORMAL_QUEUE` | `NORMAL/BULK` write / invalidate / rollback | 普通用户请求 |
| `BACKGROUND` | checkpoint / GC / 擦除清理 | 仅空闲时推进 |

## 4. `BUSY_INTERNAL` 语义

### 4.1 设计结论

`BUSY_INTERNAL` 表示模块内部正在做 checkpoint / GC / recovery 的后台工作，不等价于拒绝新请求。

### 4.2 受理规则

| 请求 | `MEMIF_BUSY_INTERNAL` 下行为 |
| --- | --- |
| `Read` | 允许受理；cache 命中时优先调度 |
| `FAST Write` | 允许受理；进入 `URGENT_QUEUE` |
| `NORMAL/BULK Write` | 允许受理；进入 `NORMAL_QUEUE` |
| `Invalidate` | 允许受理；按所属 lane 入队 |
| `Rollback` | 允许受理；与同块写请求串行 |

不允许做的事：

- 后台 GC 运行时一刀切拒绝所有 API
- checkpoint 长时间压住 cache-hit read

## 5. 主调度流程

推荐主调度伪代码如下：

```c
void fee_mainfunction(void)
{
    fee_port_mainfunction();

    if (fee_port_get_status() == MEMIF_BUSY)
    {
        return;
    }

    if (read_fast_pending())
    {
        dispatch_read_fast();
        return;
    }

    if (urgent_queue_not_empty())
    {
        dispatch_urgent_request();
        return;
    }

    if (normal_queue_not_empty())
    {
        dispatch_normal_request();
        return;
    }

    if (checkpoint_force_due())
    {
        dispatch_checkpoint();
        return;
    }

    if (gc_force_pending())
    {
        dispatch_force_gc_lane();
        return;
    }

    if (checkpoint_bg_due())
    {
        dispatch_checkpoint();
        return;
    }

    if (gc_bg_pending())
    {
        dispatch_gc_round_robin();
        return;
    }
}
```

## 6. Read 路径

### 6.1 cache 命中读

如果 `block_id` 在 RAM cache 中命中，且模块初始化状态允许读：

1. 直接解析物理地址
2. 若底层硬件空闲，则优先发起 read
3. 若底层硬件忙，则挂入 `read_fast_pending`
4. 下一个空闲点优先于 checkpoint / GC 调度

### 6.2 cache 未命中读

cache 未命中通常说明：

- 模块未 full-ready
- block 从未写入
- cache 损坏或配置错误

此时不允许走“临时全盘扫描”补救，避免读时长尾。应返回：

- `BUSY`，若尚未完成恢复
- `INVALID/INCONSISTENT`，若恢复已完成但无有效副本

## 7. GC 调度

### 7.1 触发级别

每个 lane 独立维护：

- `gc_requested`
- `gc_force`
- `gc_in_progress`

### 7.2 步进约束

每次 `fee_mainfunction()` 对单个 lane 最多推进一项工作：

1. 搬运 1 个 live block
2. 或写 1 个 sector header
3. 或轮询 1 个 erase job

不允许在一个周期内完成“整扇区扫描 + 多块搬迁”。

### 7.3 lane 优先级

建议背景 GC 的优先级为：

1. `FAST lane` 的 `gc_force`
2. `NORMAL lane` 的 `gc_force`
3. `BULK lane` 的 `gc_force`
4. 其余 `gc_requested` round-robin

## 8. 公平性规则

1. `NORMAL/BULK` 用户请求等待超过阈值时，后台任务停止插队
2. `FAST` 请求可以抢占未开始的后台任务，但不能打断已发起的 flash job
3. 同一 block 的 `write/invalidate/rollback` 必须串行
4. checkpoint 连续占用周期数达到阈值后，必须让出执行权

## 9. GC 状态机

建议状态：

```text
GC_IDLE
  -> GC_REQUESTED
  -> GC_PREPARE_DST
  -> GC_COPY_ONE
  -> GC_SWITCH_COMMIT
  -> GC_OLD_PENDING_ERASE
  -> GC_FINISH
  -> GC_IDLE
```

说明：

- `GC_PREPARE_DST`: 擦除并提交目标扇区 header
- `GC_COPY_ONE`: 搬运单块 live data
- `GC_SWITCH_COMMIT`: 提升新扇区、降级旧扇区
- `GC_OLD_PENDING_ERASE`: 后台擦除旧扇区

## 10. checkpoint 与 GC 的关系

1. lane 角色切换完成后应尽快触发 checkpoint
2. checkpoint 未完成前，不影响新 `ACTIVE` 扇区继续写入
3. 若 checkpoint 长期落后，运行期必须通过 `checkpoint_force_due()` 纠偏

## 11. 建议接口

```c
void fee_sched_mainfunction(void);
Std_ReturnType fee_sched_submit_read(...);
Std_ReturnType fee_sched_submit_write(...);
Std_ReturnType fee_sched_submit_invalidate(...);
Std_ReturnType fee_sched_submit_rollback(...);
boolean fee_sched_has_background_work(void);
```

## 12. 测试关注点

- checkpoint 到期时 cache-hit read 仍优先
- `FAST` 写入插队 `NORMAL` lane GC
- `NORMAL` 长时间积压时后台任务让路
- `gc_force` 与 `gc_requested` 的优先级
- 同一 block 的 `write + rollback` 串行化
