# custom_fee 对外 API 列表

## 1. 这份文档解决什么问题

这份文档面向 **使用 `custom_fee` 的工程师**，不是面向 FEE 内部维护者。

它回答四类问题：

- 用户到底能调哪些接口
- 每个接口是同步完成，还是异步排队
- 调用后应该怎么看结果
- 一个新项目如何把 FEE 接起来并跑起来

如果你想看 flash 中的 record / sector / checkpoint 具体长什么样，请再看 [fee_diag_test.md](C:/sourcedata/rt-thread/components/custom_fee/fee_diag_test.md)。

## 2. 哪些是“对用户暴露”的接口

当前建议用户直接依赖的头文件只有：

- [fee_api.h](C:/sourcedata/rt-thread/components/custom_fee/fee_api.h)

不建议业务层直接调用的内部接口：

- [fee_port.h](C:/sourcedata/rt-thread/components/custom_fee/fee_port.h)
- [fee_flash_drv.h](C:/sourcedata/rt-thread/components/custom_fee/fee_flash_drv.h)
- `fee_core_*`
- `fee_sched_*`
- `fee_gc_*`
- `fee_recovery_*`

可以把边界理解成：

```text
业务代码
  -> fee_api.h

板级/驱动适配代码
  -> fee_flash_drv.h

FEE 内部实现
  -> 其他 fee_*.c / *.h
```

### 2.1 功能特性

这一节不是重复列 API 名字，而是说明当前这套 `custom_fee` 机制本身做了什么，以及这些能力在代码里分别落在哪些模块。

#### 2.1.1 RAM cache + 快速 block 查找

- `fee_cache.c` 里不是简单数组顺序扫描，而是同时维护 `g_fee_cache[]` 和 `g_fee_cache_index[]`
- `fee_cache_lookup(block_id)` 先对 `block_id` 做 hash，再做线性探测定位 slot，平均查找复杂度接近 O(1)
- `fee_get_status()`、`fee_core_read()`、恢复流程、checkpoint 导入导出，都会先走这层 cache，而不是每次从 flash 头扫到尾

对使用者的直接价值：

- block 数量增大后，查找最新版本地址的开销更稳定
- 读路径先定位地址，再按地址读 payload，不需要把历史 record 全部重扫一遍

#### 2.1.2 同步读，异步写，语义明确

- `fee_read()` 是同步接口，路径是 `fee_read()` -> `fee_sched_submit_read()` -> `fee_core_read()`，函数返回时结果已经在用户 buffer 里，或者已经明确失败
- `fee_write()`、`fee_invalidate()`、`fee_rollback()` 是异步提交接口，先进入调度队列，真正执行靠 `fee_mainfunction()` 逐步推进
- `fee_sched.c` 在提交写请求时会立刻把模块状态置成 `BUSY_INTERNAL/PENDING`，这表示“请求已受理”，不是“已经落盘”

这意味着：

- **立即读**：是的，当前实现支持同步读，调用返回即可拿结果
- **立即写完成**：不是。当前实现支持“立即提交写请求”，但真正写完并持久化到 flash，要看 `fee_get_job_result()` 最终是否变成 `FEE_JOB_OK`

这种设计的价值是：

- 读请求延迟更确定
- 写请求不会把业务线程长期卡死在擦写动作里

#### 2.1.3 当前副本 + 上一副本，支持回滚和容错读

- `fee_cache_entry_t` 同时保存 `cur_addr/prev_addr` 和 `cur_valid/prev_valid`
- 新数据写入成功后，旧版本会下沉成 `prev_*`
- `fee_core_read()` 先读 `cur_addr`；如果当前副本校验失败，且 `prev_valid` 还在，就会再尝试读上一份
- `fee_core_rollback()` 不是简单改指针，而是把 `prev_addr` 对应的数据重新写成一条新的 current record

对使用者的价值：

- 可以显式调用 `fee_rollback()` 回到上一版
- 当前副本损坏时，读路径还有机会从上一份恢复结果
- 对掉电中断、坏 record、异常校验失败更稳健

#### 2.1.4 checkpoint 快速启动，boot-critical block 可提前可读

