# FIOPAD 驱动程序

## 1. 概述
IOPad，是输入/输出（Input/Output）引脚。嵌入式系统通常由处理器、内存、外设和输入/输出接口组成。输入/输出引脚是用于连接外部设备和嵌入式系统的接口。它们用于数据和控制信号的输入和输出，可以连接各种传感器、执行器、存储设备等外围设备。IOPad通常由特定的计算机芯片或微控制器提供，并通过编程方式进行配置和控制

## 2. 功能

iopad控制器驱动提供了iopad的控制访问方法，
- 初始化iopad控制器
- 配置引脚复用，引脚输入输出延迟等

驱动相关的源文件包括
```
.
├── fiopad_g.c
├── fiopad_hw.c
├── fiopad_hw.h
├── fiopad_intr.c
├── fiopad_sinit.c
├── fiopad.c
└── fiopad.h
```

## 3. 配置方法

以下部分将指导您完成 fiopad 驱动的软件配置:

- 初始化iopad控制器
- 设置引脚功能复用，设置引脚延时

## 4 应用示例


## 5. API参考

### 5.1. 用户数据结构

- fiopad控制数据

```c
typedef struct
{
    FIOPadConfig config;/* iopad config */
    u32 is_ready;/* iopad init ready flag */
    
} FIOPadCtrl; 
```

- fiopad配置数据，FIOPadConfig主要是iopad控制器id、基地址，FIOPadMulConfig主要包括用户可配置的复用参数，包括复用功能，上下拉，驱动能力等，FIOPadDelayConfig主要用户可配置的延时参数，输入输出方向，粗调延时，精调延时等

```c
typedef struct
{
    u32 instance_id; /* Device instance id */
    uintptr base_address; /* iopad control register base address */

} FIOPadConfig;
```

- fiopad复用功能，E2000最多支持8种功能
```c
typedef enum
{
    FIOPAD_FUNC0 = 0b000,
    FIOPAD_FUNC1,
    FIOPAD_FUNC2,
    FIOPAD_FUNC3 = 0b011,
    FIOPAD_FUNC4,
    FIOPAD_FUNC5,
    FIOPAD_FUNC6,
    FIOPAD_FUNC7 = 0b111,

    FIOPAD_NUM_OF_FUNC
} FIOPadFunc; /* Pin multiplexing function configuration, func0 is the default function */
```

- fiopad驱动能力
```c
typedef enum
{
    FIOPAD_DRV0 = 0b0000,
    FIOPAD_DRV1,
    FIOPAD_DRV2,
    FIOPAD_DRV3,
    FIOPAD_DRV4,
    FIOPAD_DRV5,
    FIOPAD_DRV6,
    FIOPAD_DRV7,
    FIOPAD_DRV8,
    FIOPAD_DRV9,
    FIOPAD_DRV10,
    FIOPAD_DRV11,
    FIOPAD_DRV12,
    FIOPAD_DRV13,
    FIOPAD_DRV14,
    FIOPAD_DRV15 = 0b1111,

    FIOPAD_NUM_OF_DRIVE
} FIOPadDrive; /* Pin drive capability configuration ，divided into 16 levels*/
```

- fiopad上下拉配置
```c
typedef enum
{
    FIOPAD_PULL_NONE = 0b00,
    FIOPAD_PULL_DOWN = 0b01,
    FIOPAD_PULL_UP = 0b10,

    FIOPAD_NUM_OF_PULL
} FIOPadPull; /* Pin up pull-down configuration */

```

- fiopad延迟输入输出方向配置
```c
typedef enum
{
    FIOPAD_OUTPUT_DELAY = 0, /* Delay setting direction to output */
    FIOPAD_INPUT_DELAY, /* Delay setting direction to input */

    FIOPAD_NUM_OF_DELAY_DIR
} FIOPadDelayDir; /* Pin delay configuration direction */

```

