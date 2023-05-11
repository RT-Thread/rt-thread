# FCAN 驱动程序

## 1. 概述

CAN 是控制器局域网络(Controller Area Network)的缩写，由以研发和生产汽车电子产品著称的德国BOSCH公司开发，并最终成为国际标准(ISO 11898)，是国际上应用最广泛的现场总线之一。

## 2. 功能

CAN控制器驱动提供了CAN的控制访问方法，
- 初始化CAN控制器
- 以轮询方式发送/接收数据
- 发送/接收数据的中断触发

驱动相关的源文件包括，
```
.
├── fcan_g.c
├── fcan_hw.c
├── fcan_hw.h
├── fcan_intr.c
├── fcan_sinit.c
├── fcan.c
└── fcan.h
```

## 3. 配置方法

以下部分将指导您完成 fcan 驱动的软件配置:

- 初始化CAN控制器
- 设置CAN的中断处理函数，包括收发中断

## 4 应用示例

### [can收发数据](../../../baremetal/example/peripheral/can)

## 5. API参考

### 5.1. 用户数据结构

- fcan控制数据

```c
typedef struct
{
    FCanConfig config;
    u32 is_ready;  /* Device is initialized and ready */
    boolean use_canfd; /* if use canfd function */
    
    FCanIntrEventConfig intr_event[FCAN_INTR_EVENT_NUM];/* event handler and parameters for interrupt */
} FCanCtrl;
```

- fcan配置数据，FCanConfig主要是can控制器id、基地址和中断号，FCanIntrEventConfig主要包括中断处理函数

```c
typedef struct
{
    u32 instance_id;   /* Id of device */
    uintptr base_address; /* Can base Address */
    u32 irq_num;    /* interrupt number */
    u32 irq_prority;/* interrupt priority*/
}FCanConfig;
```

- fcan波特率配置
```c
typedef struct
{
    FCanSegmentType segment;
    boolean auto_calc; /* if auto calculate baudrate parameters */
    u32 baudrate;     /* baudrate */
    u32 sample_point; /* sample point */
    u32 prop_seg;     /* Propagation segment in TQs */
    u32 phase_seg1;   /* Phase buffer segment 1 in TQs */
    u32 phase_seg2;   /* Phase buffer segment 2 in TQs */
    u32 sjw;          /* Synchronisation jump width in TQs */
    u32 brp;          /* Baudrate prescaler */
}FCanBaudrateConfig;
```

- fcan报文
```c
typedef struct
{
    u32 canid;
    u8 candlc;
    u8 flags; /* additional flags for CAN FD */
    u8 data[FCAN_DATA_LENGTH] __attribute__((aligned(8)));
}FCanFrame;
```

- fcan中断事件类型
```c
typedef enum
{
    FCAN_INTR_EVENT_SEND = 0,    /* Handler type for frame sending interrupt */
    FCAN_INTR_EVENT_RECV = 1,    /* Handler type for frame reception interrupt */
    FCAN_INTR_EVENT_ERROR,       /* Handler type for error interrupt */
    FCAN_INTR_EVENT_NUM
} FCanIntrEventType;
```

### 5.2  错误码定义

- FCAN_SUCCESS      执行成功
- FCAN_NOT_READY    驱动未初始化
- FCAN_FAILURE      执行失败
- FCAN_INVAL_PARAM  参数无效

### 5.3. 用户API接口

#### FCanLookupConfig

- 获取Fata控制器默认配置

```c
const FCanConfig *FCanLookupConfig(u32 instance_id);
```

Note:

- 获取默认配置参数，包括基地址、中断号等

Input:

- {u32} instance_id，控制器id号

Return:

- {const FCanConfig *} fcan默认配置，返回NULL如果找不到默认配置

#### FCanCfgInitialize

- 初始化fcan控制器, 使之可以使用

```c
FError FCanCfgInitialize(FCanCtrl *instance_p, const FCanConfig *input_config_p);
```

Note:

- 输入配置通过FCanLookupConfig获取，用户按照需要修改后传入此函数

Input:

- {FCanCtrl} *instance_p fcan驱动控制数据
- {FCanConfig} *input_config_p fcan用户输入配置

Return:

- {FError} 驱动初始化的错误码信息，FCAN_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FCanSend

- 发送can数据

```c
FError FCanSend(FCanCtrl *instance_p, FCanFrame *frame_p);
```

Note:

- 指定can控制器发送can数据

Input:

- {FCanCtrl} *instance_p，fcan驱动控制数据
- {FCanFrame} *frame_p，can数据

Return:

- {FError} 驱动初始化的错误码信息，FCAN_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FCanRecv

- 接收can数据

```c
FError FCanRecv(FCanCtrl *instance_p, FCanFrame *frame_p);
```

Note:

- 指定can控制器接收can数据

Input:

- {FCanCtrl} *instance_p，fcan驱动控制数据
- {FCanFrame} *frame_p，can数据

Return:

- {FError} 驱动初始化的错误码信息，FCAN_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FCanRegisterInterruptHandler

- 注册can中断事件函数

```c
void FCanRegisterInterruptHandler(FCanCtrl *instance_p, FCanIntrEventConfig *intr_event_p);
```

Note:
- 无

Input:
- {FCanCtrl} *instance_p，fcan驱动控制数据
- {FCanIntrEventConfig} *intr_event_p，中断事件类型，回调函数，回调函数参数

Return:
- 无

#### FCanIntrHandler

- can中断处理函数入口

```c
void FCanIntrHandler(s32 vector, void *args);
```

Note:
- 根据中断类型，设置对应的回调函数和参数传入

Input:
- {s32} vector
- {void} *param, 输入参数，指向fcan驱动控制数据

Return:
- 无

#### FCanIdMaskFilterSet

- can id过滤设置

```c
FError FCanIdMaskFilterSet(FCanCtrl *instance_p, FCanIdMaskConfig *id_mask_p);
```

Note:
- 设置可接收帧id值和掩码

Input:
- {FCanCtrl} *instance_p, fcan驱动控制数据
- {FCanIdMaskConfig} *id_mask_p, 过滤寄存器序号，可接收帧id，可接收帧id掩码

Return:
- {FError} 驱动初始化的错误码信息，FCAN_SUCCESS 表示初始化成功，其它返回值表示初始化失败