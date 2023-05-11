<!--
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: fxmac.md
 * Date: 2022-07-12 15:31:05
 * LastEditTime: 2022-07-12 15:31:05
 * Description:  This file is for 
 * 
 * Modify History: 
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
-->
# FXMAC 驱动程序

## 1. 概述

以太网控制器（XMAC）的主要功能是在兼容 IEEE802.3 standard 标准的以太网中发送和接收数据，当前支持 SGMII/RGMII 的 PHY 接口

XMAC 接口特点包括
- 支持速率 1000Mbps/100Mbps/10Mbps
- 支持 Reduced Gigabit Media Independent Interface (RGMII)
- 支持 SGMII Serial Gigabit Media-Independent Interface （SGMII）

## 2. 功能

XMAC 驱动提供了以太网控制器的初始化，DMA 环形队列使用函数，外部PHY 接口相关的配置功能

XMAC 驱动程序的源文件包括，

```
.
├── fxmac_bd.h
├── fxmac_bdring.c
├── fxmac_bdring.h
├── fxmac.c
├── fxmac_g.c
├── fxmac.h
├── fxmac_hw.h
├── fxmac_intr.c
├── fxmac_options.c
├── fxmac_phy.c
├── fxmac_phy.h
├── fxmac_sinit.c
├── Kconfig
└── phy
    ├── eth_ieee_reg.h
    └── yt
        ├── phy_yt.c
        └── phy_yt.h
```

- 其中fxmac.h/fxmac.c 为开发者提供以下功能：
1. mac 控制器实例初始化
2. 设置每个控制器实例中4个mac地址的接口
3. 设置每个控制器实例中4个mac匹配地址的接口
4. 外置phy 芯片交互接口
5. 中断相关接口

- 其中fxmac_bdring.h/fxmac_bdring.c 为开发者提供了以下功能：
1.  创建dma 环形队列
2.  环形队列数据拷贝
3.  环形队列描述符分配
4.  环形队列描述符释放



## 4 应用示例

### [fgmac_lwip_echo](../../../baremetal/example/fgmac_lwip_echo/README.md)

- 启动LWIP网络协议栈，通过FXMAC驱动，支持开发板和网络主机的ping通

### [lwip port](../../../third-party/lwip-2.1.2/ports/fxmac/)

- fxmac 耦合lwip 功能

## 5. API参考

### 5.1. 用户数据结构

- FXMAC 驱动配置数据
```c
    typedef struct
    {
        u32 instance_id; /* Id of device*/
        volatile uintptr_t base_address;
        volatile uintptr_t extral_mode_base;
        volatile uintptr_t extral_loopback_base;
        FXmacPhyInterface interface; /* 接口类型，提供SGMII/RGMII 选择 */
        u32 speed;    /* FXMAC_SPEED_XXX */
        u32 duplex;   /* 1 is full-duplex , 0 is half-duplex */
        u32 auto_neg; /* Enable auto-negotiation - when set active high, autonegotiation operation is enabled. */
        u32 pclk_hz;
        u32 max_queue_num; /* Number of Xmac Controller Queues  */
        u32 tx_queue_id;   /* 0 ~ FXMAC_QUEUE_MAX_NUM ,Index queue number */
        u32 rx_queue_id;   /* 0 ~ FXMAC_QUEUE_MAX_NUM ,Index queue number */
        u32 hotplug_irq_num;
        u32 dma_brust_length; /*  burst length */
        u32 network_default_config; /* mac 控制器默认配置 */
        u32 queue_irq_num[FXMAC_QUEUE_MAX_NUM]; /* mac0 8个 ，其他的 4个 */
    } FXmacConfig;
```

- FGMAC 驱动控制数据
```c
    typedef struct
    {
        FXmacConfig config;
        u32 is_ready; /* Device is ininitialized and ready*/
        u32 is_started; 
        u32 link_status; /* indicates link status ,FXMAC_LINKUP is link up ,FXMAC_LINKDOWN is link down,FXMAC_NEGOTIATING is need to negotiating*/
        u32 options;

        FXmacQueue tx_bd_queue; /* Transmit Queue */
        FXmacQueue rx_bd_queue; /* Receive Queue */

        FXmacIrqHandler send_irq_handler;
        void *send_args;

        FXmacIrqHandler recv_irq_handler;
        void *recv_args;

        FXmacErrorIrqHandler error_irq_handler;
        void *error_args;

        FXmacIrqHandler link_change_handler;
        void *link_change_args;

        FXmacIrqHandler restart_handler;
        void *restart_args;

        u32 moudle_id; /* Module identification number */
        u32 max_mtu_size;
        u32 max_frame_size;

        u32 phy_address;                    /* phy address */
        u32 rxbuf_mask; /* Filter length */ /* 1000,100,10 */

    } FXmac;
```

- FGMAC DMA描述符

