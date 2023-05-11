# FADC 驱动程序

## 1. 概述

ADC，Analog-to-Digital Converter的缩写，指模/数转换器或者模拟/数字转换器。是将连续变量的模拟信号转换为离散的数字信号的器件。真实世界的模拟信号，例如温度、压力、声音或者图像等，需要转换成更容易储存、处理和发射的数字形式。模/数转换器可以实现这个功能，典型的模拟数字转换器将模拟信号转换为表示一定比例电压值的数字信号。

## 2. 功能

adc控制器驱动提供了adc的控制访问方法，
- 初始化adc控制器，配置相关参数，如转换模式，通道使能等
- 读adc转换数据
- 转换完成与结果阈值的中断触发

驱动相关的源文件包括
```
.
├── fadc_g.c
├── fadc_hw.c
├── fadc_hw.h
├── fadc_intr.c
├── fadc_sinit.c
├── fadc.c
└── fadc.h
```

## 3. 配置方法

以下部分将指导您完成 fadc 驱动的软件配置:

- 初始化adc控制器
- 设置adc的中断处理函数
- 根据adc转换完成状态读取adc转换结果

## 4 应用示例

### [adc收发数据](../../../baremetal/example/peripheral/adc)

## 5. API参考

### 5.1. 用户数据结构

- fadc控制数据

```c
typedef struct
{
    FAdcConfig config;/* adc config */
    FAdcConvertConfig convert_config; /* adc convert config */
    FAdcThresholdConfig threshold_config; /* adc channel threshold config */
    u32 is_ready;/* adc init ready flag */
    u16 value[FADC_CHANNEL_NUM];  /* adc value */
    boolean convert_complete[FADC_CHANNEL_NUM]; /*!< Specifies whether the conversion is complete> */
    FAdcIntrEventHandler event_handler[FADC_INTR_EVENT_NUM];  /* event handler for interrupt */
    void *event_param[FADC_INTR_EVENT_NUM];   /* parameters of event handler */
  
}FAdcCtrl;
```

- fadc配置数据，FAdcConfig主要是adc控制器id、基地址和中断号，FAdcConvertConfig主要包括用户可配置的参数，包括转换间隔时间、转换模式、通道模式等，FAdcThresholdConfig主要包含具体通道的结果阈值

```c
typedef struct
{
    u32 instance_id;/* adc id */
    uintptr base_addr;/* adc control register base address*/
    u32 irq_num;/* adc interrupt number */
    u32 irq_prority;/* adc interrupt priority*/
    const char *instance_name;/* instance name */

} FAdcConfig; 

typedef struct
{
    u32 convert_interval; /* convert interval time */
    u32 clk_div; /* clock divider */
    FAdcConvertMode convert_mode;/*!<  convert mode */
    FAdcChannelMode channel_mode;/*!< channel mode */

} FAdcConvertConfig; 

typedef struct
{
    u16 high_threshold[FADC_CHANNEL_NUM]; /*!< Configures the ADC analog high threshold value.
                                           This parameter must be a 10-bit value. */
    u16 low_threshold[FADC_CHANNEL_NUM];  /*!< Configures the ADC analog low threshold value. 
                                            This parameter must be a 10-bit value. */
} FAdcThresholdConfig;
```

- fadc转换模式，单次转换和连续转换
```c
typedef enum
{
    FADC_CONTINUOUS_CONVERT = 0,/* continuous conversion*/
    FADC_SINGLE_CONVERT = 1,    /* single conversion*/
    
    FADC_CONVERT_MODE_NUM
    
} FAdcCovertMode;
```

- fadc通道模式，多通道顺序转换和固定通道转换
```c
typedef enum
{
    FADC_MULTI_CHANNEL = 0, /* multi channel conversion*/
    FADC_FIXED_CHANNEL = 1, /* fixed channel conversion*/
    
    FADC_CHANNEL_MODE_NUM
} FAdcChannelMode;
```

- fadc中断事件类型
```c
typedef enum
{
    FADC_INTR_EVENT_COVFIN = 0,  /**< Handler type for convert finish interrupt */
    FADC_INTR_EVENT_DLIMIT = 1,  /**< Handler type for low limit interrupt*/
    FADC_INTR_EVENT_ULIMIT = 2,  /**< Handler type for high limit interrupt*/
    FADC_INTR_EVENT_ERROR  = 3,  /**< Handler type for error interrupt*/

    FADC_INTR_EVENT_NUM
} FAdcIntrEventType;

```

### 5.2  错误码定义

- FADC_SUCCESS                执行成功 
- FADC_ERR_INVAL_PARM         参数无效
- FADC_ERR_NOT_READY          驱动未初始化
- FADC_ERR_TIMEOUT            超时
- FADC_ERR_CMD_FAILED         执行失败