- `fee_init()` 内部不是一次性把所有 lane 全扫完才返回，而是先通过 `fee_recovery_step()` 尝试恢复 checkpoint
- 如果 checkpoint 能恢复，且所有 `boot_critical` block 都已经在 cache 里有有效 current copy，就先进入 `FEE_INIT_CKPT_READY`
- 后续剩余 tail 记录再由 `fee_mainfunction()` 在后台继续补扫，最终进入 `FEE_INIT_FULL_READY`

这带来的好处是：

- 系统启动时可以先把关键配置读出来，不必等所有历史 record 全恢复完
- “快启动”和“全量恢复”被拆成两个阶段，启动时间更可控

这里要特别说明：

- `CKPT_READY` 不等于“全部 block 都能读”
- 在这个阶段，只有 `boot_critical` 且确实已经恢复到 RAM cache 的 block 才允许读

#### 2.1.5 lane 分级隔离，快慢业务不混跑

- `fee_cfg.c` 里的每个 block 都带 `lane_type`，当前分成 `FAST`、`NORMAL`、`BULK`
- `fee_sched.c` 会把 `FAST` block 的请求放进 urgent queue，把 `NORMAL/BULK` 放进 normal queue
- `fee_recovery.c` 和 GC 上下文里，每个 lane 都独立维护自己的地址范围、`active/dst/spare sector`、`free_offset`、GC 状态和代际信息

这意味着：

- 高频小块和低频大块不会完全共享同一条写入通道
- `FAST` lane 请求可以优先于普通 lane 请求推进
- GC、恢复、容量压力也是按 lane 分开处理，不是整片 flash 一锅炖

#### 2.1.6 checkpoint 与 GC 都在后台推进

- 写入后，`fee_core.c` 会按剩余空间计算 `gc_requested/gc_force`
- 同时还会按每个 lane 的脏 record 数和脏字节数，决定是否请求 checkpoint，或者直接强制 checkpoint
- `fee_mainfunction()` 会依次推进 `port -> recovery -> scheduler -> gc -> core(checkpoint flush)`，把后台维护动作拆成小步执行

这种机制的价值：

- 正常读写请求和后台维护动作被解耦
- checkpoint 不需要每写一笔都同步刷
- 空间接近阈值时，又能自动把 GC 和 checkpoint 拉起来做自保护

#### 2.1.7 读路径带完整性校验，不是盲读

- `fee_core_read_payload()` 读取时会检查 record header、commit tail
- 如果 block 配置启用了 CRC，还会把 payload 读回 RAM 做 CRC 校验
- 只有 header、tail、CRC 都通过，才认为本次读取成功

这带来的价值：

- 不是“地址存在就算有效”
- 用户读到的数据是经过格式和完整性校验的
- 一旦当前版本损坏，配合上一副本机制，还能继续尝试降级读取

#### 2.1.8 底层驱动统一抽象，QEMU/RAM mock 和真 flash 共用一套 FEE

- 对 FEE 上层来说，只依赖 `fee_flash_driver_*` 这一组统一接口
- `fee_port.c` 只是薄封装，默认提供 weak 的 RAM mock 实现，板级工程可以给出 strong definition 覆盖掉它
- 所以上层 `fee_api.c / fee_core.c / fee_sched.c / fee_recovery.c` 不需要知道底层接的是 QEMU mock、RAM mock，还是真实 FLS 驱动

对接入工程的价值：

- 先在 QEMU 或 RAM mock 上把 block 配置、恢复逻辑、GC 行为跑通
- 再切到真实 flash driver 时，业务层 API 和 FEE 核心逻辑都不用重写
- 驱动适配边界清晰，板级代码只关心 `read/write/erase/get_caps/mainfunction/status/job_result`

## 3. 公开 API 总览

### 3.1 功能接口