```c
    typedef struct
    {
        uintptr phys_base_addr; /* Physical address of 1st BD in list */
        uintptr base_bd_addr;   /* Virtual address of 1st BD in list */
        uintptr high_bd_addr;   /* Virtual address of last BD in the list */
        u32 length;             /* Total size of ring in bytes */
        u32 run_state;          /* Flag to indicate DMA is started */
        u32 separation;         /* Number of bytes between the starting address
                                  of adjacent BDs */
        FXmacBd *free_head;
        /* First BD in the free group */
        FXmacBd *pre_head; /* First BD in the pre-work group */
        FXmacBd *hw_head;  /* First BD in the work group */
        FXmacBd *hw_tail;  /* Last BD in the work group */
        FXmacBd *post_head;
        /* First BD in the post-work group */
        FXmacBd *bda_restart;
        /* BDA to load when channel is started */

        volatile u32 hw_cnt; /* Number of BDs in work group */
        u32 pre_cnt;         /* Number of BDs in pre-work group */
        u32 free_cnt;        /* Number of allocatable BDs in the free group */
        u32 post_cnt;        /* Number of BDs in post-work group */
        u32 all_cnt;         /* Total Number of BDs for channel */
    } FXmacBdRing;
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


### 5.2  错误码定义

- 模块错误码编号：0x1070000
- [0x0] FGMAC: Success
- FXMAC_ERR_INVALID_PARAM : Invalid parameter
- FXMAC_ERR_SG_LIST : dma ring out of sequence
- FXMAC_ERR_GENERAL :the number of BDs to allocate greater that the number of BDs in the preprocessing state.
- FXMAC_ERR_SG_NO_LIST : dma ring is not allocated
- FXMAC_ERR_PHY_BUSY  : if there is another PHY operation in progress
- FXMAC_PHY_IS_NOT_FOUND : phy is not found
- FXMAC_PHY_AUTO_AUTONEGOTIATION_FAILED : PHY autonegotiation is error
- FXMAC_ERR_MAC_IS_PROCESSING : MAC controllers are enabled together. As a result, some operations cannot be mirrored


### 5.3 初始化流程

1. FXmacLookupConfig 获取默认配置
2. 修改默认配置 中 phy interface 类型、协商模式
3. 初始化mac 模块
4. 初始化phy 模块
5. 初始化mac 中断
6. 初始化dma 模块
7. 根据mac 默认配置启动mac 功能


### 5.4. 用户API接口

#### FXmacLookupConfig

- 获取FXMAC驱动的默认配置参数

```c
const FXmacConfig *FXmacLookupConfig(u32 instance_id);
```

Note:

- 返回FXMAC的默认配置，复制后修改配置
- 需要确认当前平台支持输入的instance_id

Input:

- {u32} instance_id, 驱动控制器号

Return:

- {const FXmacConfig *}, 驱动默认配置
#### FXmacCfgInitialize

- 完成FGMAC驱动实例的初始化，使之可以使用

```c
FError FXmacCfgInitialize(FXmac *instance_p, const FXmacConfig *config_p)
```

Note:

- 此函数会重置FGMAC控制器和FGMAC控制数据

Input:

- {FXmac} *instance_p MAC 控制器实例指针

- {FXmacConfig} *cofig_p 控制器驱动配置数据

Return:

- {FError} 驱动初始化的错误码信息，FGMAC_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FXmacInitInterface

- 根据phy 接口类型 ，初始化mac 控制器配置

```c
void FXmacInitInterface(FXmac *instance_p)
```

Note:
- 此函数一般用于 PHY 芯片协商完成之后被调用，与PHY配置进行适配

Input:
- {FXmac}     *instance_p MAC 控制器实例指针

#### FXmacGetMacAddress

- 根据index 获取mac 地址

```c
void FXmacGetMacAddress(FXmac *instance_p, u8 *address_ptr, u8 index)
```

Input :

- {FGmac} *instance_p MAC 控制器实例指针
- {u8}  index MAC(0-3)地址的索引

Output :
- {u8}  *address_ptr 是指向缓冲区的指针当前MAC地址将被复制。


#### FXmacSetMacAddress

- 根据index 写入mac 地址

```c
FError FXmacSetMacAddress(FXmac *instance_p, u8 *address_ptr, u8 index);
```

Input :

- {FGmac} *instance_p MAC 控制器实例指针
- {u8}  *address_ptr 是指向缓冲区的指针当前MAC地址将被复制。
- {u8}  index MAC(0-3)地址的索引

Output :

- {FError} FT_SUCCESS 如果MAC地址设置成功

#### FXmacSetOptions

- 设置FXmac 中的相关配置信息

```c
FError FXmacSetOptions(FXmac *instance_p, u32 options, u32 queue_num)
```

Note:
- 必须在mac 控制器关闭的情况被调用

Input:
- {FGmac} *instance_p MAC 控制器实例指针
- {u32} options 是要设置的选项。 选项参数位于 fxmac.h 中的 FXMAC_****_OPTION 
- {u32} queue_num mac控制器中队列的选项，仅在 FXMAC_JUMBO_ENABLE_OPTION 配置时被使用

Return:
- {FError} FT_SUCCESS 设置成功

#### FXmacClearOptions

- 清除FXmac 中的相关配置信息

```c
FError FXmacClearOptions(FXmac *instance_p, u32 options, u32 queue_num)
```

Note:
- 必须在mac 控制器关闭的情况被调用

Input:
- {FGmac} *instance_p MAC 控制器实例指针
- {u32} options 是要设置的选项。 选项参数位于 fxmac.h 中的 FXMAC_****_OPTION 
- {u32} queue_num mac控制器中队列的选项，仅在 FXMAC_JUMBO_ENABLE_OPTION 配置时被使用

Return:
- {FError} FT_SUCCESS 清除成功

#### FXmacStart

- 启动以太网控制器

```c
void FXmacStart(FXmac *instance_p)
```

note:

- 根据 network_default_config 中的 FXMAC_TRANSMIT_ENABLE_OPTION 与 
FXMAC_RECEIVER_ENABLE_OPTION ，决定是否开启控制器的接收与发送功能。并且默认开启接收与发送相关中断

Input:

- {FGmac} *instance_p MAC 控制器实例指针


#### FXmacStop

- 关闭以太网控制器

```c
void FXmacStop(FXmac *instance_p)
```

note:
- 关闭所有中断，关闭接收与发送功能

Input:

- {FGmac} *instance_p MAC 控制器实例指针


#### FXmacSetQueuePtr

- 设置mac 控制器中接收/发送缓冲区 的描述符环形队列的首地址

```c
void FXmacSetQueuePtr(FXmac *instance_p, uintptr queue_p, u8 queue_num,
                      u32 direction)
