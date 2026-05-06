# FEE Boot Recovery 设计

## 1. 目的

本文档冻结 FEE 的启动恢复策略，重点回答三个问题：

1. 上电后如何尽快恢复 RAM cache
2. 何时允许首个 `read block`
3. checkpoint 失效、GC 中断或格式异常时如何降级

## 2. 设计目标

- 在 checkpoint 有效时，启动时间与 tail 大小相关，而不是与历史记录总量相关
- `boot_critical` block 尽早可读
- 恢复路径对 GC 中断和 checkpoint 部分损坏有确定裁决
- 初始化状态对上层可见，不依赖隐式假设

## 3. 启动状态机

建议显式区分以下初始化状态：

| 状态 | 说明 | 是否允许读 |
| --- | --- | --- |
| `INIT_RESET` | 模块刚上电，未访问 flash | 否 |
| `INIT_META_SCAN` | 正在读取 `META lane` 和双 checkpoint | 否 |
| `INIT_CKPT_READY` | checkpoint 已恢复到 RAM cache | 仅 `boot_critical` |
| `INIT_TAIL_SCAN` | 正在补扫 checkpoint 之后的 tail | `boot_critical` 与已验证 block |
| `INIT_FULL_READY` | 恢复完成 | 是 |
| `INIT_DEGRADED` | checkpoint 全损或恢复冲突，进入全量恢复 | 受限 |
| `INIT_FAILED` | 格式错误或介质错误，无法继续 | 否 |

## 4. 首个可读时刻

### 4.1 设计结论

为了满足“上电快速读 block”，推荐把“可读”拆成两级：

1. `CKPT-ready read`
   仅允许读取 `boot_critical = 1` 且 checkpoint 中存在有效映射的 block
2. `full-ready read`
   允许读取所有已配置 block

### 4.2 规则

只有同时满足以下条件，模块才能进入 `INIT_CKPT_READY`：

1. 至少 1 份 checkpoint 有效
2. lane 角色表恢复成功
3. `boot_critical` block 的 `cur_addr` 都已恢复到 RAM cache
4. 没有检测到需要立即中止的格式冲突

若某个 `boot_critical` block 在 checkpoint 中缺失，则不能宣称 `CKPT-ready`，必须继续进入 tail scan 或降级。

## 5. checkpoint 恢复流程

### 5.1 checkpoint 选择规则

双 checkpoint 的选择顺序如下：

1. 过滤掉 CRC 错误或 `commit_marker` 缺失的副本
2. 在剩余副本中选择 `ckpt_generation` 最大者
3. 若代数相同，选择 `chunk_count` 完整者
4. 若仍冲突，进入 `INIT_DEGRADED`

### 5.2 从 checkpoint 恢复 RAM cache

恢复内容至少包括：

- 每个 lane 的 `active/dst/spare`
- 每个 lane 的 `free_offset`
- 每个 block 的 `cur_addr`
- 每个 block 的 `prev_addr`
- 每个 block 的 `seq`

恢复后立即做以下校验：

1. 地址必须落在对应 lane 范围内
2. `cur_addr` 与 `prev_addr` 不得相同
3. `seq(cur) >= seq(prev)`
4. `active/dst/spare` 不得重复指向同一扇区

## 6. tail scan 设计

### 6.1 目标

tail scan 只扫描 checkpoint 之后新增的数据，不回扫整个历史区域。

### 6.2 上界约束

为了让启动时间可证，建议增加以下配置：

| 配置项 | 说明 |
| --- | --- |
| `max_uncheckpointed_records_per_lane` | 每个 lane 未 checkpoint 的最大 record 数 |
| `max_uncheckpointed_bytes_per_lane` | 每个 lane 未 checkpoint 的最大累计字节 |
| `max_tail_scan_pages_per_lane` | 每个 lane 启动阶段最多扫描页数 |
| `ckpt_force_flush_threshold` | 触发强制 checkpoint 的上界 |

建议满足：