| 接口 | 作用 | 同步/异步 | 何时算完成 |
| --- | --- | --- | --- |
| `fee_init()` | 初始化 FEE | 半同步 | 函数返回后已到 `CKPT_READY` 或 `FULL_READY`；如需全量 ready 还要继续跑 `fee_mainfunction()` |
| `fee_read()` | 读取 block 数据 | 同步 | 函数返回即完成 |
| `fee_write()` | 写入 block 数据 | 异步提交 | 要靠 `fee_mainfunction()` 推进，直到 `fee_get_job_result() != PENDING` |
| `fee_invalidate()` | 失效一个 block | 异步提交 | 同上 |
| `fee_rollback()` | 回滚到上一个版本 | 异步提交 | 同上 |
| `fee_get_status()` | 查询某个 block 的逻辑状态 | 同步 | 函数返回即完成 |
| `fee_mainfunction()` | 驱动内部状态机 | 轮询入口 | 需要周期调用 |

### 3.2 状态查询接口

| 接口 | 返回什么 |
| --- | --- |
| `fee_get_memif_status()` | FEE 模块当前总体状态：未初始化 / 空闲 / 忙 |
| `fee_get_job_result()` | 最近一次异步 job 的全局结果 |
| `fee_get_init_state()` | 初始化阶段当前处于哪个状态 |

## 4. 返回码和状态码

### 4.1 `fee_ret_t`

| 值 | 含义 | 典型场景 |
| --- | --- | --- |
| `FEE_E_OK` | 成功 | 提交成功 / 读取成功 |
| `FEE_E_NOT_OK` | 失败 | block 不存在、数据无效、底层失败 |
| `FEE_E_BUSY` | 当前不能做 | 正在初始化、GC 阻塞、队列满、空间不足待回收 |
| `FEE_E_UNINIT` | 未初始化 | 没先调 `fee_init()` |
| `FEE_E_PARAM` | 参数错误 | 空指针、非法长度、非法 block id |

### 4.2 `fee_status_t`

| 值 | 含义 |
| --- | --- |
| `FEE_STATUS_UNINIT` | 模块未初始化 |
| `FEE_STATUS_IDLE` | 空闲，没有待处理工作 |
| `FEE_STATUS_BUSY` | 底层 driver busy |
| `FEE_STATUS_BUSY_INTERNAL` | FEE 内部仍有调度、恢复、checkpoint、GC 等工作 |

### 4.3 `fee_job_result_t`

| 值 | 含义 |
| --- | --- |
| `FEE_JOB_NONE` | 还没有 job |
| `FEE_JOB_OK` | 最近一次 job 成功结束 |
| `FEE_JOB_PENDING` | 最近一次 job 仍在处理中 |
| `FEE_JOB_FAILED` | 最近一次 job 失败 |
| `FEE_JOB_CANCELED` | 预留 |
| `FEE_JOB_INCONSISTENT` | 预留 |

### 4.4 `fee_block_status_t`

| 值 | 含义 |
| --- | --- |
| `FEE_BLOCK_STATUS_EMPTY` | 该 block 还没有有效数据 |
| `FEE_BLOCK_STATUS_VALID` | 当前 block 有有效数据 |
| `FEE_BLOCK_STATUS_INVALIDATED` | block 被失效 |
| `FEE_BLOCK_STATUS_INCONSISTENT` | 预留 |

## 5. 每个 API 到底该怎么用

### 5.1 `fee_init`

```c
fee_ret_t fee_init(void);
```

用途：

- 初始化 FEE 内部上下文
- 初始化底层 flash 适配层
- 尝试恢复 checkpoint
- 扫描必要的 flash 结构

使用建议：

1. 系统启动时调用一次
2. 如果返回不是 `FEE_E_OK`，初始化失败
3. 如果返回 `FEE_E_OK`，再通过 `fee_get_init_state()` 判断是否已经 `FULL_READY`

要点：

- `fee_init()` 返回 `FEE_E_OK`，**不等于所有 block 都完全可读**
- 它只保证初始化至少已经推进到：
  - `FEE_INIT_CKPT_READY`，或者
  - `FEE_INIT_FULL_READY`

状态解释：

| 状态 | 对用户意味着什么 |
| --- | --- |
| `FEE_INIT_CKPT_READY` | checkpoint 已恢复，部分 boot-critical block 可读，后台仍需继续扫描 |
| `FEE_INIT_FULL_READY` | 全部恢复完成，可正常读写所有 block |
| `FEE_INIT_FAILED` | 初始化失败 |

推荐写法：

