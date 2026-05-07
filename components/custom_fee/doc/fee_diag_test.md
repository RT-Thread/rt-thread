# custom_fee 诊断测试用例说明

## 1. 目的

`custom_fee_diag_test` 用于在 QEMU + RAM mock flash 环境下验证 `custom_fee` 的以下行为：

- block 数据写入、读回、一致性校验
- rollback / invalidate 功能
- 重新初始化后的恢复能力
- fast lane GC 触发时的耗时和底层驱动访问次数
- checkpoint / sector / record 在 mock flash 中的实际落盘格式

和 `custom_fee_test` 的区别：

- `custom_fee_test` 只做通过/失败判定
- `custom_fee_diag_test` 额外打印数据内容、耗时、驱动访问统计、flash 布局和原始内存 dump

## 2. 执行命令

在 `bsp/qemu-vexpress-a9` 目录下执行：

```powershell
cmd /c "call C:\Work\InstallTools\env-windows\tools\bin\env-init.bat && scons -j8"
powershell -NoProfile -ExecutionPolicy Bypass -File .\codex_qemu_ps.ps1 -MshCommand custom_fee_test
powershell -NoProfile -ExecutionPolicy Bypass -File .\codex_qemu_ps.ps1 -MshCommand custom_fee_diag_test
```

## 3. 用例覆盖范围

当前诊断用例按下面的顺序执行：

| 步骤 | 内容 | 目的 |
| --- | --- | --- |
| 1 | backend 全擦除 + `fee_init()` | 构造 cold boot 场景 |
| 2 | block 1 写入 `fast_a` | 验证 fast lane 写入 |
| 3 | block 1 读回 `fast_a` | 验证读回一致性 |
| 4 | block 1 改写 `fast_b` | 验证覆盖写 |
| 5 | block 1 读回 `fast_b` | 验证最新版本生效 |
| 6 | `fee_rollback(1)` | 验证保留上一个版本 |
| 7 | block 1 再读 | 验证回滚到 `fast_a` |
| 8 | block 2 写入 `normal_a` | 验证 normal lane 写入 |
| 9 | block 2 读回 | 验证 normal lane 读回 |
| 10 | 再次 `fee_init()` | 验证重新初始化恢复 |
| 11 | block 1 / block 2 读回 | 验证恢复后数据仍可用 |
| 12 | block 1 连续写 160 次 | 触发 fast lane GC |
| 13 | block 1 再读 | 验证 GC 后最新数据仍正确 |
| 14 | `fee_invalidate(1)` | 验证失效流程 |
| 15 | 再读 block 1 | 期望返回 `FEE_E_NOT_OK` |
| 16 | dump 最终 flash 布局 | 验证 checkpoint、lane、record 的落盘结构 |

## 4. 诊断输出字段

### 4.1 通用性能字段

每个步骤会打印：

```text
custom_fee_diag_test: write block1 fast_a time=0 ms ticks=0 wait_loops=1 driver[init=0 read=0/0B write=4/1208B erase=1/57344B poll=1]
```

字段含义：

- `time`: 墙钟毫秒，来自 `rt_tick_get_millisecond()`
- `ticks`: RT-Thread tick 差值
- `wait_loops`: 该请求从提交到 idle 的轮询次数
- `driver[read=X/YB write=X/YB erase=X/YB poll=X]`
  - `read` / `write` / `erase`: 底层驱动真实调用次数
  - `YB`: 同类操作累计字节数
  - `poll`: `fee_port_mainfunction()` 被轮询的次数

注意：这里的驱动统计是端到端 flash 访问量，不仅包含 block record 本身，也包含 checkpoint、GC 搬迁等内部元数据流量。

### 4.2 GC 识别字段

GC 压测阶段会额外打印 fast lane 状态变化：

```text
custom_fee_diag_test: gc_write[106] time=10 ms ticks=1 wait_loops=7 fast_lane[sector=0->2 gen=1->2 free=0x00029a40->0x00038440 gc=1] driver[read=4/1088B write=8/2360B erase=3/172032B poll=7]
```

字段含义：

- `sector=A->B`: fast lane 活动 sector 的切换
- `gen=A->B`: fast lane generation 变化
- `free=old->new`: `free_offset` 变化
- `gc=1`: 本次写入发生了真实 GC 扇区切换

