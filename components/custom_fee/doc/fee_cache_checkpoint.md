# FEE Cache And Checkpoint 设计

## 1. 目的

本文档冻结 RAM cache 与 checkpoint 的数据结构、更新时机和容量边界。

关注点：

- RAM cache 如何支持 O(1) block 查找
- checkpoint 如何降低启动扫描成本
- 如何限制未 checkpoint tail 的上界

## 2. RAM Cache 模型

### 2.1 block cache

建议延续总设中的双副本模型：

```c
typedef struct
{
    uint8 lane;
    uint32 cur_addr;
    uint32 prev_addr;
    uint32 seq;
    uint16 len;
    uint8 cur_valid;
    uint8 prev_valid;
    uint8 cur_sector;
    uint8 prev_sector;
} fee_cache_entry_t;
```

### 2.2 lane context

```c
typedef struct
{
    uint8 active_sector;
    uint8 dst_sector;
    uint8 spare_sector;
    uint16 gc_cursor;
    uint8 gc_state;
    uint8 gc_requested;
    uint32 free_offset;
    uint32 gc_start_threshold;
    uint32 gc_force_threshold;
    uint32 dirty_record_count;
    uint32 dirty_bytes;
} fee_lane_ctx_t;
```

### 2.3 super context

```c
typedef struct
{
    fee_lane_ctx_t fast;
    fee_lane_ctx_t normal;
    fee_lane_ctx_t bulk;
    uint32 checkpoint_generation;
    uint8 checkpoint_dirty;
    uint8 init_state;
} fee_super_ctx_t;
```

## 3. cache 更新规则

1. 新 record 未提交前，不更新 cache
2. `CommitTail` 提交成功后：
   - `prev = cur`
   - `cur = new_record`
3. `TOMBSTONE` 提交后：
   - `cur_valid = 0`
   - `prev_valid` 按配置保留或清除
4. `rollback` 成功后：
   - `cur = copied_prev_record`
   - `prev = old_cur`

## 4. checkpoint 内容

### 4.1 必选内容

- `checkpoint_generation`
- 每个 lane 的 `active/dst/spare`
- 每个 lane 的 `free_offset`
- 每个 lane 的 `dirty_record_count`
- 每个 block 的 `cur_addr`
- 每个 block 的 `prev_addr`
- 每个 block 的 `seq`

### 4.2 可选内容

- `boot_critical` bitmap
- 统计信息摘要
- checkpoint 创建时间戳

## 5. checkpoint 刷写时机

### 5.1 背景触发

满足任一条件时请求后台 checkpoint：

1. lane 完成一次 GC 切换
2. `dirty_record_count >= ckpt_bg_records`
3. `dirty_bytes >= ckpt_bg_bytes`
4. `boot_critical` block 更新

### 5.2 强制触发

满足任一条件时必须优先完成 checkpoint：

1. `dirty_record_count >= ckpt_force_records`
2. `dirty_bytes >= ckpt_force_bytes`
3. 即将超过 `max_uncheckpointed_records_per_lane`
4. 即将超过 `max_uncheckpointed_bytes_per_lane`

## 6. tail 上界

### 6.1 设计目标

checkpoint 的价值不只是“平均更快”，而是要把启动 tail 扫描控制在明确上界内。

### 6.2 约束公式

对每个 lane 建议维护：

```text
dirty_record_count(lane) <= max_uncheckpointed_records_per_lane
dirty_bytes(lane)        <= max_uncheckpointed_bytes_per_lane
tail_scan_pages(lane)    <= max_tail_scan_pages_per_lane
```

推荐关系：

```text
ckpt_force_records <= max_uncheckpointed_records_per_lane
ckpt_force_bytes   <= max_uncheckpointed_bytes_per_lane
```

### 6.3 设计含义

这样启动时就可以给出明确预算：

```text
T_boot_tail_scan <= Σ lane_scan_time(max_tail_scan_pages_per_lane)
```

## 7. checkpoint 写入流程

### 7.1 chunk 化

当 `BLOCK_COUNT` 较大时，允许拆成多个 `CKPT_CHUNK` record。

### 7.2 提交流程

1. 写 checkpoint header / chunk metadata
2. 分块写 `BlockMapEntry[]`
3. 每个 chunk 独立提交
4. 最后一个 chunk 提交后，视为新 checkpoint 生效

### 7.3 生效语义

新 checkpoint 生效后：

- 旧 checkpoint 仍保留，直到下一次成功轮换
- RAM 中 `checkpoint_generation` 递增
- `dirty_record_count` / `dirty_bytes` 清零

## 8. 建议实现

### 8.1 建议模块

- `fee_cache.c`: cache 查找、更新、冲突解决
- `fee_ckpt.c`: checkpoint 组包、写入、读取

### 8.2 建议接口

```c
void fee_cache_commit_write(uint16 block_id, uint32 new_addr, uint16 len);
void fee_cache_commit_tombstone(uint16 block_id, uint32 new_addr);
void fee_cache_commit_rollback(uint16 block_id, uint32 new_addr);
boolean fee_ckpt_due_background(void);
boolean fee_ckpt_due_force(void);
Std_ReturnType fee_ckpt_flush_step(void);
```

## 9. 测试关注点

- 多次写入后 `prev` 指针正确轮转
- `rollback` 后 `cur/prev` 关系正确
- checkpoint chunk 化写入中断
- `dirty_bytes` 达到上界时强制 checkpoint
- 启动时 tail 扫描页数不超过配置预算
