# FSDIO 驱动程序

## 1. 概述

SD/SDIO/eMMC控制器，主要支持SD卡，eMMC介质的访问能力，同时支持连接SDIO接口设备，目前 FSDIO 驱动已经支持 SD 卡的访问

## 2. 功能

FSDIO 驱动提供了SD/MMC卡的控制访问方法，
- 初始化SD/MMC控制器
- 以轮询方式发送/接收数据和命令

访问SD/MMC卡需要兼容一系列协议命令，这一部分驱动不提供，可以通过第三方框架sdmmc使用

驱动相关的源文件包括，
```
fsdio
    ├── fsdio.c
    ├── fsdio.h
    ├── fsdio_cmd.c
    ├── fsdio_dma.c
    ├── fsdio_g.c
    ├── fsdio_hw.h
    ├── fsdio_intr.c
    ├── fsdio_pio.c
    ├── fsdio_selftest.
```

## 3. 配置方法

以下部分将指导您完成 FSDIO 驱动的软件配置:

- 初始化 FSDIO 控制器
- 通过协议命令完成 SD/MMC 卡初始化
- 通过协议命令读写 SD/MMC 卡数据

## 4 应用示例


### [通过协议命令读写SD卡](../../../baremetal/example/storage/sdio_cmds)

## 5. API参考

### 5.1. 用户数据结构

#### FSdio

- SDIO intance

```c
typedef struct _FSdio
{
    FSdioConfig         config;      /* Current active configs */
    u32                 is_ready;    /* Device is initialized and ready */
    FSdioIDmaDescList   desc_list;   /* DMA descriptor list, valid in DMA trans mode */
    FSdioEvtHandler     evt_handlers[FSDIO_NUM_OF_EVT]; /* call-backs for interrupt event */
    void                *evt_args[FSDIO_NUM_OF_EVT]; /* arguments for event call-backs */
    FSdioRelaxHandler   relax_handler;
    u32                 prev_cmd; /* record previous command code */
} FSdio; /* SDIO intance */
```

#### FSdioConfig

- SDIO intance configuration

```c
typedef struct
{
    u32            instance_id; /* Device instance id */
    uintptr        base_addr;   /* Device base address */
    u32            irq_num;     /* Interrupt num */
    FSdioTransMode trans_mode;  /* Trans mode, PIO/DMA */
    FSdioSpeedType speed;       /* Trans speed type */
    FSdioVoltageType voltage;   /* Card voltage type */
    boolean        non_removable; /* No removeable media, e.g eMMC */
    boolean        filp_resp_byte_order; /* Some SD protocol implmentation may not do byte-order filp */
} FSdioConfig; /* SDIO intance configuration */
```
#### FSdioCmdData

- SDIO trans command and data 

```c
typedef struct 
{
    u32 cmdidx; /* command index */
    u32 cmdarg; /* command argument */
    u32 response[4]; /* command response buffer */
    u32 flag; /* command flags */
#define FSDIO_CMD_FLAG_NEED_INIT         BIT(1) /* need initialization */
#define FSDIO_CMD_FLAG_EXP_RESP          BIT(2) /* need reply */
#define FSDIO_CMD_FLAG_EXP_LONG_RESP     BIT(3) /* need 136 bits long reply */
#define FSDIO_CMD_FLAG_NEED_RESP_CRC     BIT(4) /* need CRC */
#define FSDIO_CMD_FLAG_EXP_DATA          BIT(5) /* need trans data */
#define FSDIO_CMD_FLAG_WRITE_DATA        BIT(6) /* need trans data to write card */
#define FSDIO_CMD_FLAG_READ_DATA         BIT(7) /* need trans data to read card */
#define FSDIO_CMD_FLAG_NEED_AUTO_STOP    BIT(8) /* need auto stop after command */
#define FSDIO_CMD_FLAG_ADTC              BIT(9) /* need ADTC */
#define FSDIO_CMD_FLAG_SWITCH_VOLTAGE    BIT(10) /* need switch voltage */
    FSdioData *data_p; /* SDIO trans data */
} FSdioCmdData; /* SDIO trans command and data */
```
#### FSdioIDmaDesc

- SDIO DMA descriptor