```c
if (fee_init() != FEE_E_OK)
{
    /* init failed */
}

while (fee_get_init_state() != FEE_INIT_FULL_READY)
{
    fee_mainfunction();
}
```

如果你的系统希望尽快启动，也可以在 `CKPT_READY` 先放行业务，再后台继续推进：

```c
if (fee_init() == FEE_E_OK)
{
    if (fee_get_init_state() == FEE_INIT_CKPT_READY)
    {
        /* 先只使用 boot-critical block */
    }
}
```

### 5.2 `fee_read`

```c
fee_ret_t fee_read(uint16_t block_id, uint16_t offset, uint8_t *dst, uint16_t len);
```

用途：

- 从某个 block 读取数据

特点：

- **同步接口**
- 函数返回时，`dst` 已经拿到结果，或者已经明确失败

参数说明：

| 参数 | 含义 |
| --- | --- |
| `block_id` | 要读取的 block 号 |
| `offset` | block 内偏移 |
| `dst` | 用户缓冲区 |
| `len` | 要读的长度 |

返回结果判断：

- `FEE_E_OK`：读取成功
- `FEE_E_BUSY`：当前还没恢复到可读阶段，或者 block 当前不可读
- `FEE_E_NOT_OK`：block 没有有效数据，或数据校验失败
- `FEE_E_PARAM`：参数错误

例子：

```c
uint8_t data[32];
fee_ret_t ret;

ret = fee_read(1U, 0U, data, sizeof(data));
if (ret == FEE_E_OK)
{
    /* data 有效 */
}
```

注意：

- `fee_read()` 不走异步队列
- 但它仍依赖当前恢复状态
- 如果 `fee_get_init_state()` 还没到允许读取该 block 的阶段，可能返回 `FEE_E_BUSY`

### 5.3 `fee_write`

```c
fee_ret_t fee_write(uint16_t block_id, const uint8_t *src, uint16_t len);
```

用途：

- 把一份新的 block 数据提交给 FEE

特点：

- **异步提交接口**
- `fee_write()` 返回 `FEE_E_OK` 只代表“已成功入队或成功接收”
- 不代表数据已经真正落到 flash 并提交完成

正确用法：

```c
fee_ret_t ret;

ret = fee_write(1U, data, sizeof(data));
if (ret != FEE_E_OK)
{
    /* 提交失败 */
}

while (fee_get_job_result() == FEE_JOB_PENDING)
{
    fee_mainfunction();
}

if (fee_get_job_result() == FEE_JOB_OK)
{
    /* 本次写入真正完成 */
}
```

写完成后，你可以再用 `fee_read()` 回读验证。

### 5.4 `fee_invalidate`

```c
fee_ret_t fee_invalidate(uint16_t block_id);
```

用途：

- 标记一个 block 为失效

特点：

- 异步提交
- 完成判断方式和 `fee_write()` 相同

适用场景：

- 某 block 不再有效，需要让后续 `fee_read()` 返回无效

### 5.5 `fee_rollback`

```c
fee_ret_t fee_rollback(uint16_t block_id);
```

用途：

- 回滚到该 block 的上一个有效版本

特点：

- 异步提交
- 只有 block 配置了 `keep_prev_copy=1` 且 `allow_rollback=1` 才有意义

完成后建议：

- 用 `fee_read()` 重新回读
- 用业务层校验回滚后的内容是否正确

### 5.6 `fee_get_status`

```c
fee_ret_t fee_get_status(uint16_t block_id, fee_block_status_t *status);
```

用途：

- 查询某个 block 当前的逻辑状态

它回答的不是“模块忙不忙”，而是：

- 这个 block 有没有数据
- 这个 block 是否已失效

例子：

```c
fee_block_status_t status;

if (fee_get_status(1U, &status) == FEE_E_OK)
{
    if (status == FEE_BLOCK_STATUS_VALID)
    {
        /* block 有效 */
    }
}
```

### 5.7 `fee_mainfunction`

```c
void fee_mainfunction(void);
```

这是最容易被忽略，但又最关键的接口。

作用：

- 推进恢复流程
- 推进写队列
- 推进 rollback / invalidate
- 推进 GC
- 推进 checkpoint flush
- 推进底层 flash driver 状态机

