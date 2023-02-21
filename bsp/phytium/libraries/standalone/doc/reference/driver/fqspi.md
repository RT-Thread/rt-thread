# FQSPI 驱动程序

## 1. 概述

- QSPI是Motorola公司推出的SPI接口的扩展，比SPI应用更加广泛。在SPI协议的基础上，Motorola公司对其功能进行了增强，大幅提升了数据交换能力。QSPI 是一种专用的通信接口，连接单、双或四（条数据线） SPI Flash 存储介质。

- 本驱动程序提供了FT2000/4、D2000、E2000平台的QSPI功能

- FT2000/4、D2000上包含 1 个通用 QSPI 接口控制器，作为QSPI Flash接口使用，片最大支持 2Gb（256MB）的容量，最大支持连接四个相同容量的Flash


## 2. 功能


- 驱动相关的源文件如下，
- drivers/qspi/fqspi

```
.
├── fqspi_norflash.c
├── fqspi_norflash.h
├── fqspi_g.c
├── fqspi_hw.c
├── fqspi_hw.h
├── fqspi_sinit.c
├── fqspi.h
└── fqspi.c
```


## 3. 配置方法


以下部分将指导您完成 FQSPI 驱动的软件配置:

### 3.1 使用 SFUD 通用SPI协议框架

- 使能 CONFIG_USE_QSPI 和 CONFIG_USE_SFUD 配置
- 初始化 SFUD 框架
- 调用 SFUD 提供的 API 读写 QSPI 设备

关于 SFUD 框架的使用，可以参考[sfud.md](./sfud.md)

### 3.2 不使用 SFUD 通用SPI协议框架

- 使能 CONFIG_USE_QSPI 配置
- 初始 QSPI 驱动
- 调用 QSPI 提供的 API 读写 QSPI 设备，需要按照 QSPI 设备的手册实现相关的命令和协议

## 4 应用示例

### [fqspi_nor_flash](../../../baremetal/example/peripheral/qspi/qspi_nor_flash/README.md)

### [qspi_sfud](../../../baremetal/example/storage/qspi_sfud/README.md)

## 4. API参考

### 4.1 用户数据结构

- QSPI 驱动配置数据
```c
typedef struct
{
    u32 instance_id;  /* Id of device */
    uintptr base_addr; /* Base address of qspi */
    uintptr mem_start; /* Start address of qspi memory */
    u32 capacity;    /* Flash capacity */
    u32 dev_num;      /* Qspi device number */
    u32 channel;     /* channel number */
} FQspiConfig;
```

- QSPI 驱动控制数据
```c
typedef struct
{
    FQspiConfig config;
    FQspiRdCfgDef rd_cfg;
    FQspiWrCfgDef wr_cfg;
    FQspiCommandPortDef cmd_def;
    FQspiCsTimingCfgDef cs_timing_cfg;
    u32 is_ready;    /**< Device is initialized and ready */
    u32 flash_size;  /* size of QSPI flash */
} FQspiCtrl;
```

- QSPI 传输命令协议，指定传输的指令、地址和修饰符、数据三者的宽度
```c
typedef enum
{
    FQSPI_TRANSFER_1_1_1 = 0x0,
    FQSPI_TRANSFER_1_1_2 = 0x1,
    FQSPI_TRANSFER_1_1_4 = 0x2,
    FQSPI_TRANSFER_1_2_2 = 0x3,
    FQSPI_TRANSFER_1_4_4 = 0x4,
    FQSPI_TRANSFER_2_2_2 = 0x5,
    FQSPI_TRANSFER_4_4_4 = 0x6
}FQspiTransferMode;
```

- QSPI Flash的容量大小
```c
typedef enum
{
    FQSPI_FLASH_CAP_4MB = 0b000,
    FQSPI_FLASH_CAP_8MB = 0b001,
    FQSPI_FLASH_CAP_16MB = 0b010,
    FQSPI_FLASH_CAP_32MB = 0b011,
    FQSPI_FLASH_CAP_64MB = 0b100,
    FQSPI_FLASH_CAP_128MB = 0b101,
    FQSPI_FLASH_CAP_256MB = 0b110,
} FQspiFlashCapcityType;
```