```c
typedef struct
{
    u32 attribute; /* ds0 */
#define FSDIO_IDMAC_DES0_DIC	BIT(1)/* 内部描述表不触发TI/RI中断 */
#define FSDIO_IDMAC_DES0_LD	    BIT(2)/* 数据的最后一个描述符 */
#define FSDIO_IDMAC_DES0_FD	    BIT(3)/* 数据的第一个描述符 */
#define FSDIO_IDMAC_DES0_CH	    BIT(4)/* 链接下一个描述符地址 */
#define FSDIO_IDMAC_DES0_ER	    BIT(5)/* 链表已经到达最后一个链表 */
#define FSDIO_IDMAC_DES0_CES	BIT(30)/* RINTSTS寄存器错误汇总 */
#define FSDIO_IDMAC_DES0_OWN	BIT(31)/* 描述符关联DMA，完成传输后该位置置0 */
    u32 non1; /* ds1 --> unused */
    u32 len; /* ds2 bit[25:13] buffer2 size，bit[12:0] buffer1 size*/
#define FSDIO_IDMAC_DES2_BUF1_MASK      GENMASK(12, 0)
#define FSDIO_IDMAC_DES2_BUF1_SIZE(x)  (FSDIO_IDMAC_DES2_BUF1_MASK & (x))
#define FSDIO_IDMAC_DES2_BUF2_MASK      GENMASK(25, 13)
#define FSDIO_IDMAC_DES2_BUF2_SIZE(x)  (FSDIO_IDMAC_DES2_BUF2_MASK & (x << 13))
    u32 non2; /* ds3 --> unused */
    u32 addr_lo; /* ds4 Lower 32-bits of Buffer Address Pointer 1 --> buffer 1 */
    u32 addr_hi; /* ds5 Upper 32-bits of Buffer Address Pointer 1 */
    u32 desc_lo; /* ds6 Lower 32-bits of Next Descriptor Address --> buffer 2 */
    u32 desc_hi; /* ds7 Upper 32-bits of Next Descriptor Address */
} __attribute__ ((packed)) __attribute((aligned(4))) FSdioIDmaDesc; /* SDIO DMA descriptor */

```

### 5.2  错误码定义

- FSDIO_SUCCESS           : 操作成功
- FSDIO_ERR_TIMEOUT       ：操作超时失败
- FSDIO_ERR_NOT_INIT      ：控制器未初始化
- FSDIO_ERR_SHORT_BUF     ：缓冲区大小不足
- FSDIO_ERR_NOT_SUPPORT   ：操作不支持
- FSDIO_ERR_INVALID_STATE ：控制器的状态不合法
- FSDIO_ERR_TRANS_TIMEOUT ：传输数据超时失败
- FSDIO_ERR_CMD_TIMEOUT   ：传输命令超时失败
- FSDIO_ERR_NO_CARD       ：卡不在位
- FSDIO_ERR_BUSY          : 卡处于繁忙状态

### 5.3. 用户API接口

#### FSdioLookupConfig

```c
const FSdioConfig *FSdioLookupConfig(u32 instance_id)
```

Note:

- Get the device instance default configure 

Input:

- {u32} instance_id

Return:

- {const FSdioConfig *} default configure

#### FSdioCfgInitialize

```c
FError FSdioCfgInitialize(FSdio *const instance_p, const FSdioConfig *input_config_p)
```

Note:

- initialization SDIO controller instance
- get into card-detect mode after initialization, bus width = 1, card freq = 400kHz

Input:

- {FSdio} *instance_p, SDIO controller instance
- {FSdioConfig} *input_config_p, SDIO controller configure

Return:

- {FError} FSDIO_SUCCESS if initialization success, otherwise failed

#### FSdioDeInitialize

```c
void FSdioDeInitialize(FSdio *const instance_p)
```

Note:

- deinitialization SDIO controller instance

Input:

- {FSdio} *instance_p, SDIO controller instance

Return:

- {NONE}

#### FSdioSetIDMAList

```c
FError FSdioSetIDMAList(FSdio *const instance_p, volatile FSdioIDmaDesc *desc, u32 desc_num)
```

Note:

- Setup DMA descriptor for SDIO controller instance

Input:

- {FSdio} *instance_p, SDIO controller instance
- {volatile FSdioIDmaDesc} *desc, first item in DMA descriptor lists
- {u32} desc_num, number of items in DMA descriptor lists

Return:

- {FError} FSDIO_SUCCESS if setup done, otherwise failed

#### FSdioSetClkFreq

```c
void FSdioSetClkFreq(FSdio *const instance_p, u32 input_clk_hz)
```

Note:

- Set the Card clock freqency

Input:

- {FSdio} *instance_p, SDIO controller instance
- {u32} input_clk_hz, Card clock freqency in Hz

