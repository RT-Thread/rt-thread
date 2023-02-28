# FGPIO 驱动程序

## 1. 概述

- GPIO(General-purpose input/output)，即通用型输入输出，其引脚可以供使用者通过程序控制其输入、输出，常用于产生时钟，作为片选信号和模拟低速通信协议等场景

- FT2000/4和D2000提供两个 GPIO 模块，每个 GPIO 模块有 16 位接口，每8位一组，分别是A组和B组，GPIO可以控制外部IO的输入输出方向，作为输出时，内部寄存器的数据输出到片外，作为输入时，片外的数据被锁存在内部寄存器

- FGPIO 驱动支持配置 GPIO 引脚的输入输出方向，输出高低电平，或者获取输入电平，配置引脚的中断触发模式，配置引脚的中断响应回调函数等

- FGPIO_VERSION_1 对应 FT2000/4和D2000 的 GPIO，FGPIO_VERSION_2 对应 E2000的 GPIO，具体差异请参考软件编程手册

## 2. 功能

- FGPIO 驱动程序主要完成GPIO相关的功能配置，包括

- 1. GPIO 控制器初始化
- 2. GPIO 引脚输入输出方向设置
- 3. GPIO 引脚输出和输入
- 4. GPIO 引脚中断使能和屏蔽
- 5. GPIO 引脚中断类型设置
- 6. GPIO 引脚中断回调函数注册

- 驱动相关的源文件如下，
- drivers/pin/fgpio
```
.
├── Kconfig
├── fgpio.c
├── fgpio.h
├── fgpio_g.c
├── fgpio_hw.h
├── fgpio_selftest.c
├── fgpio_intr.c
└── fgpio_sinit.c
```

## 3. 配置方法

- FGPIO 驱动支持 FT2000/4, D2000和E2000，在 D2000 和 E2000 上完成测试

- 参考以下步骤完成 FGPIO 硬件配置，
- 1. 获取FT2000/4, D2000或E2000的软件编程手册，参考引脚复用表，设置引脚复用为 GPIO
- 2. 初始化 GPIO 控制器实例
- 3. 设置 GPIO 引脚的输入，输出方向
- 4. 获取 GPIO 引脚上的输入，或者设置 GPIO 引脚的输出电平
- 5. 设置 GPIO 引脚的中断屏蔽位和中断触发类型，注册引脚的中断回调函数

## 4 应用示例

- 设置 GPIO 引脚的输出电平，获取引脚的输入电平，通过外部输入触发 GPIO 中断

### [fgpio_irq](../../../baremetal/example/peripheral/pin/fgpio_irq)

- 通过 GPIO 产生占空比和频率可配的 PWM 波形

### [fgpio_soft_pwm](../../../baremetal/example/peripheral/pin/fgpio_soft_pwm)

## 5. API参考

### 5.1. 用户数据结构

#### FGpioConfig

```c
typedef struct
{
    u32 instance_id; /* GPIO实例ID */
    uintptr base_addr; /* GPIO控制器基地址 */
#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
    u32 irq_num; /* GPIO控制器中断号 */
#elif defined(FGPIO_VERSION_2) /* E2000 GPIO 0 ~ 5 */
    u32 irq_num[FGPIO_PIN_NUM]; /* GPIO各引脚的中断号 */
#endif
    u32 irq_priority; /* 中断优先级 */
} FGpioConfig; /* GPIO控制器配置 */
```

#### FGpioPin

```c
typedef struct _FGpioPin
{
    FGpioPinId index; /* 索引 */
    u32 is_ready;
    FGpio *instance;
    FGpioInterruptCallback irq_cb; /* 中断回调函数, Port-A有效 */
    void *irq_cb_params; /* 中断回调函数的入参, Port-A有效 */
    boolean irq_one_time; /* Port-A有效, TRUE: 进入中断后关闭该引脚的中断，用于电平敏感中断，防止一直进入中断 */
} FGpioPin; /* GPIO引脚实例 */
```

#### FGpio

```c
typedef struct _FGpio
{
    FGpioConfig config;
    u32 is_ready;
    FGpioPin *pins[FGPIO_PORT_NUM][FGPIO_PIN_NUM];
} FGpio; /* GPIO控制器实例 */
```
### 5.2  错误码定义

- [0x0] FGPIO_SUCCESS : success

- [0x1050000] FGPIO_ERR_INVALID_PARA : invalid input parameters

- [0x1050001] FGPIO_ERR_INVALID_STATE : invalid state


### 5.3 用户API接口

#### FGpioLookupConfig

```c
const FGpioConfig *FGpioLookupConfig(u32 instance_id);
```

Note:

- 获取GPIO控制器的默认配置

Input:

-  {u32} instance_id, GPIO控制器实例号

Return:

- {const FGpioConfig *} GPIO控制器的默认配置

#### FGpioCfgInitialize

```c
FError FGpioCfgInitialize(FGpio *const instance, const FGpioConfig *const config);
```

Note:

- 初始化GPIO控制器实例

Input:

- {FGpio} *instance, GPIO控制器实例
- {FGpioConfig} *config, GPIO控制器配置

Return:

- {FError} FGPIO_SUCCESS 表示初始化成功

#### FGpioDeInitialize

```c
void FGpioDeInitialize(FGpio *const instance);
```

Note:

- 去初始化GPIO控制器实例

Input:

- {FGpio} *instance, GPIO控制器实例

Return:

- 无

#### FGpioPinInitialize

```c
FError FGpioPinInitialize(FGpio *const instance, FGpioPin *const pin,
                          const FGpioPinId pin_id);
```

Note:

- 初始化GPIO引脚实例

Input:

- {FGpio} *instance, GPIO控制器实例
- {FGpioPin} *pin_instance, GPIO引脚实例
- {FGpioPinId} index, GPIO引脚索引

