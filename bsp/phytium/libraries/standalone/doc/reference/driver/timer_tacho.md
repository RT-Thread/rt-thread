# TIMER_TACHO 驱动程序

## 1. 概述


- TIMER_TACHO包含了2种功能，定时器和输入捕获。其中定时计数作为通用定时器供软件使用，输入捕获功能主要用来测试输入方波的高电平持续时间，该方波是由风扇设备设备发出，通过PAD直接连接到控制器模块输入端。
- 对于定时功能，有若干可配置参数，例如产生中断次数，是否对当前计数值进行清空，是否使能计数器，计数器位宽选择（32/64），或者是restart/free模式，以及当进行了初值配置是否需要强制更新，以及可以通过配置寄存器对控制器模块进行复位操作。
- 对于输入捕获，控制器模块设置了上下阈值，也就是当捕获到的高电平时间低于或者高于阈值都会发出中断（此时分别对应风扇不同的故障）。同时对输入信号进行消抖处理，也可以对消抖级数进行配置。
- 本驱动程序提供了E2000(D、Q、S)平台的定时器和输入捕获功能
- E2000（D、Q、S）上包含了38个定时器控制器，（D、Q）上包含了4个tacho输入捕获接口，（S）上包含了16个输入捕获接口

## 2. 功能

- 驱动相关的源文件如下:
- drivers/timer/ftimer_tacho

```
.
├── ftacho.c --> 转速计功能实现
├── ftimer_tacho_g.c --> 相关配置和全局变量
├── ftimer_tacho_hw.h --> 寄存器操作
├── ftimer_tacho_intr.c --> 中断相关处理
├── ftimer_tacho.h --> 用户接口
└── ftimer.c --> 定时器功能实现
```

## 3. 配置方法

以下部分将指导您完成ftimer_tacho驱动的软件配置:

- 初始化timer_tacho控制器，使用timer功能还是tacho功能
- 分别配置两个功能的参数，配置使用timer功能的id，定时时间，计数方式等；配置使用tacho功能的id，阈值，输入消抖级数等。
- 注册中断处理函数，使能中断

## 4. 应用示例

### [timer定时器](../../../baremetal/example/peripheral/timer/timer_tacho/README.md)

#### timer
- FTimerFunctionInit     获取cmd传递进来的最基本参数
- FTimerCfgInit          对传递的参数以及默认参数进行配置，并启动中断
- FTimerStartTest       定时器开始工作，如果是单次计时，则可以传递新的参数并计时，循环模式则仅仅进行启动
- 在中断中进行回调

#### tacho
- FTachoFunctionInit    获取cmd传递进来的参数，使用计时器的id以及工作模式
- FTachoCfgInit         配置工作参数
- TachoEnableIntr       启用事件中断
- FTimerStart           tacho开始工作
- FTachoGetRPM          可以获取RPM参数了

#### timer与tacho的切换
- 注意需要对定时器控制器进行disable，可以调用各自的F****DeInit函数，也可以FTimerSwithMode进行操作

## 5. API参考

### 5.1 用户数据结构

- ftimer_tacho控制数据

```c
typedef struct
{
    FTimerTachoConfig     config;   /* Current active configs */
    boolean               isready;  /* Device is initialized and ready */
    FTimerEventHandler    evt_handlers[FMAX_TIMER_TACHO_EVENT];/* event handler for interrupt */
}FTimerTachoCtrl;
```

- ftimer_tacho配置数据

```c
typedef struct 
{
    u32     id;        /* id of timer tacho */
    char    name[12];  /* instance name */
    u32     irq_priority; /* intr priority */
    u32     work_mode;  /* timer/tacho/capture mode */
    /* for timer function */
    u32     timer_mode; /* free-run/restart */
    u32     timer_bits; /* 32/64 bits */
    u32     cmp_type; /* once/cycle cmp */
    boolean clear_cnt;  /* clear timer counts */
    boolean force_load; /* start count from start val */
    /* for tacho function */
    u32     edge_mode; /* rising/falling/double */
    u32     jitter_level; /* jitter level */
    u32     plus_num;  /* plus_num of period to calculate rpm */
    u32     captue_cnt; /* in capture mode, when cnt reach this val, intr asserted */
}FTimerTachoConfig;
```

- ftimer_tacho工作模式
```c
typedef enum
{
    /*TimerTacho mode */
    FTIMER_WORK_MODE_TIMER = 0,
    FTIMER_WORK_MODE_TACHO,
    FTIMER_WORK_MODE_CAPTURE
}FTimerTachoModeType;
```

- timer计数模式
```c
typedef enum
{
    /*Timer count mode*/
    FTIMER_FREE_RUN = 0,
    FTIMER_RESTART
}FTimerCntModeType;
```

- ftimer_tacho中断事件类型
```c
typedef enum
{
    FTACHO_EVENT_OVER = 0,      /*tacho超速事件*/
    FTACHO_EVENT_UNDER,         /*tacho低速事件*/
    FTIMER_EVENT_ROLL_OVER,     /*计数器翻转事件*/
    FTIMER_EVENT_ONCE_CMP,      /*单次定时输出事件*/
    FTIMER_EVENT_CYC_CMP,       /*重复定时输出事件*/
    FTACHO_EVENT_CAPTURE,       /*tacho输入捕获事件*/
    
    FMAX_TIMER_TACHO_EVENT
}FTimerTachoEventType;
```

- tacho输入模式选择
```c
typedef enum
{
    FTACHO_FALLING_EDGE = 0,
    FTACHO_RISING_EDGE,
    FTACHO_DOUBLE_EDGE
}FTachoEdgeType;
```

