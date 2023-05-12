# FGDMA 驱动程序

## 1. 概述

GDMA(Generic Direct Memory Access)，提供多个DMA通道，多个通道可以同时工作，独立配置给不同内存数据搬运使用


## 2. 功能

FGDMA 驱动程序主要完成 GDMA 模块的初始化，GDMA 通道的分配与释放，
相关源文件为：
```
fgdma
    .
    ├── fgdma.c
    ├── fgdma.h
    ├── fgdma_g.c
    ├── fgdma_hw.h
    ├── fgdma_intr.c
    ├── fgdma_selftest.c
    └── fgdma_sinit.c
```

## 3. 配置方法

以下部分将指导您完成 FGDMA 驱动的软件配置:

- 初始化 GDMA 控制器
- 配置 GDMA 通道，使用直接模式或者 BDL 模式进行操作
- 启动 GDMA 通道

## 4. 应用示例

### [通过GDMA拷贝内存数据](../../../baremetal/example/peripheral/dma/fgdma_async_memcpy)

## 5. API参考

### 5.1. 用户数据结构

#### FGdmaConfig

- GDMA控制器配置

```c
typedef struct
{
    u32 instance_id;               /* GDMA控制器ID */
    u32 irq_num[FGDMA_NUM_OF_CHAN];   /* GDMA控制器中断号 */
    u32 irq_prority;               /* GDMA控制器中断优先级 */
    volatile uintptr_t base_addr;  /* GDMA控制器基地址 */
    FGdmaOperPriority rd_qos;      /* 读操作优先级 */
    FGdmaOperPriority wr_qos;      /* 写操作优先级 */
    u32 caps;                       /* driver capacity */
} FGdmaConfig; /* GDMA控制器配置 */
```

#### FGdmaChanConfig

- DMA通道配置

```c
typedef struct
{
    FGdmaChanIndex      chan_id; /* DMA通道ID */
    FGdmaOperPriority   rd_qos;  /* DMA通道读Qos配置 */
    FGdmaOperPriority   wr_qos;  /* DMA通道写Qos配置 */
    FGdmaOperMode       trans_mode; /* DMA通道的操作模式，直接模式或者BDL模式 */
    /* Direct模式有效 */
    FGdmaBurstSize      rd_align; /* DMA读请求的Burst对齐方式 */
    FGdmaBurstSize      wr_align; /* DMA写请求的Burst对齐方式 */    
    /* BDL模式有效 */
    boolean             roll_back; /* 循环模式，TRUE: 当前BDL列表完成后，从第一个BDL项从新开始传输 */ 
    FGdmaBdlDesc        *descs;
    u32                 total_desc_num;
    u32                 valid_desc_num;
} FGdmaChanConfig; /* DMA通道配置 */
```

#### FGdmaChan

- GDMA通道实例

```c
typedef struct _FGdmaChan
{
    FGdmaChanConfig config;     /* DMA通道配置 */
    FGdma *gdma;                /* DMA控制器实例 */
    FGdmaChanEvtHandler evt_handlers[FGDMA_CHAN_NUM_OF_EVT];  /* DMA通道事件回调函数 */
    void *evt_handler_args[FGDMA_CHAN_NUM_OF_EVT];            /* DMA通道事件回调函数入参 */
} FGdmaChan; /* GDMA通道实例 */
```

#### FGdma

- GDMA控制器实例

```c
typedef struct _FGdma
{
    FGdmaConfig config;       /* GDMA控制器配置 */
    u32 is_ready;             /* GDMA控制器初始化是否完成 */
    FGdmaChan *chans[FGDMA_NUM_OF_CHAN]; /* GDMA通道实例，如果通道没有分配，值为NULL */
} FGdma; /* GDMA控制器实例 */
```

#### FGdmaBdlDesc

- BDL描述符

```c
typedef struct
{
    u32 src_addr_l; /* 0x0, 数据源地址低32位 */
    u32 src_addr_h; /* 0x4, 数据源地址高32位 */
    u32 dst_addr_l; /* 0x8, 数据目的地址低32位 */
    u32 dst_addr_h; /* 0xc, 数据目的地址高32位 */
#define FGDMA_SRC_TC_BDL_BURST_SET(x)      SET_REG32_BITS((x), 1U, 0U)
#define FGDMA_SRC_TC_BDL_SIZE_SET(x)       SET_REG32_BITS((x), 6U, 4U)
#define FGDMA_SRC_TC_BDL_LEN_SET(x)        SET_REG32_BITS((x), 15U, 8U)
    u32 src_tc;     /* 0x10, 源传输控制位 */
#define FGDMA_DST_TC_BDL_BURST_SET(x)      SET_REG32_BITS((x), 1U, 0U)
#define FGDMA_DST_TC_BDL_SIZE_SET(x)       SET_REG32_BITS((x), 6U, 4U)
#define FGDMA_DST_TC_BDL_LEN_SET(x)        SET_REG32_BITS((x), 15U, 8U)
    u32 dst_tc;     /* 0x14, 目的传输控制 */
    u32 total_bytes;/* 0x18, 传输数据总量，以Byte为单位  */
    u32 ioc;        /* 0x1c, 该条目传输完成中断产生控制位  */
} __attribute__((__packed__)) FGdmaBdlDesc; /* BDL描述符 */
```

```c
/* gdma capacity mask  */

#define FGDMA_IRQ1_MASK BIT(0)   /* All Gdma channel share a single interrupt */
#define FGDMA_IRQ2_MASK BIT(1)   /* Each gdma channel owns an independent interrupt */
#define FGDMA_TRANS_NEED_RESET_MASK BIT(2) /* Gdma needs to be reset before transmission */

```


### 5.2  错误码定义

