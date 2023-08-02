# FDDMA 驱动程序

## 1. 概述

DDMA(Device Direct Memory Access)是E2000提供的一个通用DMA控制模块，支持典型的DMA操作，提供多个DMA通道，多个通道可以同时工作，独立配置给不同外设使用

## 2. 功能

FDDMA 驱动程序主要完成 DDMA 模块的初始化，DDMA通道的分配与释放，
相关源文件为：
```
fddma
    .
    ├── fddma.c
    ├── fddma.h
    ├── fddma_g.c
    ├── fddma_hw.c
    ├── fddma_hw.h
    ├── fddma_intr.c
    ├── fddma_selftest.c
    └── fddma_sinit.c
```

## 3. 配置方法

以下部分将指导您完成 FDDMA 驱动的软件配置:

- 初始化 DDMA 控制器
- 配置 DDMA 通道，与外设完成绑定
- 启动 DDMA 通道 

## 4 应用示例

### [通过DDMA搬运SPI数据完成回环测试](../../../baremetal/example/peripheral/dma/fddma_spi)

## 5. API参考

### 5.1. 用户数据结构

#### FDdmaConfig

- DDMA 实例配置

```c
typedef struct
{
    u32 id;                     /* DDMA ctrl id */
    uintptr base_addr;          /* DDMA ctrl base address */
    u32 irq_num;                /* DDMA ctrl interrupt id */
    u32 irq_prority;            /* DDMA ctrl interrupt priority */
} FDdmaConfig; /* DDMA instance configuration */
```

#### FDdmaChanConfig

- DDMA 通道配置

```c
typedef struct
{
    FDdmaChanIndex id;          /* DMA channel index */
    u32 slave_id;               /* Perpherial slave id for DDMA */
    FDdmaChanRequst req_mode;   /* DMA transfer direction */
    uintptr ddr_addr;           /* DMA channel DDR address, could be source or destination */
    u32 dev_addr;               /* DMA channel Perpherial, could be source or destination */
    u32 trans_len;              /* DMA channel transfer length */
#define FDDMA_MIN_TRANSFER_LEN      4  /* min bytes in transfer */
    u32 timeout;                /* timeout = 0 means no use DMA timeout */
} FDdmaChanConfig;  /* DDMA channel instance */
```

#### FDdmaChan

- DDMA 通道实例

```c
typedef struct FDdmaChan_
{
    FDdmaChanConfig config; /* DDMA channel configuration */
    boolean is_used;        /* TRUE means channel is in use */
    FDdma *dma;             /* DMA instance of this channel */
    FDdmaChanEvtHandler evt_handler[FDDMA_NUM_OF_CHAN_EVT]; /* interrupt evt */
    void *evt_handler_args[FDDMA_NUM_OF_CHAN_EVT]; /* interrupt evt args */
} FDdmaChan; /* DDMA channel instance */
```

#### FDdma

- DDMA 控制器实例

```c
typedef struct FDdma_
{
    FDdmaConfig config;  /* DDMA instance configuration */
    FDdmaChan   *chan[FDDMA_NUM_OF_CHAN];  /* DDMA channel instance, NULL means channel not yet allocate */
    u32 is_ready;        /* TRUE means DDMA init ok */
    u32 bind_status;     /* channel bind status, BIT(n) = 1 means channel n is allocated */
} FDdma; /* DDMA instance */
```

### 5.2  错误码定义


- FDDMA_SUCCESS                   : 成功  
- FDDMA_ERR_NOT_INIT              ：驱动未初始化
- FDDMA_ERR_CHAN_BINDED           ：通道已经绑定无法分配
- FDDMA_ERR_CHAN_RUNNING          : 通道正在工作无法分配
- FDDMA_ERR_INVALID_TRANS_SIZE    : DMA传输字节数不合法
- FDDMA_ERR_WAIT_TIMEOUT          : DMA等待超时
- FDDMA_ERR_INVALID_DDR_ADDR      : DMA传输地址不合法

### 5.3. 用户API接口

#### FDdmaLookupConfig


```c
const FDdmaConfig *FDdmaLookupConfig(u32 instance_id);
```

Note:

- 获取DDMA实例默认配置 

Input:

- {u32} instance_id, DDMA实例号

Return:

- {const FDdmaConfig *} DDMA控制器默认配置

#### FDdmaCfgInitialization


```c
FError FDdmaCfgInitialization(FDdma *const instance, const FDdmaConfig *input_config);
```

Note:

- 初始化DDMA控制器

Input:

- {FDdma} *instance, DDMA控制器实例
- {FDdmaConfig} *input_config, DDMA控制器配置

Return:

- {FError} FDDMA_SUCCESS表示初始化成功，其它返回值表示初始化失败

#### FDdmaDeInitialization


```c
void FDdmaDeInitialization(FDdma *const instance);
```

Note:

- 去初始化DDMA控制器

Input:

- {FDdma} *instance, DDMA控制器实例

Return:

- 无

#### FDdmaAllocateChan

```c
FError FDdmaAllocateChan(FDdma *const instance, FDdmaChan *const dma_chan, const FDdmaChanConfig *dma_chan_config);
```

Note:

- 按照配置分配并使能DDMA通道

Input:

- {FDdma} *instance, DDMA控制器实例
- {FDdmaChan} *dma_chan, DDMA通道实例
- {FDdmaChanConfig} *dma_chan_config, DDMA通道配置

Return:

- {FError} FDDMA_SUCCESS表示分配成功，其它返回值表示分配失败

#### FDdmaDellocateChan

```c
FError FDdmaDellocateChan(FDdmaChan *const dma_chan);
```

Note:

- 释放之前分配的DDMA通道

Input:

- {FDdmaChan} *dma_chan, DDMA控制器实例

Return:

- {FError} FDDMA_SUCCESS表示释放成功，其它返回值表示释放失败

#### FDdmaStart

```c
FError FDdmaStart(FDdma *const instance);
```

Note:

- 启动DDMA控制器，开始传输

Input:

- {FDdma} *instance, DDMA控制器实例

Return:

- {FError} FDDMA_SUCCESS表示启动成功，其它返回值表示启动失败

#### FDdmaStop

```c
FError FDdmaStop(FDdma *const instance);
```

Note:

- 停止DDMA控制器

Input:

- {FDdma} *instance, DDMA控制器实例

Return:

- {FError} FDDMA_SUCCESS表示停止成功，其它返回值表示停止失败

#### FDdmaIrqHandler

```c
void FDdmaIrqHandler(s32 vector, void *args)
```

Note:

- DDMA中断处理函数 

Input:

- {s32} vector
- {void} *param, 输入参数

Return:

- 无

#### FDdmaRegisterChanEvtHandler

```c
void FDdmaRegisterChanEvtHandler(FDdmaChan *const dma_chan,
                                 FDdmaChanEvt evt, 
                                 FDdmaChanEvtHandler handler, 
                                 void *handler_arg);
```

Note:

- 注册DDMA通道中断响应事件函数 

Input:

- {FDdmaChan} *dma_chan, DDMA通道
- {FDdmaChanEvt} evt, 中断事件
- {FDdmaChanEvtHandler} handler, 中断响应事件函数
- {void} *handler_arg, 中断响应事件函数输入参数

Return:

- 无