```text
tail_scan_bytes(lane) <= max_uncheckpointed_bytes_per_lane
tail_scan_pages(lane) <= max_tail_scan_pages_per_lane
```

当任一 lane 即将突破上界时，运行期必须优先完成 checkpoint，而不是继续无限推迟。

### 6.3 tail scan 行为

1. 从 checkpoint 记录的 `free_offset` 开始向后扫描
2. 遇到合法已提交 record 则更新 cache
3. 遇到未提交 record 则停止该连续区扫描
4. 遇到 header 损坏则按 `align_unit` 前进并统计异常
5. 达到 `data_end` 则结束该 lane 扫描

## 7. GC 中断恢复

### 7.1 裁决原则

GC 中断恢复不能只依赖 RAM，必须使用 `generation + sector_state + committed record` 裁决。

### 7.2 推荐裁决表

| 组合 | 结论 |
| --- | --- |
| `ACTIVE` 存在，`GC_DST` 不存在 | 继续使用旧 `ACTIVE` |
| `ACTIVE` 存在，`GC_DST` 存在但未提交 header | 丢弃 `GC_DST` |
| `ACTIVE` 存在，`GC_DST` 已提交且数据不完整 | 继续使用旧 `ACTIVE`，保留 `GC_DST` 待清理 |
| `ACTIVE` 存在，`GC_DST` 已提交且 live block 已复制完成 | 提升 `GC_DST` 为 `ACTIVE`，旧扇区转 `OLD_PENDING_ERASE` |
| 两个 `ACTIVE` 并存 | 选择 `generation` 更新且 live map 更完整者，另一方转降级恢复 |

### 7.3 stale checkpoint

checkpoint 可能落后于真实 flash 状态，因此恢复必须允许：

1. 先按 checkpoint 建立初始 cache
2. 再通过 tail scan 和 sector state 纠偏
3. 若发现 checkpoint 的 `active/dst/spare` 与 flash header 冲突，以合法 sector header 为准

## 8. 读接口语义

### 8.1 `fee_read` 在初始化阶段的行为

| 状态 | 行为 |
| --- | --- |
| `INIT_RESET/INIT_META_SCAN` | 返回 `BUSY` |
| `INIT_CKPT_READY` | 仅允许读取 `boot_critical` |
| `INIT_TAIL_SCAN` | 允许读取 `boot_critical` 和已验证 block |
| `INIT_FULL_READY` | 正常读 |
| `INIT_DEGRADED` | 按降级策略决定，默认只读已验证 block |
| `INIT_FAILED` | 返回 `E_NOT_OK` |

### 8.2 状态查询接口

建议提供：

```c
typedef enum
{
    FEE_INIT_RESET,
    FEE_INIT_META_SCAN,
    FEE_INIT_CKPT_READY,
    FEE_INIT_TAIL_SCAN,
    FEE_INIT_FULL_READY,
    FEE_INIT_DEGRADED,
    FEE_INIT_FAILED
} fee_init_state_t;

fee_init_state_t fee_get_init_state(void);
```

## 9. 恢复实现建议

### 9.1 建议模块分工

- `fee_recovery.c`: 启动状态机、checkpoint 选择、tail scan、GC 恢复
- `fee_ckpt.c`: checkpoint 解析和重建
- `fee_cache.c`: cache 导入与冲突裁决

### 9.2 推荐接口

```c
Std_ReturnType fee_recovery_start(void);
Std_ReturnType fee_recovery_step(void);
boolean fee_recovery_can_read_block(uint16 block_id);
boolean fee_recovery_is_full_ready(void);
```

## 10. 测试关注点

- checkpoint A 正确、checkpoint B 损坏
- checkpoint A/B 都正确，但 B 更新
- checkpoint A/B 都损坏，进入 `INIT_DEGRADED`
- `GC_SWITCH_HEADER` 期间掉电
- stale checkpoint 指向旧 `ACTIVE`
- `boot_critical` block 在 `INIT_CKPT_READY` 即可读
- tail 超过上界时强制 checkpoint 的行为