当前样例中：

- 160 次 fast write 里只有 `gc_write[106]` 触发了真实 GC
- 该次 GC 从 `sector 0` 切换到 `sector 2`
- GC 总结输出为：

```text
custom_fee_diag_test: gc summary writes=160 total_time=1070 ms total_ticks=116 gc_events=1 gc_time=10 ms gc_ticks=1 gc_max_ticks=1
```

## 5. Mock Flash 总体布局

QEMU 默认 RAM mock flash 参数：

- 总容量：`0x000A0000` = 640 KiB
- 擦除粒度：`0x0000E000` = 56 KiB
- 读粒度：`1`
- 写粒度：`8`

当前 `custom_fee` 实际使用 `10` 个 sector，总占用 `0x0008C000`，尾部 `0x00014000` 未使用。

### 5.1 地址布局图

```text
0x00000000  +-------------------------------+
            | Meta sector 0 (checkpoint A)  |
0x0000E000  +-------------------------------+
            | Meta sector 1 (checkpoint B)  |
0x0001C000  +-------------------------------+
            | Fast lane sector 0            |
0x0002A000  +-------------------------------+
            | Fast lane sector 1            |
0x00038000  +-------------------------------+
            | Fast lane sector 2            |
0x00046000  +-------------------------------+
            | Normal lane sector 0          |
0x00054000  +-------------------------------+
            | Normal lane sector 1          |
0x00062000  +-------------------------------+
            | Normal lane sector 2          |
0x00070000  +-------------------------------+
            | Bulk lane sector 0            |
0x0007E000  +-------------------------------+
            | Bulk lane sector 1            |
0x0008C000  +-------------------------------+
            | Unused tail                   |
0x000A0000  +-------------------------------+
```

### 5.2 末态布局摘要

来自一次 `custom_fee_diag_test` 样例：

```text
custom_fee_diag_test: meta[0] base=0x00000000 valid=1 generation=165 entries=2 commit=0x434f4d4d
custom_fee_diag_test: meta[1] base=0x0000e000 valid=1 generation=164 entries=2 commit=0x434f4d4d
custom_fee_diag_test: lane=fast   range=[0x0001c000,0x00046000) active=2 dst=0 spare=0 free=0x0003f040
custom_fee_diag_test: lane=normal range=[0x00046000,0x00070000) active=0 dst=1 spare=2 free=0x000460b0
custom_fee_diag_test: lane=bulk   range=[0x00070000,0x0008c000) active=0 dst=1 spare=1 free=0x00070040
```

说明：

- 最终活动 checkpoint 镜像在 `meta[0]`
- fast lane 的有效活动 sector 已经切换到 `sector 2`
- normal lane 只写入了一个 record
- bulk lane 仅格式化了 sector header，没有业务 record

### 5.3 先建立一个简单心智模型

对新工程师来说，可以先把 `custom_fee` 想成三层：

```text
应用 block 读写
        |
        v
FEE 逻辑层
- 根据 block_id 找到 lane
- 维护 cache
- 决定是否做 checkpoint / GC
        |
        v
flash 落盘层
- sector header
- record header
- payload
- commit tail
```

再进一步，把一个 lane 想成“顺序追加日志”的空间：

```text
lane sector
  -> 先写一个 sector header
  -> 后面不断顺序追加 record
  -> free_offset 始终指向下一个可写位置
  -> 空间快用完时触发 GC，把仍然有效的 record 搬到新 sector
```

对业务 block 来说，有两个最关键的事实：

- **写 block 不是覆盖旧地址，而是追加一个新 record**
- **读 block 不是扫描整个 flash，而是先查 cache，再去读当前 record**

### 5.4 一次 block 写入，到底在 flash 里放了什么

以 `block 1` 写入 `fast_a` 为例，真正落盘的对象不是“只有 32 字节 payload”，而是一个完整 record：

```text
+---------------------------+
| fee_record_header_t 0x20  |
+---------------------------+
| payload                   |
| len = block data len      |
+---------------------------+
| fee_commit_tail_t  0x10   |
+---------------------------+
| erased padding            |
| 对齐到 record_align       |
+---------------------------+
```