Return:

- {FError} FGPIO_SUCCESS 表示初始化成功

#### FGpioPinDeInitialize

```c
void FGpioPinDeInitialize(FGpioPin *const pin);
```

Note:

- 去初始化GPIO引脚实例

Input:

- {FGpioPin} *pin_instance, GPIO引脚实例

Return:

- {FError} FGPIO_SUCCESS 表示初始化成功

#### FGpioGetPinIrqSourceType

```c
FGpioIrqSourceType FGpioGetPinIrqSourceType(FGpioPin *const pin);
```

Note:

- 获取引脚中断的上报方式

Input:

- {FGpioPin} *pin_instance, GPIO引脚实例

Return:

- {FGpioIrqSourceType} 引脚中断的上报方式

#### FGpioSetDirection

```c
void FGpioSetDirection(FGpioPin *const pin, FGpioDirection dir);
```

Note:

- 设置GPIO引脚的输入输出方向
- 初始化 GPIO 实例后使用此函数

Input:

- @param {FGpioPin} *instance, GPIO控制器实例
- @param {FGpioDirection} dir, 待设置的GPIO的方向

Return:

- 无

#### FGpioGetDirection

```c
FGpioDirection FGpioGetDirection(FGpioPin *const pin);
```

Note:

- 获取GPIO引脚的输入输出方向
- 初始化 GPIO 实例后使用此函数

Input:

- {FGpioPin} *pin, GPIO引脚实例

Return:

- {FGpioDirection} GPIO引脚方向

#### FGpioSetOutputValue

```c
FError FGpioSetOutputValue(FGpioPin *const pin, const FGpioPinVal output);
```

Note:

- 设置GPIO引脚的输出值
- 初始化 GPIO 实例后使用此函数，先设置 GPIO 引脚为输出后调用此函数

Input:

- {FGpioPin} *pin, GPIO引脚实例
- {FGpioPinVal} output, GPIO引脚的输出值

Return:

- {FError} FGPIO_SUCCESS 表示设置成功

#### FGpioGetInputValue

- 获取GPIO引脚的输入值

```c
FGpioPinVal FGpioGetInputValue(FGpioPin *const pin);
```

Note:

- 初始化 GPIO 实例后使用此函数，先设置 GPIO 引脚为输入后调用此函数

Input:

- {FGpioPin} *instance, GPIO引脚实例
- {FGpioPinVal} output, GPIO引脚的输出值

Return:

- {FGpioPinVal} 获取的输入值，高电平/低电平

#### FGpioGetInterruptMask

- 获取GPIO A组引脚的中断屏蔽位 

```c
void FGpioGetInterruptMask(FGpio *const instance, u32 *mask, u32 *enabled)
```

Note:

- 获取的是A组所有Pin的中断屏蔽位和中断使能位

Input:

- {FGpio} *instance, GPIO控制器实例
- {u32} *mask, 返回的GPIO A组引脚中断屏蔽位
- {u32} *enabled, 返回的GPIO A组中断使能位

Return:

- 无
#### FGpioSetInterruptMask

- 设置GPIO A组引脚的中断屏蔽位

```c
void FGpioSetInterruptMask(FGpioPin *const pin, boolean enable);
```

Note:

- index对应的引脚必须为A组引脚，B组引脚不支持中断

Input:

- {FGpioPin} *pin, GPIO引脚实例
- {boolean} enable, TRUE表示使能GPIO引脚中断，FALSE表示去使能GPIO引脚中断

Return:

- 无
#### FGpioGetInterruptType

- 获取GPIO A组引脚的中断类型和中断极性

```c
void FGpioGetInterruptType(FGpio *const instance, u32 *levels, u32 *polarity)
```

Note:

- 获取的是A组所有Pin的电平和极性

Input:

- {FGpio} *instance, GPIO控制器实例
- {u32} *levels, GPIO A组引脚中断电平类型
- {u32} *polarity, GPIO A组引脚中断极性类型

Return:

- 无

#### FGpioSetInterruptType

- 设置GPIO引脚的中断类型

```c
void FGpioSetInterruptType(FGpioPin *const pin, const FGpioIrqType type)
```

Note:

- index对应的引脚必须为A组引脚，B组引脚不支持中断

Input:

- {FGpioPin} *pin, GPIO引脚实例
- {FGpioIrqType} type, GPIO引脚中断触发类型

Return:

- 无

#### FGpioInterruptHandler

- GPIO中断处理函数

```c
void FGpioInterruptHandler(s32 vector, void *param)
```

Note:

- 需要用户将此函数注册到Interrtup上，使能GPIO中断才能生效

Input:

- {s32} vector, 中断输入参数1
- {void} *param, 中断输入参数2

Return:

- 无


#### FGpioPinInterruptHandler

- GPIO中断处理函数

```c
void FGpioPinInterruptHandler(s32 vector, void *param)
```

Note:

- 需要用户将此函数注册Gic上，才能生效

Input:

- {s32} vector, 中断输入参数1
- {void} *param, 中断输入参数2

Return:

- 无

#### FGpioRegisterInterruptCB

- 注册GPIO引脚中断回调函数

```c
void FGpioRegisterInterruptCB(FGpioPin *const pin, FGpioInterruptCallback cb, void *cb_param, boolean irq_one_time)
```

Note:

- 注册的回调函数在`FGpioInterruptHandler`中被调用

Input:

- {FGpioPin} pin, GPIO引脚实例
- {FGpioInterruptCallback} cb, GPIO引脚中断回调函数
- {void} *cb_param, GPIO引脚中断回调函数输入参数
- {boolean} irq_one_time, TRUE表示引脚中断触发一次后自动关闭中断，用于电平敏感中断

Return:

- 无