- fiopad粗调，精调类型配置
```c
typedef enum
{
    FIOPAD_DELAY_COARSE_TUNING = 0, /*delay coarse tuning */
    FIOPAD_DELAY_FINE_TUNING, /*delay fine tuning */

    FIOPAD_NUM_OF_DELAY_TYPE
} FIOPadDelayType; /* Pin delay configuration type */

```

- fiopad粗调，精调类型配置，粗调每级延时均值约360ps，精调每级延时均值约100ps
```c
typedef enum
{
    FIOPAD_DELAY_NONE = 0,
    FIOPAD_DELAY_1,
    FIOPAD_DELAY_2,
    FIOPAD_DELAY_3,
    FIOPAD_DELAY_4,
    FIOPAD_DELAY_5,
    FIOPAD_DELAY_6,
    FIOPAD_DELAY_7,

    FIOPAD_NUM_OF_DELAY
} FIOPadDelay;/* Pin delay level configuration */

```

### 5.2  错误码定义
- FIOPAD_SUCCESS      执行成功
- FIOPAD_INVAL_PARAM  参数无效
- FIOPAD_NOT_READY    驱动未初始化
- FIOPAD_NOT_SUPPORT  驱动不支持

### 5.3. 用户API接口

#### FIOPadLookupConfig

- 获取fiopad控制器默认配置

```c
const FIOPadConfig *FIOPadLookupConfig(u32 instance_id);
```

Note:

- 获取默认配置参数，包括基地址等

Input:

- {u32} instance_id，iopad控制器id号

Return:

- {const FIOPadConfig *} iopad默认配置，返回NULL如果找不到默认配置

#### FIOPadCfgInitialize

- 初始化fiopad控制器, 使之可以使用

```c
FError FIOPadCfgInitialize(FIOPadCtrl *instance_p, const FIOPadConfig *input_config_p);
```

Note:

- 输入配置通过FIOPadLookupConfig获取，用户按照需要修改后传入此函数

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {FIOPadConfig} *input_config_p，iopad用户输入配置

Return:

- {FError} 驱动初始化的错误码信息，FIOPAD_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FIOPadGetFunc

- 获取iopad pin当前复用功能

```c
FIOPadFunc FIOPadGetFunc(FIOPadCtrl *instance_p, const u32 pin_reg_off);
```

Note:

- 获取iopad pin当前复用功能

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {u32} pin_reg_off，对应pin地址偏移量

Return:

- {FIOPadFunc} iopad pin当前复用功能

#### FIOPadSetFunc

- 设置iopad pin复用功能

```c
FError FIOPadSetFunc(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadFunc func);
```

Note:

- 设置iopad pin复用功能

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {u32} pin_reg_off，对应pin地址偏移量
- {FIOPadFunc} func, 具体复用功能

Return:

- {FError} 驱动初始化的错误码信息，FIOPAD_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FIOPadGetPull

- 获取iopad pin当前上下拉配置

```c
FIOPadPull FIOPadGetPull(FIOPadCtrl *instance_p, const u32 pin_reg_off);
```

Note:

- 获取iopad pin当前上下拉配置

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {u32} pin_reg_off，对应pin地址偏移量

Return:

- {FIOPadFunc} iopad pin当前上下拉配置

#### FIOPadSetPull

- 设置iopad pin上下拉

```c
FError FIOPadSetPull(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadPull pull);
```

Note:

- 设置iopad pin上下拉

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {u32} pin_reg_off，对应pin地址偏移量
- {FIOPadPull} pull, 具体上下拉配置

Return:

- {FError} 驱动初始化的错误码信息，FIOPAD_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FIOPadGetDriver

- 获取iopad pin当前驱动能力

```c
FIOPadDrive FIOPadGetDriver(FIOPadCtrl *instance_p, const u32 pin_reg_off);
```

Note:

- 获取iopad pin当前驱动能力

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {u32} pin_reg_off，对应pin地址偏移量

Return:

- {FIOPadDrive} iopad pin当前驱动能力

#### FIOPadSetDriver

- 设置iopad pin驱动能力

```c
FError FIOPadSetDriver(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDrive drive);
```

Note:

- 设置iopad pin驱动能力

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {u32} pin_reg_off，对应pin地址偏移量
- {FIOPadDrive} Driver, 具体驱动能力参数

Return:

- {FError} 驱动初始化的错误码信息，FIOPAD_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FIOPadSetConfig

- 设置iopad pin复用功能，上下拉配置，驱动能力

```c
FError FIOPadSetConfig(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadFunc func, FIOPadPull pull, FIOPadDrive drive);
```

Note:

- 设置iopad pin复用功能，上下拉配置，驱动能力，此接口一次性设置三种配置

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {u32} pin_reg_off，对应pin地址偏移量
- {FIOPadFunc} func, 具体复用功能
- {FIOPadPull} pull, 具体上下拉配置
- {FIOPadDrive} Driver, 具体驱动能力参数

Return:

- {FError} 驱动初始化的错误码信息，FIOPAD_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FIOPadGetConfig

- 获取iopad pin复用功能，上下拉配置，驱动能力

```c
FError FIOPadGetConfig(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadFunc *func, FIOPadPull *pull, FIOPadDrive *drive)
```

Note:

- 胡去哦去iopad pin复用功能，上下拉配置，驱动能力，此接口一次性获取三种配置

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {u32} pin_reg_off，对应pin地址偏移量
- {FIOPadFunc} *func, 具体复用功能
- {FIOPadPull} *pull, 具体上下拉配置
- {FIOPadDrive} *Driver, 具体驱动能力参数

Return:

- {FError} 驱动初始化的错误码信息，FIOPAD_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FIOPadGetDelay

- 获取iopad pin当前延迟相关配置

```c
FIOPadDelay FIOPadGetDelay(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDelayDir dir, FIOPadDelayType type);
```

Note:

- 获取iopad pin当前延迟相关配置

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {u32} pin_reg_off，对应pin地址偏移量
- {FIOPadDelayDir} dir，延迟配置方向
- {FIOPadDelayType} type，延迟配置类型

Return:

- {FIOPadDelay} iopad pin在具体方向和类型下延迟的具体挡位

#### FIOPadSetDelay

- 设置iopad pin延迟挡位

```c
FError FIOPadSetDelay(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDelayDir dir, FIOPadDelayType type, FIOPadDelay delay);
```

Note:

- 设置iopad pin延迟在具体方向和类型下的挡位

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {u32} pin_reg_off，对应pin地址偏移量
- {FIOPadDelayDir} dir，延迟配置方向
- {FIOPadDelayType} type，延迟配置类型
- {FIOPadDelay} delay，要设置的延迟具体值

Return:

- {FError} 驱动初始化的错误码信息，FIOPAD_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FIOPadSetDelayEn

- 设置iopad pin延迟使能

```c
FError FIOPadSetDelayEn(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDelayDir dir, boolean enable);
```

Note:

- 设置iopad pin在具体方向和类型下的延迟使能

Input:

- {FIOPadCtrl} *instance_p，iopad驱动控制数据
- {u32} pin_reg_off，对应pin地址偏移量
- {FIOPadDelayDir} dir，延迟配置方向
- {FIOPadDelayType} type，延迟配置类型
- {boolean}enable，ture 使能;false 去使能

Return:

- {FError} 驱动初始化的错误码信息，FIOPAD_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FIOPadDeInitialize

```c
FError FIOPadDeInitialize(FIOPadCtrl *instance_p)
```

Note:

- 去初始化FIOPAD控制器实例

Input:

- {FIOPadCtrl}instance_p, FIOPAD控制器实例

Return:

- {FError} 驱动初始化的错误码信息，FIOPAD_SUCCESS 表示初始化成功，其它返回值表示初始化失败