- tacho消抖级数选择
```c
typedef enum
{
    FTACHO_JITTER_LEVEL0 = 0,
    FTACHO_JITTER_LEVEL1,
    FTACHO_JITTER_LEVEL2,
    FTACHO_JITTER_LEVEL3,
}FTachoJitterLevelType;
```

### 5.2 错误码定义

- FTIMER_TACHO_ERR_IS_READ                已经初始化 
- FTIMER_TACHO_ERR_NOT_READY              未初始化
- FTIMER_TACHO_ERR_INVAL_PARM             参数错误
- FTIMER_TACHO_ERR_INIT_FAILED            初始化错误
- FTIMER_TACHO_ERR_ABORT                  运行中止
- FTIMER_TACHO_ERR_FAILED                 运行错误
- FTIMER_TACHO_ERR_NOT_SUPPORT            不支持此配置

### 5.3 用户API接口

#### Time & Tacho API 

##### FTimerSoftwareReset

- 将控制器复位

```c
FError FTimerSoftwareReset(FTimerTachoCtrl *instance_p);
```

Note:

- 复位控制器

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据

Return:

- {FError} 驱动的错误码信息

##### FTimerSetInterruptMask

- 设置中断

```c
void FTimerSetInterruptMask(FTimerTachoCtrl *instance_p,
                           FTimerTachoEventType intrType,
                           boolean enable);
```

Note:

- 设置中断,根据不同的intrType，将对于的中断mask置位

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据
- {FTimerTachoEventType} intrType，timer_tacho中断类型
- {boolean} enable，开启还是关闭中断

Return:

- void 无

##### FTimerStart

- 启动timer_tacho

```c
FError FTimerStart(FTimerTachoCtrl *instance_p);
```

Note:

- 启动已经初始化完成的timer_tacho外设,根据不同的功能，开启使能位

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据

Return:

- {FError} 驱动的错误码信息

##### FTimerStop

- 停止timer外设

```c
FError FTimerStop(FTimerTachoCtrl *instance_p);
```

Note:

- 停止timer外设，根据不同的功能，关闭使能位，计数值停止并冻结

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据

Return:

- {FError} 驱动的错误码信息

##### FTimerSwithMode

- timer 与 tacho-capture两种模式的切换

```c
FError FTimerSwithMode(FTimerTachoCtrl *instance_p, FTimerTachoConfig *new_config_p);
```

Note:

- 用于timer 与 tacho-capture两种模式的切换，切换需要失能和清除计数器

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据
- {FTimerTachoConfig} *new_config_p，timer_tacho配置数据

Return:

- {FError} 驱动的错误码信息

##### FTimerRegisterEvtCallback

- 注册中断事件处理回调函数

```c
void FTimerRegisterEvtCallback(FTimerTachoCtrl *instance_p, 
                              FTimerTachoEventType evt, 
                              FTimerEventHandler callback);
```

Note:

- 注册中断事件处理回调函数，根据不同的中断事件类型，当发生中断后，会跳转到注册的函数中

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据
- {FTimerTachoEventType} evt，中断事件类型
- {FTimerEventHandler} callback，用户自己定义的中断回调函数

Return:

- void 无

##### FTimeSettingDump

- 打印寄存器信息

```c
FError FTimeSettingDump(const FTimerTachoCtrl *instance_p);
```

Note:

- 打印已经初始化成功的timer_tacho控制器寄存器信息

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据

Return:

- {FError} 驱动的错误码信息

##### FTimerTachoIntrHandler

- TimerTacho中断处理函数

```c
void FTimerTachoIntrHandler(s32 vector, void *param);
```

Note:

- TimerTacho中断处理函数，如果注册回调函数，则跳转到回调函数

Input:

- {s32} vector，中断向量号
- {void} *param, 中断输入参数, 指向FTimerTachoCtrl的驱动控制实例

Return:

- void 无

##### FTimerTachoSetIntr

- 根据工作模式和状态设置相应的中断

```c
void FTimerTachoSetIntr(FTimerTachoCtrl *instance_p);
```

Note:

- 根据工作模式和状态设置相应的中断，此函数根据设置的模式自动配置中断，特殊需求可更改

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据

Return:

- void 无

##### FTimerInit

- TimerTacho驱动实例的初始化

```c
FError FTimerInit(FTimerTachoCtrl *instance_p, const FTimerTachoConfig *config_p);
```

Note:

- 完成TimerTacho驱动实例的初始化，使之在就绪状态，配合FTimerStart使用

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据
- {FTimerTachoConfig} *config_p，timer_tacho配置数据

Return:

- {FError} 驱动的错误码信息

##### FTimerDeInit

- Timer驱动实例去使能，清零实例数据

```c
void FTimerDeInit(FTimerTachoCtrl *instance_p);
```

Note:

- 对已经完成初始化的实例，进行Timer驱动实例去使能，清零实例数据

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据

Return:

- void 无

##### FTachoInit

- 完成Tacho驱动实例的初始化

```c
FError FTachoInit(FTimerTachoCtrl *instance_p, const FTimerTachoConfig *config_p);
```

Note:

- 完成Tacho驱动实例的初始化，使之在就绪状态

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据

Return:

- void 无

##### FTachoGetFanRPM

- 获取风扇的转速值

```c
FError FTachoGetFanRPM(FTimerTachoCtrl *instance_p,u32 *rpm);
```

Note:

- 根据预设采样周期的值，来获取风扇的转速值

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据
- {u32} *rpm，传入保存转数数据的指针

Return:

- {FError} 驱动的错误码信息

##### FTachoDeInit

- Tacho驱动实例去使能，清零实例数据

```c
void FTachoDeInit(FTimerTachoCtrl *instance_p);
```

Note:

- 完成Tacho驱动实例去使能，清零实例数据

Input:

- {FTimerTachoCtrl} *instance_p，timer_tacho驱动控制数据

Return:

- void 无