```

Note:
- 描述符环形队列的首地址按照128bit 对其

Input:

- {FXmac} *instance_p MAC 控制器实例指针
- {uintptr} queue_p 写入队列的地址
- {u8} queue_num 缓冲队列索引
- {u32} direction 当为 FXMAC_SEND 表示方向为发送，当为 FXMAC_RECV 表示方向为接收


#### FXmacPhyWrite

- 将数据写入指定的PHY寄存器。

```c
FError FXmacPhyWrite(FXmac *instance_p, u32 phy_address,
                     u32 register_num, u16 phy_data)
```

Note: 
- 这个函数不是线程安全的。 用户必须提供互斥的如果有多个线程可以调用该函数，则访问该函数。 

Input:
- {FXmac} *instance_p MAC 控制器实例指针
- {u32} phy_address 要写入的PHY的地址
- {u32} register_num 要写入的PHY的地址，特定PHY寄存器的寄存器号0-31 
- {u16} phy_data 需要写入对应PHY 芯片中 对应register_num 的参数

Return:

- {FError} FT_SUCCESS PHY 写入成功


#### FXmacPhyRead

- 指定PHY 芯片中对应的寄存器号，读出其中对应的参数

```c
FError FXmacPhyRead(FXmac *instance_p, u32 phy_address,
                    u32 register_num, u16 *phydat_aptr)
```

Note:

- 这个函数不是线程安全的。 用户必须提供互斥的如果有多个线程可以调用该函数，则访问该函数。 

Input:
- {FXmac} *instance_p MAC 控制器实例指针
- {u32} phy_address 要写入的PHY的地址
- {u32} register_num 要写入的PHY的地址，特定PHY寄存器的寄存器号0-31 

Output:
- {u16} *phydat_aptr  需要读出对应PHY 芯片中 对应register_num中值的指针
  
Return:

- {FError} FT_SUCCESS PHY 读入成功


#### FXmacPhyInit

- 初始化PHY 芯片 ，首先检查出当前已连接的PHY 芯片地址，然后根据协商方式，确定

```c
FError FXmacPhyInit(FXmac *instance_p, u32 speed,u32 duplex_mode, u32 autonegotiation_en);
```

Input:
- {FXmac} *instance_p MAC 控制器实例指针
- {u32} speed 需要设置的速度
- {u32} duplex_mode 双工模式配置，1为全双工，0 为半双工
- {u32} autonegotiation_en 为1 时，PHY 会进行自协商操作。为0时 ，将根据配置项进行协商

Return:
- FError FT_SUCCESS 初始化成功


#### FXmacSelectClk

- 根据MAC 与 PHY 芯片连接的情况，设置相关时钟参数

```c
void FXmacSelectClk(FXmac *instance_p )
```

Input:
- {FXmac} *instance_p MAC 控制器实例指针


#### FXmacSetHandler

- 设置中断回调函数

```c
FError FXmacSetHandler(FXmac *instance_p, u32 handler_type, void *func_pointer, void *call_back_ref)
```

Input:
- {FXmac} *instance_p MAC 控制器实例指针
- {u32} handler_type 指示中断处理程序类型 ,具体参数参考 FXMAC_HANDLER_*** 
- {void } *func_pointer 回调函数接口 
- {void } *call_back_ref 回调函数的传入参数