这个 record 的组成如下：

| 部分 | 内容 | 作用 |
| --- | --- | --- |
| `record header` | block id、record type、data_len、seq、hdr_crc | 标识“这是哪个 block 的第几个版本” |
| `payload` | 业务数据本身 | 真正需要保存的 block 内容 |
| `commit tail` | `data_crc`、`tail_crc`、`commit_marker` | 标识“这条 record 已提交完成，可读” |
| `padding` | 仍然保持 `0xFF` 的空白区 | 保证下一条 record 从对齐地址开始 |

#### 5.4.1 block 1 的写入排布

`block 1` 配置：

- `max_len = 32`
- `lane = fast`
- `record_align = 512`
- `crc_mode = FEE_CRC16`

因此它的 record span 不是 80B，而是被对齐到 `0x200 = 512B`：

```text
header  = 0x20 = 32B
payload = 0x20 = 32B
tail    = 0x10 = 16B
raw sum = 0x50 = 80B
aligned span = 0x200 = 512B
padding = 0x200 - 0x50 = 0x1B0 = 432B
```

样例里的第一条 `block 1` record 地址形态可以理解成：

```text
0x0001C040  +-------------------------------+
            | record header (0x20)          |
0x0001C060  +-------------------------------+
            | payload 32B                   |
0x0001C080  +-------------------------------+
            | commit tail (0x10)            |
0x0001C090  +-------------------------------+
            | padding / erased bytes        |
            | ...                           |
0x0001C240  +-------------------------------+
            | next record starts here       |
```

所以：

- `block 1` 每写一次，逻辑上只写了 32B 数据
- 但在 flash 地址空间里，会消耗一个 `512B` 的 record 槽位

#### 5.4.2 block 2 的写入排布

`block 2` 配置：

- `max_len = 128`
- `lane = normal`
- `record_align = 8`
- `crc_mode = FEE_CRC32`

因此它的 record 更紧凑：

```text
header  = 0x20 = 32B
payload = 0x40 = 64B
tail    = 0x10 = 16B
raw sum = 0x70 = 112B
aligned span = 0x70 = 112B
padding = 0
```

样例里的 `block 2` record：

```text
0x00046040  +-------------------------------+
            | record header (0x20)          |
0x00046060  +-------------------------------+
            | payload 64B                   |
0x000460A0  +-------------------------------+
            | commit tail (0x10)            |
0x000460B0  +-------------------------------+
            | next free_offset              |
```

这说明：

- fast lane 更偏向“热数据 + 大对齐 + 快速追加”
- normal lane 更偏向“普通数据 + 紧凑存储”

### 5.5 一次 block 写入，除了 record 还会发生什么

很多新工程师第一次看这条统计会困惑：

```text
custom_fee_diag_test: write block1 fast_a ... driver[write=4/1208B erase=1/57344B]
```

为什么明明只写了一个 block，却不是 `write=3`？

原因是 **一次业务写入通常不只包含“record 本身”**，还可能包含 checkpoint 元数据更新。

以当前样例的 `write block1 fast_a` 为例，可按下面理解：

```text
1. 写 record header
2. 写 payload
3. 写 commit tail
4. 写 checkpoint image
5. 擦除一个 meta sector，给 checkpoint image 轮换使用
```

图示如下：

```text
fee_write(block1)
    |
    +--> lane append record
    |     +--> write record header
    |     +--> write payload
    |     +--> write commit tail
    |
    +--> checkpoint flush
          +--> erase inactive meta sector
          +--> write new checkpoint image
```

因此性能统计里常见的现象是：

- `write_calls` 比“header/payload/tail 三次写”更多
- `erase_calls` 不一定代表 GC，也可能只是 checkpoint 轮换

### 5.6 一次 block 读取，到底读了什么

读路径不是“直接拿 payload 地址 memcpy 给用户”，而是更谨慎：

```text
fee_read(block_id, offset, len)
    |
    +--> cache lookup
          找到当前有效 record 地址
    |
    +--> read record header
          确认 block_id / len / type
    |
    +--> read commit tail
          确认 commit marker / tail crc
    |
    +--> read payload
          如 block 配置了 CRC，则读出 payload 做校验
    |
    +--> copy 用户请求的 offset/len 到 dst
```