#define FGDMA_SUCCESS           : 成功      
#define FGDMA_ERR_NOT_INIT      : 驱动未初始化
#define FGDMA_ERR_CHAN_IN_USE   : 通道已经绑定无法分配
#define FGDMA_ERR_CHAN_NOT_INIT : 通道未初始化
#define FGDMA_ERR_INVALID_ADDR  : 传输地址非法
#define FGDMA_ERR_INVALID_SIZE  : 传输字节数非法
#define FGDMA_ERR_BDL_NOT_ENOUGH : BDL已经使用完


### 5.3. 用户API接口

#### FGdmaLookupConfig

```c
const FGdmaConfig *FGdmaLookupConfig(u32 instance_id)
```

Note:

- 获取GDMA控制器默认配置

Input:

- {u32} instance_id, GDMA控制器ID

Return:

- {const FGdmaConfig *} 控制器默认配置

#### FGdmaCfgInitialize

```c
FError FGdmaCfgInitialize(FGdma *const instance_p, const FGdmaConfig *input_config)
```

Note:

- 初始化GDMA控制器实例

Input:

- FGdma *const instance_p, GDMA控制器实例
- const FGdmaConfig *input_config, GDMA控制器配置

Return:

- {FError} 返回FGDMA_SUCCESS表示初始化成功，返回其它表示失败

#### FGdmaDeInitialize

```c
void FGdmaDeInitialize(FGdma *const instance_p)
```

Note:

- 去初始化GDMA控制器实例

Input:

- FGdma *const instance_p, GDMA控制器实例

Return:

- 无

#### FGdmaAllocateChan

```c
FError FGdmaAllocateChan(FGdma *const instance_p, FGdmaChan *const dma_chan, 
						 const FGdmaChanConfig *dma_chan_config)
```

Note:

- 分配指定GDMA通道

Input:

- FGdma *const instance_p, GDMA控制器实例
- FGdmaChan *const dma_chan, GDMA通道实例
- const FGdmaChanConfig *dma_chan_config, GDMA通道配置

Return:

- {FError} FGDMA_SUCCESS表示分配成功，返回其它值表示分配失败

#### FGdmaDellocateChan

```c
FError FGdmaDellocateChan(FGdmaChan *const dma_chan)
```

Note:

- 释放GDMA通道

Input:

- FGdmaChan *const dma_chan, GDMA通道实例

Return:

- {FError} FGDMA_SUCCESS表示处理成功

#### FGdmaDirectTransfer

```c
FError FGdmaDirectTransfer(FGdmaChan *const chan_p, uintptr src_addr, uintptr dst_addr, fsize_t data_len);

```

Note:

- 直接操作模式下发起DMA传输

Input:

- FGdmaChan *const chan_p, GDMA通道实例
- uintptr src_addr, 传输源地址
- uintptr dst_addr, 传输目的地址

Return:

- {FError} FGDMA_SUCCESS表示传输成功

#### FGdmaAppendBDLEntry

```c
FError FGdmaAppendBDLEntry(FGdmaChan *const chan_p, uintptr src_addr, uintptr dst_addr, fsize_t data_len)
```

Note:

- 设置BDL描述符的一个条目

Input:

- FGdmaBdlDesc *desc_entry, 一条BDL描述符
- uintptr src_addr, 传输源地址
- uintptr dst_addr, 传输目的地址
- fsize_t data_len, 传输数据长度

Return:

- {FError} FGDMA_SUCCESS 表示设置成功

#### FGdmaBDLTransfer

```c
FError FGdmaBDLTransfer(FGdmaChan *const chan_p)
```

Note:

- BDL操作模式下发起DMA传输

Input:

- FGdmaChan *const chan_p, DMA通道实例

Return:

- {FError} FGDMA_SUCCESS 表示传输成功

#### FGdmaStart

```c
FError FGdmaStart(FGdma *const instance_p)
```

Note:

- 使能启动GDMA控制器
- 先调用此函数，后调用FGdmaAllocateChan配置特定通道

Input:

- FGdma *const instance_p, GDMA控制器实例

Return:

- {FError} FGDMA_SUCCESS表示启动成功

#### FGdmaStop

```c
FError FGdmaStop(FGdma *const instance_p)
```

Note:

- 停止GDMA控制器

Input:

- FGdma *const instance_p, GDMA控制器实例

Return:

- {FError} FGDMA_SUCCESS表示处理成功

#### FGdmaIrqHandler

```c
void FGdmaIrqHandler(s32 vector, void *args)
```

Note:

- 当 FGdmaConfig.caps 为FGDMA_IRQ1_MASK 特性时，各通道统一上报至一个中断，选择使用此函数作为中断处理函数

Input:

- {s32} vector, 中断号
- {void} *args, 中断参数

Return:

- 无


#### FGdmaIrqHandlerPrivateChannel
```c
void FGdmaIrqHandlerPrivateChannel(s32 vector, void *args)
```

Note:

- 当 FGdmaConfig.caps 为FGDMA_IRQ2_MASK 特性时，各通道独立上报中断，选择使用此函数作为中断处理函数

Input:

- {s32} vector, 中断号
- {void} *args, 中断参数

Return:

- 无

#### FGdmaChanRegisterEvtHandler

```c
void FGdmaChanRegisterEvtHandler(FGdmaChan *const chan_p, FGdmaChanEvtType evt, 
                                 FGdmaChanEvtHandler handler, void *handler_arg)
```

Note:

- 注册GDMA通道事件回调函数

Input:

- {FGdmaChan} *chan_p, GDMA通道实例
- {FGdmaChanEvtType} evt, 通道事件
- {FGdmaChanEvtHandler} handler, 事件回调函数
- {void} *handler_arg, 事件回调函数输入参数

Return:

- 无
