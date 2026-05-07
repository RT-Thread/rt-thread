# FEE Port Adapter 设计

## 1. 目的

本文档定义 FEE 与底层 flash 驱动之间的适配边界，目标是：

- 让 FEE 核心不直接依赖具体器件驱动细节
- 支持 `Fls_17_Dmu` 与 RAM mock 两类后端
- 冻结 `read/write/erase/status/job_result` 的最小接口集

## 2. 设计原则

1. FEE 不能假设底层支持任意编程粒度。
2. FEE 的 header/payload/tail 切片必须满足驱动暴露的能力参数。
3. 端口层负责把驱动语义转换为 FEE 可消费的统一语义。
4. 同一时刻只允许 1 个底层 flash job 在飞行。

## 3. 能力参数

建议底层能力通过以下结构暴露：

```c
typedef struct
{
    uint16 read_unit;
    uint16 program_unit;
    uint32 erase_unit;
    uint16 preferred_chunk;
    uint8 supports_suspend;
    uint8 supports_compare;
} fee_flash_caps_t;
```

字段说明：

- `read_unit`: 最小读粒度
- `program_unit`: 最小编程粒度
- `erase_unit`: 最小擦除单位
- `preferred_chunk`: 推荐单次读写长度
- `supports_suspend`: 是否支持擦除挂起
- `supports_compare`: 是否支持驱动层 compare

## 4. 统一接口

### 4.1 必选接口

```c
Std_ReturnType fee_port_init(void);
Std_ReturnType fee_port_get_caps(fee_flash_caps_t *caps);
Std_ReturnType fee_port_read(uint32 addr, uint8 *dst, uint32 len);
Std_ReturnType fee_port_write(uint32 addr, const uint8 *src, uint32 len);
Std_ReturnType fee_port_erase(uint32 addr, uint32 len);
MemIf_StatusType fee_port_get_status(void);
MemIf_JobResultType fee_port_get_job_result(void);
```

### 4.2 可选接口

```c
void fee_port_mainfunction(void);
Std_ReturnType fee_port_cancel(void);
Std_ReturnType fee_port_compare(uint32 addr, const uint8 *src, uint32 len);
```

## 5. 接口语义

### 5.1 参数约束

1. `addr` 必须满足对应操作的对齐要求
2. `len` 必须是 `read_unit/program_unit/erase_unit` 的整数倍，或由上层先补齐
3. 端口层不得默默修正非法参数，必须返回错误

### 5.2 job 语义

推荐按异步 job 语义设计：

- `fee_port_write/erase` 仅发起 job
- 完成状态通过 `fee_port_get_status()` / `fee_port_get_job_result()` 查询
- 上层 `fee_mainfunction()` 负责 poll

如果底层驱动本身是同步接口，也建议在 port 层模拟出统一的 job 状态机，而不是把同步/异步差异泄露给 FEE 核心。

### 5.3 错误语义

建议至少区分：

- 参数错误
- 驱动忙
- 介质错误
- ECC / compare 错误
- 未初始化

## 6. 对齐与切片规则

### 6.1 通用规则

```text
header_len % program_unit == 0
tail_len   % program_unit == 0
payload_chunk % preferred_chunk == 0  or  payload_chunk % program_unit == 0
erase_len  % erase_unit == 0
```

### 6.2 `FAST` / `NORMAL` / `BULK`

- `FAST`: 优先使用 `preferred_chunk`，目标是最少 job 数
- `NORMAL`: 优先保证稳态吞吐和可恢复性
- `BULK`: 优先按 `preferred_chunk` 或 wordline 连续切片

## 7. 与 `Fls_17_Dmu` 的映射

建议在 `fee_port_fls.c` 中做一层薄适配：

- `fee_port_read` -> `Fls_17_Dmu_Read`
- `fee_port_write` -> `Fls_17_Dmu_Write`
- `fee_port_erase` -> `Fls_17_Dmu_Erase`
- `fee_port_get_status` -> `Fls_17_Dmu_GetStatus`
- `fee_port_get_job_result` -> `Fls_17_Dmu_GetJobResult`

并在适配层内集中处理：

- 地址偏移与物理基地址映射
- 返回码翻译
- 对齐断言
- 可选的统计信息采集

## 8. RAM Mock 后端

### 8.1 目的

在真实 flash 驱动接入前，用 RAM mock 快速验证：

- on-flash format 编解码
- checkpoint / recovery
- scheduler / GC 状态机

### 8.2 建议实现

```c
static uint8 fee_mock_flash[0x10000];
```

RAM mock 也应遵守与真实驱动一致的：

- `program_unit`
- `erase_unit`
- 单 job in-flight 约束

避免 mock 过于宽松，导致切换到真驱动时暴露问题。

## 9. 建议测试

- 非法对齐写入被拒绝
- 驱动 busy 时上层正确排队
- job result 从 `PENDING -> OK/FAILED`
- RAM mock 与 `Fls_17_Dmu` 的能力参数差异对上层透明