图示如下：

```text
用户 read block
    |
    v
cache 告诉 FEE:
"当前 block 2 的最新 record 在 0x00046040"
    |
    v
读 0x00046040 处的 record header
    |
    v
读 0x000460A0 处的 commit tail
    |
    v
读 0x00046060 处的 payload
    |
    v
CRC 校验通过后，把结果返回给用户
```

这就是为什么 `block 1` / `block 2` 的读统计常见是：

```text
driver[read=3/...]
```

因为当前两个测试 block 都启用了 CRC，所以一次成功读取通常包含：

1. 读 header
2. 读 tail
3. 读完整 payload

注意：

- 即使用户只读其中一部分 `offset/len`
- 在 `CRC16/CRC32` 模式下，FEE 仍会先把完整 payload 读出来做校验

只有未来某个 block 配置成 `FEE_CRC_NONE`，读路径才可能退化成更少的底层读取。

### 5.7 rollback 为什么比普通读写更重

`rollback block1` 样例里常看到：

```text
driver[read=4/... write=4/... erase=1/...]
```

它比单次 `write` 更重，是因为 rollback 不是简单改一个指针，而是：

```text
1. 找到上一版本 record
2. 读上一版本 header
3. 读上一版本 tail
4. 读上一版本 payload
5. 再把这份旧数据当成“新版本”重新追加写入
6. 再触发 checkpoint 刷新
```

也就是说，rollback 的本质是：

- **先读旧版本**
- **再追加一条新 record 表示“我回到了旧内容”**

### 5.8 GC 时内存里发生了什么

GC 不是“压缩整个 flash”，而是“当当前 active sector 快写满时，把仍然有效的记录搬到新的 sector”。

样例中真正的 GC 发生在：

```text
gc_write[106] ... fast_lane[sector=0->2 gen=1->2 ... gc=1]
```

可以把它理解成：

```text
旧状态:
  fast lane active sector = 0
  free_offset 已接近 sector 尾部

GC 动作:
  1. 选择 sector 2 作为新的目标 sector
  2. 给 sector 2 写新的 sector header
  3. 把 sector 0 中仍然有效的 block record 搬过去
  4. 再把这次用户新写入的 record 追加到 sector 2
  5. 更新 active sector = 2, generation = 2
  6. 擦除旧 sector，释放为空闲区
  7. 刷新 checkpoint
```

图示如下：

```text
GC 前:
  fast sector 0 [old active]  --> 有效 record + 历史 record + 即将写满
  fast sector 1 [spare]
  fast sector 2 [erased]

GC 中:
  fast sector 2 <- 写新 sector header
  fast sector 2 <- 搬迁有效 record
  fast sector 2 <- 追加最新用户 record

GC 后:
  fast sector 2 [new active]
  fast sector 0 [to be erased / erased]
  fast sector 1 [spare]
```

所以样例里那次 GC 统计：

```text
driver[read=4/1088B write=8/2360B erase=3/172032B poll=7]
```

可以粗略理解为：

- 有效 record 搬迁需要额外读取旧 sector 内容
- 新 sector header + 搬迁 record + 本次新写入 + checkpoint，导致写次数显著增加
- 目标 sector 预处理、旧 sector 回收、meta sector checkpoint 轮换，会带来多次擦除

### 5.9 怎么看一条性能数据是不是“正常”

对新工程师，建议先按下面的经验判断：

| 场景 | 正常现象 |
| --- | --- |
| 普通 write | `write_calls` 通常大于 3，因为包含 checkpoint |
| 普通 read | 有 CRC 的 block 往往是 `read_calls = 3` |
| rollback | `read_calls` 和 `write_calls` 都会比普通写更大 |
| invalidate | 通常比 data write 少一次 payload 写 |
| GC write | `wait_loops`、`read_calls`、`write_calls`、`erase_calls` 会明显抬升 |

可以把一条数据先拆成两部分看：

```text
业务 record 成本
+ 元数据成本(checkpoint / GC)
= 总 driver 访问次数
```

## 6. 落盘结构细节

### 6.1 Sector Header

