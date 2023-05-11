# FSDMMC 驱动程序

## 1. 概述

SD/MMC控制器主要提供对固态非易失性存储的内存卡的访问能力，包括多媒体存储卡（MMC，MultiMedia Card）和安全和数据保护卡（SD，Secure Digital Card）。

## 2. 功能

SD/MMC控制器驱动提供了SD/MMC卡的控制访问方法，
- 初始化SD/MMC控制器
- 以轮询方式发送/接收数据和命令
- 以中断方式发送/接收数据和命令
- 设置SD/MMC控制器的中断工作模式和中断响应函数

访问SD/MMC卡需要兼容一系列协议命令，这一部分驱动不提供，可以通过第三方框架sdmmc使用

驱动相关的源文件包括，
```
fsdmmc
    ├── fsdmmc.c
    ├── fsdmmc.h
    ├── fsdmmc_dma.c
    ├── fsdmmc_dma.h
    ├── fsdmmc_g.c
    ├── fsdmmc_hw.c
    ├── fsdmmc_hw.h
    ├── fsdmmc_intr.c
    └── fsdmmc_sinit.c
```

## 3. 配置方法

以下部分将指导您完成 FSDMMC 驱动的软件配置:

- 初始化FSDMMC控制器
- 通过协议命令完成SD/MMC卡初始化
- 通过协议命令读写SD/MMC卡数据

## 4 应用示例

### [检测SD卡](../../../baremetal/example/peripheral/mmc/fsdmmc_probe)

### [SD/MMC卡协议实现](../../../third-party/sdmmc)

### [通过协议命令读写SD卡](../../../baremetal/example/storage/sdmmc_cmds)

### [通过文件系统使用SD卡](../../../baremetal/example/storage/sdmmc_fatfs)

## 5. API参考

### 5.1. 用户数据结构

- FSDMMC控制数据

```c
typedef struct
{
    FSdmmcConfig config;      /* Current active configs */
    u32          is_ready;    /* Device is initialized and ready */
    FSdmmcEventHandler evt_handler[FSDMMC_EVT_NUM];
    void         *evt_args[FSDMMC_EVT_NUM];
} FSdmmc; /* Device instance */
```

- FSDMMC配置数据

```c
typedef struct
{
    u32     instance_id; /* Device instance id */
    uintptr base_addr;   /* Device base address */
    u32     irq_num[FSDMMC_INTR_NUM];
} FSdmmcConfig;
```

- FSDMMC命令结构
```c
typedef struct 
{
    u32 cmdidx;
    u32 cmdarg;
    u32 resptype;
    u32 response[4];
    u32 flag;
#define FSDMMC_CMD_FLAG_NEED_STOP         BIT(0)
#define FSDMMC_CMD_FLAG_NEED_INIT         BIT(1)
#define FSDMMC_CMD_FLAG_EXP_RESP          BIT(2)
#define FSDMMC_CMD_FLAG_EXP_LONG_RESP     BIT(3)
#define FSDMMC_CMD_FLAG_NEED_RESP_CRC     BIT(4)
#define FSDMMC_CMD_FLAG_EXP_DATA          BIT(5)
#define FSDMMC_CMD_FLAG_WRITE_DATA        BIT(6)
#define FSDMMC_CMD_FLAG_READ_DATA         BIT(7)
#define FSDMMC_CMD_FLAG_NEED_AUTO_STOP    BIT(8)
#define FSDMMC_CMD_FLAG_ADTC              BIT(9)
    FSdmmcData *data_p;
} FSdmmcCmd;
```

- FSDMMC数据结构
```c
typedef struct 
{
    u8 *buf;
    u32 blksz;
    u32 blkcnt;
    u32 datalen;
} FSdmmcData;
```

- FSDMMC中断类型和中断事件
```c
enum
{
    FSDMMC_DMA_BD_INTR = 0,
    FSDMMC_CMD_INTR,
    FSDMMC_ERROR_INTR,

    FSDMMC_INTR_NUM  
}; /* 中断类型 */

enum
{
    FSDMMC_EVT_CARD_REMOVED = 0,
    FSDMMC_EVT_CMD_DONE,
    FSDMMC_EVT_CMD_ERROR,
    FSDMMC_EVT_CMD_RESP_ERROR,
    FSDMMC_EVT_DATA_ERROR,
    FSDMMC_EVT_DATA_READ_DONE,
    FSDMMC_EVT_DATA_WRITE_DONE,

    FSDMMC_EVT_NUM
}; /* 事件类型 */
```

### 5.2  错误码定义

- [0x0] FSDMMC_SUCCESS : success

- [0x10c0001] FSDMMC_ERR_NOT_READY : FSDMMC控制器未初始化

- [0x10c0001] FSDMMC_ERR_TIMEOUT : 数据或者命令传输等待超时

- [0x10c0001] FSDMMC_ERR_CMD_FAILED : 命令传输失败

- [0x10c0001] FSDMMC_ERR_DATA_FAILED : 数据传输失败

- [0x10c0001] FSDMMC_ERR_CARD_NO_FOUND : 卡未检测到

- [0x10c0001] FSDMMC_ERR_INVALID_BUF : 数据缓冲区不合法

### 5.3. 用户API接口

#### FSdmmcLookupConfig

- 获取FSDMMC控制器默认配置

