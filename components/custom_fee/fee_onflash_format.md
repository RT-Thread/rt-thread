# FEE On-Flash Format 设计

## 1. 目的

本文档冻结 FEE 在 flash 上的持久化格式，包括：

- lane / sector / record 的物理组织
- `SectorHeader` / `RecordHeader` / `CommitTail` / checkpoint 的字段定义
- 提交点、CRC 和掉电恢复判定规则

本文档是编码 `fee_port_fls.c`、`fee_ckpt.c`、`fee_recovery.c`、`fee_lane_*` 的直接输入。

## 2. 设计原则

1. 所有持久化结构必须满足底层 `program_unit` 对齐。
2. 业务可见一致性只依赖持久化提交标记，不依赖 RAM 中间状态。
3. `commit_marker` 是唯一提交点，必须最后落盘。
4. old copy 在 new copy 提交前必须保持可读。
5. 除 `META lane` 外，不允许在 flash 上原地修改 record 内容。

## 3. 基本约定

### 3.1 地址与对齐

- 最小地址单位：byte address
- 最小对齐单位：`align_unit = max(8, program_unit)`
- `FAST` record 推荐按 `1 wordline` 对齐
- `NORMAL/BULK` record 至少按 `align_unit` 对齐

统一定义：

```text
align_up(x, a) = ((x + a - 1) / a) * a
record_span    = align_up(header_len + payload_len + tail_len, record_align)
```

### 3.2 lane 编码

| lane | 值 | 说明 |
| --- | --- | --- |
| `META` | `0x01` | checkpoint / super state |
| `FAST` | `0x02` | immediate 语义 |
| `NORMAL` | `0x03` | 主数据路径 |
| `BULK` | `0x04` | 大块或低频大块 |

### 3.3 sector state 编码

| state | 值 | 说明 |
| --- | --- | --- |
| `ERASED` | `0xFF` | 空白扇区 |
| `PREPARE` | `0x11` | header 已写，尚未投入使用 |
| `ACTIVE` | `0x22` | 当前追加写扇区 |
| `GC_DST` | `0x33` | 当前 GC 复制目标扇区 |
| `OLD_PENDING_ERASE` | `0x44` | 已切换完成，等待擦除 |
| `BAD` | `0x55` | 检测到 header 损坏或非法状态 |

`PREPARE -> ACTIVE / GC_DST -> OLD_PENDING_ERASE -> ERASED` 是唯一合法迁移方向。

## 4. SectorHeader

### 4.1 布局基线

建议固定 `SectorHeader` 长度为 `64 B`。

| 偏移 | 字段 | 类型 | 说明 |
| --- | --- | --- | --- |
| `0x00` | `magic` | `uint32` | 固定扇区签名 |
| `0x04` | `format_version` | `uint16` | 版本号 |
| `0x06` | `lane_id` | `uint8` | lane 编码 |
| `0x07` | `state` | `uint8` | sector state |
| `0x08` | `generation` | `uint32` | lane 内单调递增代数 |
| `0x0C` | `erase_count` | `uint32` | 可选，产品化阶段启用 |
| `0x10` | `data_start` | `uint32` | record 区起始偏移 |
| `0x14` | `data_end` | `uint32` | record 区终止偏移 |
| `0x18` | `hdr_seq` | `uint32` | header 刷写序号 |
| `0x1C` | `hdr_crc` | `uint32` | header CRC |
| `0x20` | `commit_marker` | `uint32` | header 提交标记 |
| `0x24` | `reserved[7]` | `uint32[7]` | 预留 |

### 4.2 判定规则

sector header 只有同时满足以下条件才视为有效：

1. `magic` 正确
2. `format_version` 在支持范围内
3. `hdr_crc` 正确
4. `commit_marker` 正确
5. `lane_id` / `state` 组合合法

若 `hdr_crc` 正确但 `commit_marker` 缺失，则该 sector 视为未提交 header，不参与恢复。

## 5. RecordHeader

### 5.1 布局基线

建议固定 `RecordHeader` 长度为 `32 B`。

| 偏移 | 字段 | 类型 | 说明 |
| --- | --- | --- | --- |
| `0x00` | `magic` | `uint32` | 固定 record 签名 |
| `0x04` | `block_id` | `uint16` | 逻辑块号 |
| `0x06` | `record_type` | `uint8` | `DATA/TOMBSTONE/CKPT` |
| `0x07` | `flags` | `uint8` | `PREPARE/COPIED/ROLLBACK` |
| `0x08` | `data_len` | `uint16` | payload 长度 |
| `0x0A` | `header_len` | `uint16` | header 长度 |
| `0x0C` | `seq` | `uint32` | block 内单调递增序号 |
| `0x10` | `generation` | `uint32` | 所在 sector generation 镜像 |
| `0x14` | `prev_addr_hint` | `uint32` | 可选，调试/恢复辅助 |
| `0x18` | `hdr_crc` | `uint32` | header CRC |
| `0x1C` | `reserved` | `uint32` | 预留 |