- QSPI的SCK分频系数
```c
typedef enum
{
    FQSPI_SCK_DIV_128 = 0x0,
    FQSPI_SCK_DIV_2 = 0x1,
    FQSPI_SCK_DIV_4 = 0x2,
    FQSPI_SCK_DIV_8 = 0x3,
    FQSPI_SCK_DIV_16 = 0x4,
    FQSPI_SCK_DIV_32 = 0x5,
    FQSPI_SCK_DIV_64 = 0x6
}FQspiSckDivType;
```

- QSPI的地址长度格式
```c
typedef enum
{
    FQSPI_ADDR_SEL_3 = 0x0,
    FQSPI_ADDR_SEL_4 = 0x1,
}FQspiAddrType;
```

### 4.2 错误码定义

- FQSPI_SUCCESS : fqspi success
- FQSPI_INVAL_PARAM : fqspi invalid input parameters
- FQSPI_NOT_READY : fqspi driver not ready
- FQSPI_NOT_ALLIGN : fqspi address not alligned
- FQSPI_NOT_SUPPORT : fqspi not support operation
- FQSPI_TIMEOUT : fqspi wait timeout

### 4.3 用户API接口

#### FQspiLookupConfig

- 获取FQSPI驱动的默认配置参数

```c
const FQspiConfig *FQspiLookupConfig(u32 instance_id)
```

Note:

- 用户可以通过此接口获取驱动默认配置的副本，进行修改后，作为`FQspiCfgInitialize`函数的入参使用

Input:

- u32 instance_id, 选择的FQSPI控制器实例号

Return:

- const FQspiConfig *, 返回的默认驱动配置，返回NULL表示失败


#### FQspiCfgInitialize

- 完成FQSPI驱动实例的初始化，使之可以使用

```c
FError FQspiCfgInitialize(FQspiCtrl *instance_p, const FQspiConfig *input_config_p);
```

Note:

- 此函数会重置FQSPI控制器和FQSPI控制数据

Input:

- FQspiCtrl *instance_p, FQSPI驱动控制数据

- const FQspiConfig *input_config_p, FQSPI驱动配置数据

Return:

- FError, 错误码信息，FQSPI_SUCCESS 表示初始化成功，其它返回值表示初始化失败


#### FQspiDeInitialize

- 完成FQSPI驱动实例去初始化，之后不能使用

```c
void FQspiDeInitialize(FQspiCtrl *instance_p)
```

Note:

- 此函数会重置FQSPI控制数据

Input:

- FQspiCtrl *instance_p, FQSPI驱动控制数据

Return:

无


#### FQspiCommandPortConfig
- 配置FQSPI命令端口寄存器的值

```c
FError FQspiCommandPortConfig(FQspiCtrl *pctrl)
```

Note:

- 使用此函数前需要确保FQSPI驱动初始化成功
- 配置FQSPI命令端口寄存器

Input:
 
- FQspiCtrl *pctrl, FQSPI驱动控制数据

Return:

- FError, 错误码信息，FQSPI_SUCCESS 表示数据读取成功，其它返回值表示读取失败


#### FQspiRdCfgConfig

- 配置FQSPI地址访问读配置寄存器的值

```c
FError FQspiRdCfgConfig(FQspiCtrl *pctrl)
```

Note:

- 使用此函数前需要确保FQSPI驱动初始化成功
- 配置QSPI地址访问读配置寄存器

Input:
 
- FQspiCtrl *pctrl, FQSPI驱动控制数据

Return:

- FError, 错误码信息，FQSPI_SUCCESS 表示数据读取成功，其它返回值表示读取失败


#### FQspiSetLdPortData

- 写FQSPI低位数据端口寄存器的值

```c
FError FQspiSetLdPortData(FQspiCtrl *pctrl, const u8 *buf, size_t len)
```

