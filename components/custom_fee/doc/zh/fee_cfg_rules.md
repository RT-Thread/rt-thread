# FEE Configuration Rules 设计

## 1. 目的

本文档冻结 block 配置表、lane 映射、容量规划和编译期校验规则。

编码目标是：

- 把错误配置挡在编译期
- 让 `FAST/NORMAL/BULK/META` 的职责边界稳定
- 让容量与启动时间预算可计算

## 2. block 配置模型

建议配置结构如下：

```c
typedef struct
{
    uint16 block_id;
    uint16 max_len;
    uint8 block_class;
    uint8 lane_type;
    uint8 endurance_class;
    uint8 keep_prev_copy;
    uint8 allow_rollback;
    uint8 crc_mode;
    uint16 record_align;
    uint8 boot_critical;
} fee_block_cfg_t;
```

## 3. block class 规则

| class | 规则 |
| --- | --- |
| `FAST` | immediate 语义；优先单 record / 单 wordline |
| `NORMAL` | 常规配置和状态数据 |
| `BULK` | 大块或低频大块；不得污染 `FAST/NORMAL` |
| `META` | 仅给 checkpoint / super state 使用 |

## 4. lane 映射规则

### 4.1 必选规则

1. `FAST` 块只能映射到 `FAST lane`
2. `NORMAL` 块只能映射到 `NORMAL lane`
3. `BULK` 块只能映射到 `BULK lane`
4. 业务 block 不能映射到 `META lane`

### 4.2 immediate 映射

若上层配置 `FeeImmediateData = TRUE`，内部应自动映射为：

- `block_class = FAST`
- `lane_type = FAST`

## 5. 大小与对齐规则

### 5.1 记录跨度

```text
record_span(i) = align(record_header + max_len(i) + commit_tail, record_align(i))
```

### 5.2 推荐分类

| 类别 | payload 大小建议 | 规则 |
| --- | --- | --- |
| `small` | `<= 448 B` | 尽量单 wordline 提交 |
| `medium` | `449 B ~ 2048 B` | 允许多 wordline |
| `large` | `> 2048 B` | 默认归 `BULK lane` |

### 5.3 约束

1. `FAST` 块必须满足 `record_span <= fast_single_record_limit`
2. `FAST` 块禁止跨 wordline 提交
3. `BULK` 块不得配置为 immediate
4. `allow_rollback = 1` 时必须 `keep_prev_copy = 1`

## 6. 容量规划

### 6.1 基础公式

```text
live_span(i)   = record_span(i) * (keep_prev_copy(i) ? 2 : 1)
lane_live      = Σ live_span(i), i ∈ lane
lane_payload   = sector_count(lane) * sector_usable_bytes - lane_mgmt_bytes
lane_headroom  = max_burst_records(lane) * max(record_span(i), i ∈ lane) + switch_guard(lane)
```

必须满足：

```text
lane_payload >= lane_live + lane_headroom + gc_fragment_guard
```

### 6.2 建议经验值

- `FAST lane`: `max_burst_records = 2 ~ 4`
- `NORMAL lane`: `max_burst_records = 1 ~ 2`
- `BULK lane`: `max_burst_records = 1`
- `gc_fragment_guard >= 2 * max_record_span(lane)`

## 7. 启动时间相关配置

为了保证上电快速读 block，配置中还应引入：

| 配置项 | 说明 |
| --- | --- |
| `boot_critical` | 启动早期必须可读 |
| `ckpt_bg_records` / `ckpt_bg_bytes` | 背景 checkpoint 阈值 |
| `ckpt_force_records` / `ckpt_force_bytes` | 强制 checkpoint 阈值 |
| `max_uncheckpointed_records_per_lane` | 启动 tail 上界 |
| `max_uncheckpointed_bytes_per_lane` | 启动 tail 上界 |
| `max_tail_scan_pages_per_lane` | 启动时间预算输入 |

## 8. 编译期校验清单

建议配置工具或静态断言至少检查：

1. `block_id` 全局唯一
2. `max_len > 0`
3. `record_align >= program_unit`
4. `FAST` 块满足 `fast_single_record_limit`
5. `allow_rollback -> keep_prev_copy`
6. `lane_payload >= lane_live + lane_headroom + gc_fragment_guard`
7. `checkpoint_size <= meta_lane_capacity`
8. `boot_critical` 块必须可进入 checkpoint

## 9. 示例

```c
static const fee_block_cfg_t fee_block_table[] =
{
    { .block_id = 1, .max_len = 32,   .block_class = FEE_BLOCK_FAST,   .lane_type = FEE_LANE_FAST,   .endurance_class = FEE_END_HOT,  .keep_prev_copy = 1, .allow_rollback = 1, .crc_mode = FEE_CRC16, .record_align = 512, .boot_critical = 1 },
    { .block_id = 2, .max_len = 256,  .block_class = FEE_BLOCK_NORMAL, .lane_type = FEE_LANE_NORMAL, .endurance_class = FEE_END_WARM, .keep_prev_copy = 1, .allow_rollback = 1, .crc_mode = FEE_CRC32, .record_align = 8,   .boot_critical = 0 },
    { .block_id = 3, .max_len = 4096, .block_class = FEE_BLOCK_BULK,   .lane_type = FEE_LANE_BULK,   .endurance_class = FEE_END_COLD, .keep_prev_copy = 0, .allow_rollback = 0, .crc_mode = FEE_CRC32, .record_align = 512, .boot_critical = 0 },
};
```

## 10. 测试关注点

- 非法 immediate 大块被编译期拒绝
- lane 容量不足被编译期拒绝
- `boot_critical` 缺失 checkpoint 空间时报错
- `record_align` 与 `program_unit` 不匹配时报错