`fee_sector_header_t` 大小为 `0x40` 字节。

| 偏移 | 大小 | 字段 | 说明 |
| --- | --- | --- | --- |
| `0x00` | 4 | `magic` | `FEE_SECTOR_MAGIC = 0x46454553` |
| `0x04` | 2 | `format_version` | 当前为 `0x0100` |
| `0x06` | 1 | `lane_id` | meta/fast/normal/bulk |
| `0x07` | 1 | `state` | `ACTIVE` / `GC_DST` 等 |
| `0x08` | 4 | `generation` | 当前活动代次 |
| `0x0C` | 4 | `erase_count` | 当前 mock 驱动未累计 |
| `0x10` | 4 | `data_start` | record 区起始地址 |
| `0x14` | 4 | `data_end` | record 区结束地址 |
| `0x18` | 4 | `hdr_seq` | 当前等于 generation |
| `0x1C` | 4 | `hdr_crc` | header CRC |
| `0x20` | 4 | `commit_marker` | `0x434F4D4D` |
| `0x24` | 28 | `reserved[7]` | 预留 |

### 6.2 Record Header

`fee_record_header_t` 大小为 `0x20` 字节。

| 偏移 | 大小 | 字段 | 说明 |
| --- | --- | --- | --- |
| `0x00` | 4 | `magic` | `FEE_RECORD_MAGIC = 0x46454552` |
| `0x04` | 2 | `block_id` | 业务 block 号 |
| `0x06` | 1 | `record_type` | `DATA` / `TOMBSTONE` |
| `0x07` | 1 | `flags` | 当前固定 `0x01` |
| `0x08` | 2 | `data_len` | 业务 payload 长度 |
| `0x0A` | 2 | `header_len` | 当前固定 `0x20` |
| `0x0C` | 4 | `seq` | block 内递增版本号 |
| `0x10` | 4 | `generation` | 当前实现未单独填写 |
| `0x14` | 4 | `prev_addr_hint` | 当前实现未填写 |
| `0x18` | 4 | `hdr_crc` | record header CRC |
| `0x1C` | 4 | `reserved` | 预留 |

### 6.3 Commit Tail

`fee_commit_tail_t` 大小为 `0x10` 字节。

| 偏移 | 大小 | 字段 | 说明 |
| --- | --- | --- | --- |
| `0x00` | 4 | `data_crc` | payload CRC |
| `0x04` | 4 | `tail_crc` | tail CRC |
| `0x08` | 4 | `tail_flags` | 当前为 `0` |
| `0x0C` | 4 | `commit_marker` | `0x434F4D4D` |

### 6.4 Record 占用公式

```text
record_span =
    align_up(
        sizeof(fee_record_header_t) +
        align_up(data_len, program_unit) +
        sizeof(fee_commit_tail_t),
        record_align)
```

当前样例：

- block 1
  - payload = `32B`
  - program unit = `8B`
  - record align = `512B`
  - span = `0x200`
- block 2
  - payload = `64B`
  - program unit = `8B`
  - record align = `8B`
  - span = `0x70`

## 7. 样例 dump 与字段解读

以下 dump 为 little-endian 原始内存内容。

### 7.1 活动 checkpoint 镜像

```text
custom_fee_diag_test: meta active raw addr=0x00000000 len=64
0x00000000: 4b 43 45 46 00 01 00 00 a5 00 00 00 00 00 00 00
0x00000010: 00 00 00 00 00 00 00 00 00 00 00 00 40 f0 03 00
0x00000020: 02 00 00 00 02 00 00 03 00 00 00 00 b0 60 04 00
0x00000030: 01 00 00 00 00 01 02 03 00 00 00 00 40 00 07 00
```

解读：

- `0x00000000 = 0x4645434B`，即 checkpoint magic
- `0x00000008 = 0x000000A5`，即 generation `165`
- `0x0000001C = 0x0003F040`，是 fast lane `free_offset`
- `0x00000020 = 0x00000002`，是 fast lane `active_generation`
- `0x00000024 = 02 00 00 03`
  - `active_sector = 2`
  - `dst_sector = 0`
  - `spare_sector = 0`
  - `sector_count = 3`