Note:

- 使用此函数前需要确保FQSPI驱动初始化成功
- 设置寄存器的值，可用于向flash传送数据

Input:
 
- FQspiCtrl *pctrl, FQSPI驱动控制数据

- const u8 *buf, 写缓存，存储要写入的数据

- size_t len, 要读取的buf长度

Return:

- FError, 错误码信息，FQSPI_SUCCESS 表示数据写入成功，其它返回值表示写入失败

#### FQspiFlashSpecialInstruction
- 读flash某些状态寄存器的值，此函数适配的flash型号为S25FS256S NorFlash芯片

```c
FError FQspiFlashSpecialInstruction(FQspiCtrl *pctrl, u8 cmd, u8 *buf, size_t len);
```

Note:

- 使用此函数前需要确保FQSPI驱动初始化成功
- 读取flash寄存器的值，主要支持RDID, RDSR1, RDSR2, RDCR指令

Input:
 
- FQspiCtrl *pctrl, FQSPI驱动控制数据

- u8 cmd, 读寄存器状态的指令，具体参见flash芯片手册

- u8 *buf, 读缓存，存储读到的寄存器值

- size_t len, 要读取的buf长度

Return:

- FError, 错误码信息，FQSPI_SUCCESS 表示数据读取成功，其它返回值表示读取失败

#### FQspiFlashWriteReg
- 写flash寄存器的值

```c
FError FQspiFlashWriteReg(FQspiCtrl *pctrl, u8 command, const u8 *buf, size_t len)
```

Note:

- 使用此函数前需要确保FQSPI驱动初始化成功

Input:

- FQspiCtrl *pctrl, FQSPI驱动控制数据

- u8 command, 写寄存器的指令

- const u8 *buf, 写缓存，存储写入的寄存器值

- size_t len, 要写入的buf长度

Return:

- FError, 错误码信息，FQSPI_SUCCESS 表示数据写入成功，其它返回值表示写入失败

#### FQspiFlashReadDataConfig

- 读flash配置

```c
FError FQspiFlashReadDataConfig(FQspiCtrl *pctrl, u8 command)
```

Note:

- 使用此函数前需要确保FQSPI驱动初始化成功
- 配置采用何种方式读flash中的数据，read、fast read、quad read

Input:

- FQspiCtrl *pctrl, FQSPI驱动控制数据

- u8 command 读flash数据的指令，具体参见flash芯片手册

Return:

- FError, 错误码信息，FQSPI_SUCCESS 表示读配置成功，其它返回值表示读配置失败

#### FQspiFlashReadData

- 读取norflash的数据

```c
size_t FQspiFlashReadData(FQspiCtrl *pctrl, u32 chip_addr, u8 *buf, size_t len)
```

Note:

- 使用此函数前需要确保FQSPI驱动初始化成功
- 使用此函数前需要使用FQspiFlashReadDataConfig函数配置读方式

Input:

- FQspiCtrl *pctrl, FQSPI驱动控制数据

- u32 chip_addr, 读数据的起始地址

- u8 *buf 读缓存, 存储读到的数据

- size_t len, 要读取的buf长度

Return:

- FError, 错误码信息，FQSPI_SUCCESS 表示数据读取成功，其它返回值表示读取失败

#### FQspiNorFlashWrite

- 写norflash数据函数 

```c
FError FQspiFlashWriteData(FQspiCtrl *pctrl, u8 command, u32 chip_addr, const u8 *buf, size_t len)
```

Note:

- 使用此函数前需要确保FQSPI驱动初始化成功

Input:

- FQspiCtrl *pctrl, FQSPI驱动控制数据

- u8 command 写flash数据的指令，具体参见flash手册

- u32 chip_addr, 写数据的起始地址

- u8 *buf 写缓存, 存储要写入的数据

- size_t len, 要写入的buf长度

Return:

- FError, 错误码信息，FQSPI_SUCCESS 表示数据写入成功，其它返回值表示写入失败