Return:

- {None}

#### FSdioGetClkFreq

```c
u32 FSdioGetClkFreq(FSdio *const instance_p)
```

Note:

- Get the Card clock freqency

Input:

- {FSdio} *instance_p, SDIO controller instance

Return:

- {u32} real clock in Hz



#### FSdioDMATransfer

```c
FError FSdioDMATransfer(FSdio *const instance_p, FSdioCmdData *const cmd_data_p)
```

Note:

- Start command and data transfer in DMA mode

Input:

- {FSdio} *instance_p, SDIO controller instance
- {FSdioCmdData} *cmd_data_p, contents of transfer command and data

Return:

- {FError} FSDIO_SUCCESS if transfer success, otherwise failed

#### FSdioPollWaitDMAEnd

```c
FError FSdioPollWaitDMAEnd(FSdio *const instance_p, FSdioCmdData *const cmd_data_p)
```

Note:

- Wait DMA transfer finished by poll

Input:

- {FSdio} *instance_p, SDIO controller instance
- {FSdioCmdData} *cmd_data_p, contents of transfer command and data

Return:

- {FError} FSDIO_SUCCESS if wait success, otherwise wait failed

#### FSdioGetInterruptMask


```c
u32 FSdioGetInterruptMask(FSdio *const instance_p, FSdioIntrType type)
```

Note:

- Get SDIO controller interrupt mask

Input:

- {FSdio} *instance_p, SDIO controller instance
- {FSdioIntrType} type, Type of interrupt, controller/DMA interrupt

Return:

- {u32} interrupt mask bits

#### FSdioSetInterruptMask


```c
void FSdioSetInterruptMask(FSdio *const instance_p, FSdioIntrType type, u32 set_mask, boolean enable)
```

Note:

- Enable/Disable SDIO controller interrupt

Input:

- {FSdio} *instance_p, SDIO controller instance
- {FSdioIntrType} type, Type of interrupt, controller/DMA interrupt
- {u32} set_mask, interrupt mask bits
- {boolean} enable, TRUE: enable interrupt mask bits

Return:

- {NONE}

#### FSdioInterruptHandler

```c
void FSdioInterruptHandler(s32 vector, void *param)
```

Note:

- Interrupt handler for SDIO instance

Input:

- {s32} vector, Interrupt id
- {void} *param, Interrupt params, is SDIO instance

Return:

- {NONE}

#### FSdioRegisterEvtHandler

```c
void FSdioRegisterEvtHandler(FSdio *const instance_p, FSdioEvtType evt, FSdioEvtHandler handler, void *handler_arg)
```

Note:

- Register event call-back function as handler for interrupt events

Input:

- {FSdio} *instance_p, SDIO controller instance
- {FSdioEvtType} evt, interrupt event
- {FSdioEvtHandler} handler, event call-back function
- {void} *handler_arg, argument of event call-back function

Return:

- {NONE}


#### FSdioPIOTransfer

```c
FError FSdioPIOTransfer(FSdio *const instance_p, FSdioCmdData *const cmd_data_p)
```

Note:

- Start command and data transfer in PIO mode

Input:

- {FSdio} *instance_p, SDIO controller instance
- {FSdioCmdData} *cmd_data_p, contents of transfer command and data

Return:

- {FError} FSDIO_SUCCESS if transfer success, otherwise failed

#### FSdioPollWaitPIOEnd

```c
FError FSdioPollWaitPIOEnd(FSdio *const instance_p, FSdioCmdData *const cmd_data_p);
```

Note:

- Wait PIO transfer finished by poll

Input:

- {FSdio} *instance_p, SDIO controller instance
- {FSdioCmdData} *cmd_data_p, contents of transfer command and data

Return:

- {FError} FSDIO_SUCCESS if wait success, otherwise wait failed

#### FSdioGetCmdResponse

```c
FError FSdioGetCmdResponse(FSdio *const instance_p, FSdioCmdData *const cmd_data_p)
```

Note:

- Get cmd response and received data after wait poll status or interrupt signal

Input:

- {FSdio} *instance_p, SDIO controller instance
- {FSdioCmdData} *cmd_data_p, contents of transfer command and data

Return:

- {FError} FSDIO_SUCCESS if get success

#### FSdioRestart

```c
FError FSdioRestart(FSdio *const instance_p)
```

Note:

- reset controller from error state

Input:

- {FSdio} *instance_p, instance of controller

Return:

- {FError} FSDIO_SUCCESS if restart success