### 5.3. 用户API接口

#### FAdcLookupConfig

- 获取fadc控制器默认配置

```c
const FAdcConfig *FAdcLookupConfig(u32 instance_id);
```

Note:

- 获取默认配置参数，包括基地址、中断号等

Input:

- {u32} instance_id，adc控制器id号

Return:

- {const FAdcConfig *} adc默认配置，返回NULL如果找不到默认配置

#### FAdcCfgInitialize

- 初始化fadc控制器, 使之可以使用

```c
FError FAdcCfgInitialize(FAdcCtrl *pctrl, const FAdcConfig *input_config_p);
```

Note:

- 输入配置通过FAdcLookupConfig获取，用户按照需要修改后传入此函数

Input:

- {FAdcCtrl} *pctrl，adc驱动控制数据
- {FAdcConfig} *input_config_p，adc用户输入配置

Return:

- {FError} 驱动初始化的错误码信息，FADC_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FAdcVariableConfig

- 设置adc可配置参数

```c
FError FAdcVariableConfig(FAdcCtrl *pctrl, u8 channel, FAdcConvertConfig *convert_config, 
                        FAdcThresholdConfig *threshold_config);
```

Note:

- 设置指定adc控制器的可配置参数，包括转换模式，通道阈值等

Input:

- {FAdcCtrl} *pctrl，adc驱动控制数据
- {u8} channel，adc通道号
- {FAdcConvertConfig} *convert_config，adc转换参数配置
- {FAdcThresholdConfig} *threshold_config，adc通道转换结果阈值配置

Return:

- {FError} 驱动初始化的错误码信息，FADC_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FAdcChannelThresholdSet

- 设置adc通道的转换结果阈值，使能该通道

```c
FError FAdcChannelThresholdSet(FAdcCtrl *pctrl, u8 channel, FAdcThresholdConfig *threshold_config);
```

Note:

- 设置指定adc控制器的指定通道的转换结果阈值，使能该通道

Input:

- {FAdcCtrl} *pctrl，adc驱动控制数据
- {u8} channel，adc通道号
- {FAdcThresholdConfig} *threshold_config，adc通道转换结果阈值配置

Return:

- {FError} 驱动初始化的错误码信息，FADC_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FAdcConvertStart

- 设置adc控制器转换开始

```c
FError FAdcConvertStart(FAdcCtrl *pctrl);
```

Note:

- 设置指定adc控制器转换开始

Input:

- {FAdcCtrl} *pctrl，adc驱动控制数据

Return:

- {FError} 驱动初始化的错误码信息，FADC_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FAdcInterruptEnable

- 使能adc通道的中断

```c
FError FAdcInterruptEnable(FAdcCtrl *pctrl, u8 channel, FAdcIntrEventType event_type);
```

Note:

- 使能指定adc控制器的指定通道的中断

Input:

- {FAdcCtrl} *pctrl，adc驱动控制数据
- {u8} channel，adc通道号
- {FAdcIntrEventType} event_type，中断事件类型

Return:

- {FError} 驱动初始化的错误码信息，FADC_SUCCESS 表示初始化成功，其它返回值表示初始化失败


#### FAdcReadConvertResult

- 读adc通道的转换结果

```c
FError FAdcReadConvertResult(FAdcCtrl *pctrl, u8 channel, u16 *val);
```

Note:

- 读指定adc控制器的指定通道的转换结果

Input:

- {FAdcCtrl} *pctrl，adc驱动控制数据
- {u8} channel，adc通道号
- {u16} *val，存储转换结果的指针

Return:

- {FError} 驱动初始化的错误码信息，FADC_SUCCESS 表示初始化成功，其它返回值表示初始化失败


#### FAdcRegisterInterruptHandler

- 注册adc中断事件函数

```c
void FAdcRegisterInterruptHandler(FAdcCtrl *instance_p, FAdcIntrEventType event_type, 
                                    FAdcIntrEventHandler handler, void *param);
```

Note:
- 无

Input:
- {FAdcCtrl} *instance_p，fadc驱动控制数据
- {FAdcIntrEventType} event_type，中断事件类型
- {FAdcIntrEventHandler} handler，中断事件回调函数
- {void} *param，回调函数参数

Return:
- 无

#### FAdcIntrHandler

- adc中断处理函数入口

```c
void FAdcIntrHandler(s32 vector, void *args);
```

Note:
- 根据中断类型，设置对应的回调函数和参数传入

Input:
- {s32} vector
- {void} *param, 输入参数，指向fadc驱动控制数据

Return:
- 无