如果你的系统只调了 `fee_write()`，但没有周期调 `fee_mainfunction()`，那么：

- job 会一直停在 `FEE_JOB_PENDING`
- `fee_get_memif_status()` 可能一直是 busy

推荐：

- 放到周期任务中调用
- 或者在阻塞等待循环里主动调用

例如：

```c
void app_10ms_task(void)
{
    fee_mainfunction();
}
```

## 6. 如何获取“最终结果”

这是使用 FEE 时最重要的部分。

### 6.1 初始化结果怎么判断

判断顺序：

1. 看 `fee_init()` 返回值
2. 再看 `fee_get_init_state()`

推荐规则：

- `fee_init() != FEE_E_OK`：初始化失败
- `fee_init() == FEE_E_OK && fee_get_init_state() == FEE_INIT_FULL_READY`：完全可用
- `fee_init() == FEE_E_OK && fee_get_init_state() == FEE_INIT_CKPT_READY`：部分可用，继续调用 `fee_mainfunction()`

### 6.2 读取结果怎么判断

读取是同步的，直接看 `fee_read()` 的返回值。

规则：

- `FEE_E_OK`：`dst` 有效
- 其他值：本次读取失败

### 6.3 写入/失效/回滚结果怎么判断

这三个是异步接口，要分两步判断：

第一步，看“提交成功没有”：

```c
ret = fee_write(...);
if (ret != FEE_E_OK)
{
    /* 连提交都没成功 */
}
```

第二步，看“后台执行最终成功没有”：

```c
while (fee_get_job_result() == FEE_JOB_PENDING)
{
    fee_mainfunction();
}

if (fee_get_job_result() == FEE_JOB_OK)
{
    /* 真正完成 */
}
else
{
    /* 真正失败 */
}
```

### 6.4 `fee_get_job_result()` 是不是“按 block 分开”的

不是。

当前 `fee_get_job_result()` 是 **全局最近 job 结果**，不是 per-block 结果。

这意味着：

- 对简单业务，建议串行使用：上一条 write 完成后，再提下一条
- 对复杂业务，如果要并发排队多个请求，需要自己在业务层维护请求上下文

## 7. 推荐调用范式

## 7.1 最简单、最稳妥的串行模式

这是最推荐新项目采用的模式。

```c
static fee_ret_t app_fee_wait_job_done(void)
{
    while (fee_get_job_result() == FEE_JOB_PENDING)
    {
        fee_mainfunction();
    }

    return (fee_get_job_result() == FEE_JOB_OK) ? FEE_E_OK : FEE_E_NOT_OK;
}

fee_ret_t app_fee_write_block_sync(uint16_t block_id, const uint8_t *src, uint16_t len)
{
    fee_ret_t ret;

    ret = fee_write(block_id, src, len);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    return app_fee_wait_job_done();
}
```

优点：

- 最容易理解
- 调试最简单
- 不容易误用全局 `job_result`

### 7.2 周期任务模式

如果系统里已经有 10ms / 5ms 周期任务，可以这样用：

```c
void app_periodic_10ms(void)
{
    fee_mainfunction();
}
```

业务发请求时：

```c
if (fee_write(1U, data, len) == FEE_E_OK)
{
    /* 返回后不阻塞，等待后台完成 */
}
```

之后由其他逻辑轮询：

```c
if (fee_get_job_result() == FEE_JOB_OK)
{
    /* 最近 job 完成 */
}
```

### 7.3 恢复期读 boot-critical block

如果你有“系统先启动关键配置，其他数据稍后恢复”的需求，可以利用：

- `FEE_INIT_CKPT_READY`
- block 配置里的 `boot_critical`

逻辑如下：

```c
if (fee_init() == FEE_E_OK)
{
    if (fee_get_init_state() == FEE_INIT_CKPT_READY)
    {
        /* 先读取 boot-critical block */
    }
}
```

注意：

- 不是所有 block 在 `CKPT_READY` 都可读
- 非 boot-critical block 可能仍返回 `FEE_E_BUSY`

## 8. 队列和并发语义

当前实现里：