- `0x0000002C = 0x000460B0`，是 normal lane `free_offset`

### 7.2 Fast lane 活动 sector header

```text
custom_fee_diag_test: sector raw addr=0x00038000 len=64
0x00038000: 53 45 45 46 00 01 01 22 02 00 00 00 00 00 00 00
0x00038010: 40 80 03 00 00 60 04 00 02 00 00 00 6a 80 24 00
0x00038020: 4d 4d 4f 43 00 00 00 00 00 00 00 00 00 00 00 00
0x00038030: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
```

解读：

- `magic = 0x46454553`
- `lane_id = 1`，对应 fast lane
- `state = 0x22`，对应 `ACTIVE`
- `generation = 2`
- `data_start = 0x00038040`
- `data_end = 0x00046000`
- `hdr_seq = 2`
- `commit_marker = 0x434F4D4D`

样例输出里该 header 被标记为 `header-valid=0`，但原始 bytes 仍然完整打印，便于继续排查 header 校验路径。

### 7.3 Normal lane record 样例

record header:

```text
custom_fee_diag_test: record header raw addr=0x00046040 len=32
0x00046040: 52 45 45 46 02 00 d1 01 40 00 20 00 01 00 00 00
0x00046050: 00 00 00 00 00 00 00 00 21 f7 a5 ae 00 00 00 00
```

payload:

```text
custom_fee_diag_test: record payload raw addr=0x00046060 len=64
0x00046060: 21 24 27 2a 2d 30 33 36 39 3c 3f 42 45 48 4b 4e
0x00046070: 51 54 57 5a 5d 60 63 66 69 6c 6f 72 75 78 7b 7e
0x00046080: 81 84 87 8a 8d 90 93 96 99 9c 9f a2 a5 a8 ab ae
0x00046090: b1 b4 b7 ba bd c0 c3 c6 c9 cc cf d2 d5 d8 db de
```

tail:

```text
custom_fee_diag_test: record tail raw addr=0x000460a0 len=16
0x000460a0: 60 44 b0 0a 3e 69 7a 2e 00 00 00 00 4d 4d 4f 43
```

解读：

- `block_id = 2`
- `record_type = 0xD1`，即 `DATA`
- `data_len = 0x40`，即 `64B`
- `header_len = 0x20`
- `seq = 1`
- `hdr_crc = 0xAEA5F721`
- tail 中：
  - `data_crc = 0x0AB04460`
  - `tail_crc = 0x2E7A693E`
  - `tail_flags = 0`
  - `commit_marker = 0x434F4D4D`

### 7.4 sector 内部排布图

以 normal lane 的 sector 0 为例：

```text
0x00046000  +-------------------------------+
            | fee_sector_header_t (0x40)    |
0x00046040  +-------------------------------+
            | fee_record_header_t (0x20)    |
0x00046060  +-------------------------------+
            | payload (0x40)                |
0x000460A0  +-------------------------------+
            | fee_commit_tail_t (0x10)      |
0x000460B0  +-------------------------------+
            | next free_offset              |
            | erased area ...               |
0x00054000  +-------------------------------+
```

## 8. 结果解读建议

看 `custom_fee_diag_test` 输出时，优先关注下面几点：

- block write/read 的数据内容是否和测试模式一致
- `driver[...]` 是否符合预期
  - fast block 单次写入统计明显大于纯 payload，是因为包含 checkpoint traffic
- `gc_write[*]` 中 `gc=1` 的那一条是否存在
- `gc summary` 是否能反映真实 sector 切换次数
- 最终 `flash layout [final]` 中 lane 地址、active sector、free_offset 是否合理
- `record header raw` / `record tail raw` 的 magic 和 commit marker 是否正确

## 9. 当前样例结论

基于当前 QEMU 样例：

- `custom_fee_test` / `custom_fee_diag_test` 均通过
- block 1 / block 2 的写入、读回、回滚、重启恢复、失效场景均正确
- fast lane 在 `gc_write[106]` 发生一次真实 GC
- GC 后 fast lane 从 `sector 0` 切换到 `sector 2`
- checkpoint generation 最终增长到 `165`
- 诊断输出已经可以直接对应到 checkpoint、sector header、record header、payload、tail 的原始内存布局