```c
const FSdmmcConfig *FSdmmcLookupConfig(u32 instance_id);
```

Note:

- instance_id从0开始，取决于FSDMMC控制器的个数

Input:

- {u32} instance_id 驱动控制器ID

Return:

- {const FSdmmcConfig *}  FSDMMC默认配置，返回NULL如果找不到默认配置

#### FSdmmcCfgInitialize

- 初始化FSDMMC控制器, 使之可以使用

```c
FError FSdmmcCfgInitialize(FSdmmc *instance_p, const FSdmmcConfig *input_config_p);
```

Note:

- 输入配置通过FSdmmcLookupConfig获取，用户按照需要修改后传入此函数

Input:

- {FSdmmc} *instance_p FSDMMC驱动控制数据
- {FSdmmcConfig} *input_config_p FSDMMC用户输入配置

Return:

- {FError} 驱动初始化的错误码信息，FSDMMC_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FSdmmcDeInitialize

- 去使能FSDMMC控制器, 清零实例数据

```c
void FSdmmcDeInitialize(FSdmmc *instance_p);
```

Note:

- 无

Input:

- {FSdmmc} *instance_p FSDMMC驱动控制数据

Return:

- 无

#### FSdmmcPollTransfer

- 通过FSDMMC轮询方式发送/接收数据和命令

```c
FError FSdmmcPollTransfer(FSdmmc *instance_p, FSdmmcCmd *cmd_data_p);
```

Note:

- FSDMMC控制器初始化后才能调用此函数

Input:

- {FSdmmc} *instance_p FSDMMC驱动控制数据
- {FSdmmcCmd} *cmd_data_p FSDMMC数据和命令

Return:

- {FError} 驱动初始化的错误码信息，FSDMMC_SUCCESS 表示发送/接收成功，其它返回值表示发送/接收失败

#### FSdmmcInterruptTransfer

- 通过FSDMMC中断方式发送/接收数据和命令

```c
FError FSdmmcInterruptTransfer(FSdmmc *instance_p, FSdmmcCmd *cmd_data_p);
```

Note:

- FSDMMC控制器初始化后才能调用此函数，使用前需要确保FSDMMC中断设置完成

Input:

- {FSdmmc} *instance_p FSDMMC驱动控制数据
- {FSdmmcCmd} *cmd_data_p FSDMMC数据和命令

Return:

- {FError} 驱动初始化的错误码信息，FSDMMC_SUCCESS 表示发送/接收成功，其它返回值表示发送/接收失败

#### FSdmmcGetInterruptMask

- 获取FSDMMC的中断掩码

```c
u32 FSdmmcGetInterruptMask(uintptr base_addr, u32 intr_type);
```

Note:

- FSDMMC控制器初始化后才能调用此函数

Input:

- {uintptr} base_addr FSDMMC控制器基地址
- {u32} intr_type FSDMMC中断类型, 参考FSDMMC_INTR_NUM

Return:

- {u32} 中断掩码

#### FSdmmcSetInterruptMask

- 设置FSDMMC的中断掩码

```c
void FSdmmcSetInterruptMask(uintptr base_addr, u32 intr_type, u32 mask, boolean enable);
```

Note:

- FSDMMC控制器初始化后才能调用此函数

Input:

- {uintptr} base_addr FSDMMC控制器基地址
- {u32} intr_type FSDMMC中断类型, 参考FSDMMC_INTR_NUM
- {u32} mask 中断掩码
- {boolean} enable TRUE:打开中断, FALSE:关闭中断

Return:

- 无

#### FSdmmcCmdInterrupHandler

- 命令中断响应函数

```c
void FSdmmcCmdInterrupHandler(s32 vector, void *param);
```

Note:

- 此函数用于设置FSDMMC中断时注册，用户可以自定义一个中断响应函数替换此函数

Input:

- vector 中断向量号
- {void} *param 中断响应输入参数

Return:

- 无

#### FSdmmcDmaInterrupHandler

- DMA中断响应函数

```c
void FSdmmcDmaInterrupHandler(s32 vector, void *param);
```

Note:

- 此函数用于设置FSDMMC中断时注册，用户可以自定义一个中断响应函数替换此函数

Input:

- {s32} vector 中断向量号
- {void} *param 中断响应输入参数

Return:

- 无

#### FSdmmcErrInterrupHandler

- 错误中断响应函数

```c
void FSdmmcErrInterrupHandler(s32 vector, void *param);
```

Note:

- 此函数用于设置FSDMMC中断时注册，用户可以自定义一个中断响应函数替换此函数

Input:

- {s32} vector 中断向量号
- {void} *param 中断响应输入参数

Return:

- 无

#### FSdmmcRegisterInterruptHandler

- 注册中断事件响应函数

```c
void FSdmmcRegisterInterruptHandler(FSdmmc *instance_p, u32 event, FSdmmcEventHandler handler, void *args);
```

Note:

- 此函数用于设置FSDMMC中断时注册，被注册的函数被FSdmmcCmdInterrupHandler、FSdmmcErrInterrupHandler
 * 和FSdmmcDmaInterrupHandler调用

Input:

- {FSdmmc} *instance_p FSDMMC驱动控制数据
- {u32} event FSDMMC中断事件类型，参考FSDMMC_EVT_NUM
- {FSdmmcEventHandler} handler, FSDMMC中断事件响应函数

Return:

- 无