- fast lane 请求进入 urgent queue
- normal/bulk 请求进入 normal queue
- 每个队列容量是 `FEE_CFG_MAX_PENDING_REQUESTS = 8`

这意味着：

- `fee_write()` / `fee_invalidate()` / `fee_rollback()` 连续提交太多时，可能返回 `FEE_E_BUSY`
- 读取不走队列

虽然实现支持排队，但对业务使用者仍建议：

- 优先采用“提交一个，等它完成，再提下一个”的串行模式

原因：

- `fee_get_job_result()` 是全局结果
- 串行模式更容易和业务动作一一对应

## 9. 最小上手步骤

### 9.1 打开组件

启用：

- `COMPONENT_USING_CUSTOM_FEE`

见 [Kconfig](C:/sourcedata/rt-thread/components/custom_fee/Kconfig)。

### 9.2 包含头文件

```c
#include "fee_api.h"
```

### 9.3 系统启动时初始化

```c
void app_fee_init(void)
{
    if (fee_init() != FEE_E_OK)
    {
        /* error */
        return;
    }

    while (fee_get_init_state() != FEE_INIT_FULL_READY)
    {
        fee_mainfunction();
    }
}
```

### 9.4 周期调用 `fee_mainfunction`

```c
void app_periodic_10ms(void)
{
    fee_mainfunction();
}
```

### 9.5 写入一个 block

```c
uint8_t cfg[32];

if (fee_write(1U, cfg, sizeof(cfg)) == FEE_E_OK)
{
    while (fee_get_job_result() == FEE_JOB_PENDING)
    {
        fee_mainfunction();
    }
}
```

### 9.6 读取一个 block

```c
uint8_t cfg[32];

if (fee_read(1U, 0U, cfg, sizeof(cfg)) == FEE_E_OK)
{
    /* cfg valid */
}
```

## 10. 用户最常见的误区

### 10.1 误区一：`fee_write()` 返回成功，就等于已经写完

不是。

- `fee_write()` 成功，只是“请求已被接受”
- 真正完成，要等 `fee_get_job_result()` 变成 `FEE_JOB_OK`

### 10.2 误区二：不调用 `fee_mainfunction()`

如果不调用：

- 初始化不会继续推进
- 异步 job 不会完成
- GC / checkpoint 不会推进

### 10.3 误区三：把 `fee_get_status()` 当成模块状态

不是。

- `fee_get_status(block_id, &status)` 查询的是 **某个 block**
- `fee_get_memif_status()` 查询的是 **整个 FEE 模块**

### 10.4 误区四：把 `fee_get_job_result()` 当成每个 block 独立的结果

不是。

它是全局最近 job 的结果。

### 10.5 误区五：业务层直接调用 `fee_port_*`

不建议。

业务层只应该通过 [fee_api.h](C:/sourcedata/rt-thread/components/custom_fee/fee_api.h) 使用 FEE。

## 11. 当前默认 block 配置示例

当前示例配置在 [fee_cfg.c](C:/sourcedata/rt-thread/components/custom_fee/fee_cfg.c)：

| block_id | max_len | lane | rollback | boot_critical |
| --- | --- | --- | --- | --- |
| `1` | `32` | fast | 是 | 是 |
| `2` | `128` | normal | 是 | 是 |
| `3` | `256` | normal | 是 | 否 |
| `4` | `768` | bulk | 否 | 否 |

如果你要上项目，通常要做的不是改 API，而是改这张 block 表。

## 12. 如何适配到自己的工程

适配分成两部分：

- **业务块配置**
- **底层 flash 驱动适配**

### 12.1 配置业务 block

当前 block 表在 [fee_cfg.c](C:/sourcedata/rt-thread/components/custom_fee/fee_cfg.c) 的 `g_fee_block_table`。

你通常需要为每个业务块确定：

- `block_id`
- `max_len`
- `block_class`
- `lane_type`
- `keep_prev_copy`
- `allow_rollback`
- `crc_mode`
- `record_align`
- `boot_critical`

建议规则：

- 高频小数据：优先放 `fast`
- 普通配置数据：优先放 `normal`
- 大块、低频数据：优先放 `bulk`

