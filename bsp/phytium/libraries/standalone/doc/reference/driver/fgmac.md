# FGMAC 驱动程序

## 1. 概述

以太网控制器（GMAC）的主要功能是在兼容 IEEE802.3-2005 标准的以太网中发送和接收数据，支持 RGMII 的 PHY 接口

GMAC 接口特点包括
- 支持速率 1000Mbps/100Mbps/10Mbps
- 支持 IEEE 802.3-2005 Ethernet MAC，Reduced Gigabit Media Independent Interface (RGMII)

## 2. 功能

FGMAC 驱动程序提供了以太网控制器初始化，发送/接收数据和配置PHY接口等功能

FGMAC 驱动程序的源文件包括，

```
├── Kconfig
├── fgmac.c 
├── fgmac.h
├── fgmac_dma.c
├── fgmac_g.c
├── fgmac_hw.c
├── fgmac_hw.h
├── fgmac_intr.c
├── fgmac_sinit.c
└── phy
    ├── ar803x
    │   ├── fgmac_ar803x.c
    │   └── fgmac_ar803x.h
    ├── fgmac_phy.c
    └── fgmac_phy.h
```

## 3. 配置方法

以下部分将指导您完成 FGMAC 驱动的硬件/软件配置:

- 选择开发板上的特定 GMAC 控制器，连通网线
- 通过驱动 API，获取指定 GMAC 控制器的默认配置
- 按需要修改获取的 GMAC 默认配置，通过驱动API，进行 GMAC 控制器的初始化
- 通过驱动API，获取 PHY 的默认配置
- 按需要修改获取的 PHY 默认配置，通过驱动API，进行 PHY 的初始化
- 分配 GMAC 数据传输使用的 DMA 描述符和 DMA 缓存区，通过驱动 API 进行注册
- 通过驱动 API 发送/接收数据

网络通信依赖协议栈，可以参考应用例程，使用LWIP网络协议栈进行通信，

## 4 应用示例

### [fgmac_link](../../../baremetal/example/fgmac_link/README.md)

启动GMAC，接收网络数据并打印

### [fgmac_lwip_echo](../../../baremetal/example/fgmac_lwip_echo/README.md)

启动LWIP网络协议栈，通过FGMAC驱动，支持开发板和网络主机的ping通

### [fgmac_lwip_tftp](../../../baremetal/example/fgmac_lwip_tftp/README.md)

启动LWIP网络协议栈，通过FGMAC驱动，支持开发板通过tftp服务获取文件

## 5. API参考

### 5.1. 用户数据结构

- FGMAC 驱动配置数据
```c
typedef struct
{
    u32     instance_id;  /* device instance id */
    uintptr base_addr;    /* device base address */
    u32     irq_num;      /* irq num */
    u32     cheksum_mode; /* hardware or software checksum */
    u32     duplex_mode;         /* selects the MAC duplex mode: Half-Duplex or Full-Duplex mode */    
    u32 max_packet_size;  /* max num of bytes in frame transfer */
    u32     mdc_clk_hz;          /* MDC clock access PHY. [1.0MHz ~2.5MHz] */
    boolean en_auto_negtiation;  /* auto-negotiation or not */
    u32     speed;               /* sets the Ethernet speed: 10/100/1000 Mbps.*/
  
} FGmacConfig; /* FGMAC 驱动配置数据 */
```

- FGMAC 驱动控制数据
```c

typedef struct
{
    FGmacConfig config;      /* Current active configs */
    u32         is_ready;    /* Device is initialized and ready */
    FGmacRingDescData rx_ring;  /* RX DMA descriptor data (idx, length) */
    volatile FGmacDmaDesc *rx_desc;  /* RX DMA descriptor table in ring */
    FGmacRingDescData tx_ring; /* TX DMA descriptor data (idx, length) */
    volatile FGmacDmaDesc *tx_desc; /* TX DMA descriptor table in ring */
    FGmacEvtHandler evt_handler[FGMAC_INTR_EVT_NUM]; /* User registered interrupt handler */
    u32 phy_valid_mask; 
    u32 phy_speed;
    u32 phy_addr;            /* phy ic addr */
} FGmac; /* FGMAC 驱动控制数据 */
```

- FGMAC DMA描述符

```c
typedef struct
{
    volatile u32 status;
    u32 ctrl;
    u32 buf_addr;
    u32 next;
} FGmacDmaDesc; 
```