### 5.2 record type 编码

| type | 值 | 说明 |
| --- | --- | --- |
| `DATA` | `0xD1` | 普通数据 |
| `TOMBSTONE` | `0xD2` | 失效记录 |
| `CKPT_CHUNK` | `0xC1` | checkpoint 片段 |

### 5.3 flags 编码

按 bit 使用：

- `bit0`: `PREPARE`
- `bit1`: `COPIED`
- `bit2`: `ROLLBACK`
- 其他 bit 保留

约束：

1. 未提交 record 可以带 `PREPARE`
2. 已提交后 `PREPARE` 语义仍可保留为“曾经是正常写入”，不要求原地清零
3. `COPIED` 仅用于 GC 迁移生成的记录
4. `ROLLBACK` 仅用于显式回滚生成的记录

## 6. CommitTail

### 6.1 布局基线

建议固定 `CommitTail` 长度为 `16 B`。

| 偏移 | 字段 | 类型 | 说明 |
| --- | --- | --- | --- |
| `0x00` | `data_crc` | `uint32` | payload CRC |
| `0x04` | `tail_crc` | `uint32` | tail 前部 CRC |
| `0x08` | `tail_flags` | `uint32` | 预留或扩展 |
| `0x0C` | `commit_marker` | `uint32` | 唯一提交点 |

### 6.2 提交规则

写入顺序固定为：

1. `RecordHeader`
2. `Payload`
3. `CommitTail` 的前 `12 B`
4. `commit_marker`

恢复时只有满足下列条件的 record 才可接受：

1. `RecordHeader` 合法
2. `Payload` 可读
3. `CommitTail` 的 `tail_crc` 正确
4. `commit_marker` 正确

若 `commit_marker` 缺失，则整个 record 视为不存在。

## 7. 特殊记录

### 7.1 TOMBSTONE

约束如下：

- `record_type = TOMBSTONE`
- `data_len = 0`
- `payload` 为空
- `seq = old_seq + 1`

### 7.2 checkpoint 记录

checkpoint 只允许出现在 `META lane`。

建议结构为：

```text
RecordHeader(type = CKPT_CHUNK)
CheckpointChunkPayload
CommitTail
```

`CheckpointChunkPayload` 内部再封装：

- `ckpt_generation`
- `chunk_index`
- `chunk_count`
- `chunk_bytes`
- `payload_crc`
- `chunk_data`

完整 checkpoint 以最后一个 chunk 的 `commit_marker` 和 `chunk_index == chunk_count - 1` 为完成标志。

## 8. Version 与升级策略

### 8.1 format version

- `major` 变化表示不兼容变更
- `minor` 变化表示向前兼容扩展

建议编码：

```text
format_version = (major << 8) | minor
```

### 8.2 升级策略

1. 启动时若发现旧版本且支持迁移，进入只读恢复 + 后台重写流程
2. 若版本不兼容且不支持迁移，必须显式返回格式错误
3. 不允许不同 `major` 版本的 record 混写在同一 lane

## 9. 编码实现建议

### 9.1 模块职责

- `fee_onflash.h`: 常量、magic、结构体和 encode/decode API
- `fee_onflash.c`: header/tail/checkpoint 编码与校验
- `fee_recovery.c`: 遍历 flash 并调用 decode API

### 9.2 建议接口

```c
uint32 fee_onflash_calc_record_span(const fee_block_cfg_t *cfg, uint16 data_len);
Std_ReturnType fee_onflash_encode_record_header(...);
Std_ReturnType fee_onflash_encode_commit_tail(...);
boolean fee_onflash_is_record_committed(const uint8 *buf);
boolean fee_onflash_validate_sector_header(const uint8 *buf);
```

## 10. 测试关注点

- `SectorHeader` CRC 正确但 `commit_marker` 缺失
- `RecordHeader` 正确但 `CommitTail` 未完成
- `TOMBSTONE` 与 `DATA` 的 `seq` 比较
- `CKPT_CHUNK` 丢失最后一块时的恢复行为
- 不同 `format_version` 的兼容与拒绝路径