### 12.2 适配底层 flash driver

板级或驱动层要实现的是 [fee_flash_drv.h](C:/sourcedata/rt-thread/components/custom_fee/fee_flash_drv.h) 中这些符号：

```c
fee_ret_t fee_flash_driver_init(void);
fee_ret_t fee_flash_driver_get_caps(fee_flash_caps_t *caps);
fee_ret_t fee_flash_driver_read(uint32_t addr, uint8_t *dst, uint32_t len);
fee_ret_t fee_flash_driver_write(uint32_t addr, const uint8_t *src, uint32_t len);
fee_ret_t fee_flash_driver_erase(uint32_t addr, uint32_t len);
void fee_flash_driver_mainfunction(void);
fee_status_t fee_flash_driver_get_status(void);
fee_job_result_t fee_flash_driver_get_job_result(void);
```

说明：

- 这些接口应由板级提供 **strong definition**
- 当前 [fee_port.c](C:/sourcedata/rt-thread/components/custom_fee/fee_port.c) 里自带的是默认 `weak` RAM mock 实现
- 在真机工程中，你应替换成实际 flash 驱动

### 12.3 底层能力参数要返回什么

`fee_flash_driver_get_caps()` 至少要正确返回：

- `total_size`
- `read_unit`
- `program_unit`
- `erase_unit`
- `preferred_chunk`

FEE 会根据这些参数做：

- 参数校验
- 对齐检查
- sector 布局
- record span 校验

### 12.4 周期调度如何接入

把 `fee_mainfunction()` 放进：

- OS 周期任务
- bare-metal 主循环
- 后台 worker

都可以。

但必须满足：

- 初始化阶段能持续推进
- 异步 job 能持续推进

### 12.5 Mock 模式如何上手

如果只是想在 QEMU 或 PC 仿真中先跑通，不需要先接真实 flash driver。

当前默认行为：

- `fee_port.c` 已自带 RAM mock flash
- 只要打开组件，就能先跑基本逻辑和测试

这适合：

- 先验证 block 表是否合理
- 先验证上层使用方式
- 先做恢复 / GC / checkpoint 联调

## 13. 推荐的接入顺序

对新项目建议按下面顺序推进：

1. 先打开 `custom_fee` 组件，用默认 mock backend 跑通基础用例
2. 按业务需求整理 block 表
3. 在应用层写最小读写封装
4. 确保 `fee_mainfunction()` 已有稳定周期调用点
5. 再接入真实 flash driver
6. 最后做真机掉电恢复、GC、耐久性验证

## 14. 一个完整的最小示例

```c
#include "fee_api.h"

static fee_ret_t app_fee_wait_ready(void)
{
    while (fee_get_init_state() != FEE_INIT_FULL_READY)
    {
        if (fee_get_init_state() == FEE_INIT_FAILED)
        {
            return FEE_E_NOT_OK;
        }
        fee_mainfunction();
    }

    return FEE_E_OK;
}

static fee_ret_t app_fee_wait_job_done(void)
{
    while (fee_get_job_result() == FEE_JOB_PENDING)
    {
        fee_mainfunction();
    }

    return (fee_get_job_result() == FEE_JOB_OK) ? FEE_E_OK : FEE_E_NOT_OK;
}

fee_ret_t app_fee_startup(void)
{
    fee_ret_t ret;

    ret = fee_init();
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    return app_fee_wait_ready();
}

fee_ret_t app_fee_save_cfg(uint16_t block_id, const uint8_t *data, uint16_t len)
{
    fee_ret_t ret;

    ret = fee_write(block_id, data, len);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    return app_fee_wait_job_done();
}

fee_ret_t app_fee_load_cfg(uint16_t block_id, uint8_t *data, uint16_t len)
{
    return fee_read(block_id, 0U, data, len);
}
```

## 15. 一句话总结

如果你只记三件事，记这三条：

1. 用户接口只看 [fee_api.h](C:/sourcedata/rt-thread/components/custom_fee/fee_api.h)
2. `fee_read()` 是同步的，`fee_write()/invalidate()/rollback()` 是异步的
3. 想让 FEE 真正工作起来，必须持续调用 `fee_mainfunction()`