- FGMAC DMA描述符表(链式)相关数据
```c
typedef struct
{
    u32 desc_idx;       /* For Current Desc position */
    u32 desc_buf_idx;   /* For Current Desc buffer buf position */
    u32 desc_max_num;   /* Max Number for  Desc and Desc buffer */
    u8 *desc_buf_base;  /*  Desc buffer Base */
} FGmacRingDescData; 
```

- FGMAC 校验方法选择
```c
enum
{
    FGMAC_CHECKSUM_BY_SOFTWARE = 0,
    FGMAC_CHECKSUM_BY_HARDWARE
}; 
```

- FGMAC 中断事件类型
```c
enum
{
    FGMAC_TX_COMPLETE_EVT = 0,
    FGMAC_RX_COMPLETE_EVT,
    FGMAC_LINK_STATUS_EVT,
    FGMAC_PHY_STATUS_EVT,
    FGMAC_DMA_ERR_EVT,

    FGMAC_INTR_EVT_NUM
};
```

### 5.2  错误码定义

- 模块错误码编号：0x1070000
- [0x0] FGMAC: Success
- [0x1070001] FGMAC: wait timeout
- [0x1070002] FGMAC: DMA address invalid
- [0x1070003] FGMAC: driver not ready
- [0x1070004] FGMAC: data transaction failed
- [0x1070005] FGMAC: PHY type not support
- [0x1070006] FGMAC: PHY is not found

### 5.3. 用户API接口

#### FGmacLookupConfig

- 获取FGMAC驱动的默认配置参数

```c
const FGmacConfig *FGmacLookupConfig(u32 instance_id);
```

Note:

- 返回FGMAC的默认配置，复制后修改配置
- 需要确认当前平台支持输入的instance_id

Input:

- {u32} instance_id, 驱动控制器号

Return:

- {const FGmacConfig *}, 驱动默认配置
#### FGmacCfgInitialize

- 完成FGMAC驱动实例的初始化，使之可以使用

```c
FError FGmacCfgInitialize(FGmac *instance_p, const FGmacConfig *cofig_p);
```

Note:

- 此函数会重置FGMAC控制器和FGMAC控制数据

Input:

- {FGmac} *instance_p 驱动控制数据

- {FGmacConfig} *cofig_p 驱动配置数据

Return:

- {FError} 驱动初始化的错误码信息，FGMAC_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FGmacDeInitialize

- 完成FGMAC驱动实例去使能，清零实例数据

```c
FError FGmacDeInitialize(FGmac *instance_p);
```

Note:

- 此函数会重置FGMAC控制数据

Input:

- {FGmac} *instance_p 驱动控制数据

Return:

- {FError} 驱动初始化的错误码信息，FGMAC_SUCCESS 表示去初始化成功，其它返回值表示去初始化失败

#### FGmacSetupTxDescRing

- 配置FGMAC的发送DMA描述符和缓冲区

```c
FError FGmacSetupTxDescRing(FGmac *instance_p, volatile FGmacDmaDesc *tx_desc_tbl, u8 *tx_buf, const fsize_t tx_pre_buf_len, const fsize_t tx_buf_num);
```

Note:

- 传入的tx_desc_tbl和tx_buf必须为32位空间地址

Input:

- {FGmac *}instance_p 驱动控制数据

- {volatile FGmacDmaDesc *} tx_desc_tbl 发送DMA描述符表(数组)

- {u8} *tx_buf 发送DMA缓冲区(数组，每一个描述符对应一个缓冲区)

- {const fsize_t} tx_pre_buf_len 单个DMA缓冲区的字节数

- {const fsize_t} tx_buf_num DMA描述符或者DMA缓存区的数目

Return:

- {FError} TX DMA初始化的错误码信息，FGMAC_SUCCESS 表示TX DMA初始化成功，其它返回值表示TX DMA初始化失败

#### FGmacSetupRxDescRing

- 配置FGMAC的接收DMA描述符和缓冲区

```c
FError FGmacSetupRxDescRing(FGmac *instance_p, volatile FGmacDmaDesc *rx_desc_tbl, u8 *rx_buf, const fsize_t rx_pre_buf_len, const fsize_t rx_buf_num);
```

Note:

- 传入的rx_desc_tbl和rx_buf必须为32位空间地址

Input:

- {FGmac *}instance_p 驱动控制数据
- {volatile FGmacDmaDesc *} rx_desc_tbl 接收DMA描述符表(数组)
- {u8} *rx_buf 接收DMA缓冲区(数组，每一个描述符对应一个缓冲区)
- {const fsize_t} rx_pre_buf_len 单个DMA缓冲区的字节数
- {const fsize_t} rx_buf_num DMA描述符或者DMA缓存区的数目

Return:

- {FError} RX DMA初始化的错误码信息，FGMAC_SUCCESS 表示RX DMA初始化成功，其它返回值表示RX DMA初始化失败

#### FGmacInterruptHandler

- FGMAC中断处理函数

```c
void FGmacInterruptHandler(s32 vector, void *param);
```

Note:

- 此函数运行在中断上下文

Input:

- {s32} vector, 中断向量号，此处没有用到
- {void} *param, 中断输入参数，此处传入的是FGMAC的驱动控制数据

Return:

无

#### FGmacRegisterEvtHandler

- 注册FGMAC中断事件响应函数

```c
void FGmacRegisterEvtHandler(FGmac *instance_p, u32 evt, FGmacEvtHandler handler);
```

Note:

- 注册的函数handler会在中断上下文执行

Input:

- {FGmac} *instance_p 驱动控制数据
- {u32} evt 中断事件类型
- {FGmacEvtHandler} handler 中断事件响应函数

Return:

无

#### FGmacStartTrans

- 使能FGMAC DMA，使之可以接收/发送数据

```c
FError FGmacStartTrans(FGmac *instance_p);
```

Note:

- 调用函数前需要确保FGMAC驱动初始化成功

Input:

- {FGmac} *instance_p 驱动控制数据

Return:

- {FError} FGMAC_SUCCESS 表示启动成功，其它返回值表示启动失败

#### FGmacStopTrans

- 去使能FGMAC DMA, 使之不再能接收/发送数据

```c
FError FGmacStopTrans(FGmac *instance_p);
```

Note:

- 调用函数前需要确保FGMAC驱动初始化成功

Input:

- {FGmac} *instance_p 驱动控制数据

Return:

- {FError} FGMAC_SUCCESS 表示去启动成功，其它返回值表示去启动失败

#### FGmacRecvFrame

- 通过FGMAC接收数据帧

```c
FError FGmacRecvFrame(FGmac *instance_p)
```

Note:

- 调用函数前需要确保FGMAC驱动初始化成功

Input:

- {FGmac} *instance_p 驱动控制数据

Return:

- {FError} FGMAC_SUCCESS 表示接收数据帧成功，其它返回值表示接收数据帧失败

#### FGmacSendFrame

- 通过FGMAC发送数据帧

```c
FError FGmacSendFrame(FGmac *instance_p, u32 frame_len);
```

Note:

- 通过FGMAC发送数据帧

Input:

- {FGmac} *instance_p 驱动控制数据

- {u32} frame_len 数据帧长度

Return:

- {FError} FGMAC_SUCCESS 表示发送数据帧成功，其它返回值表示发送数据帧失败


#### FGmacPhyLookupConfig

- 获取FGMAC PHY默认配置参数 

```c
void FGmacPhyLookupConfig(u32 gmac_instance_id, FGmac *instance_p);
```

Note:

调用此函数前确保 FGMAC 驱动初始化已经成功

Input:

- {u32} gmac_instance_id FGMAC id
- {FGmac} *instance_p FGMAC 控制数据

Return:

无

#### FGmacPhyCfgInitialize

- 查找GMAC连接的phy芯片地址，完成FGMAC PHY驱动实例的初始化，使之可以使用

```c
FError FGmacPhyCfgInitialize(FGmac *instance_p);
```

Note:

- 调用此函数前确保 FGMAC 驱动初始化已经成功

Input:

- {FGmac} *instance_p GMAC控制数据

Return:

- {FError} FGMAC_SUCCESS 表示PHY设置成功，其它返回值表示PHY设置失败

#### FGmacSetInterruptMask

- 设置FGMAC中断屏蔽位

```c
void FGmacSetInterruptMask(FGmac *instance_p, u32 intr_type, u32 mask, boolean enable);
```

Note:

- 在FGMAC驱动初始化成功后调用此函数

Input:

- {FGmac} *instance_p 驱动控制数据

- {u32} intr_type 中断类型 GMAC中断/DMA中断

- {u32} mask 中断屏蔽标志位

- {boolean} enable TRUE: 使能中断，FALSE: 去使能中断

Return:

无
