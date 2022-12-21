# WDT 驱动程序

## 1. 概述

- WDT(watchdog timer)看门狗定时器是一种监控系统运行状况的手段，软件需在运行过程中定时向看门狗发送喂狗信号。

- 若看门狗定时器在一段时间内没有收到来自软件的喂狗信号，则认为系统故障，会强制系统复位。

- WDT 驱动支持的平台包括 FT2000/4、D2000、E2000。

## 2. 功能

WDT 驱动程序主要完成WDT模块的初始化、超时时间设置和超时中断函数，该驱动程序具备以下功能：

- 模块初始化
- 超时时间设置
- 超时中断函数设置

相关源文件为：
```
fwdt
    ├── fwdt.c
    ├── fwdt.h
    ├── fwdt_g.c
    ├── fwdt_hw.c
    ├── fwdt_hw.h
    ├── fwdt_intr.c
    └── fwdt_sinit.c
```

## 3. 配置方法

以下部分将指导您完成 WDT 驱动的软件配置:

- 配置驱动程序，新建应用工程，使能WDT驱动模块
- 设置配置参数
- 设置超时时间
- 设置超时中断函数喂狗

## 4. 应用示例


### [wdt_test](../../../baremetal/example/peripheral/timer/wdt_test/README.md)


## 5. API参考


### 5.1. 用户数据结构

- drivers/wdt/fwdt/fwdt.h

- wdt实例配置

```c
typedef struct
{
    u32 instance_id;/* wdt id */
    uintptr refresh_base_addr;/* wdt refresh base addr */
    uintptr control_base_addr;/* wdt control base addr */
    u32 irq_num;    /* wdt ir num */
    u32 irq_prority;/* wdt irq priority */
    const char *instance_name;/* instance name */
}FWdtConfig;/* wdt config */
```

### 5.2  错误码定义

- FWDT_SUCCESS : success
- FWDT_ERR_INVAL_PARM : invalid input parameters
- FWDT_NOT_READY : driver not ready
- FWDT_NOT_SUPPORT : not support operation
- FWDT_TIMEOUT : wait timeout

### 5.3. 用户API接口

- 获取wdt驱动的默认配置参数

```c
const FWdtConfig *FWdtLookupConfig(u32 instance_id);
```

    Note:
    
    - 用户需要修改配置参数时，可以通过修改返回的FWdtConfig副本，作为后续使用函数的入参，

    Input:

    - u32 instance_id, 当前控制的WDT控制器实例号 

    Return:

    - const FWdtConfig *, 返回驱动默认参数， NULL表示失败


- 设置wdt超时时间

```c
u32 FWdtSetTimeout(FWdtCtrl *pCtrl, u32 timeout);
```

    Note:

    - 此函数会根据传入的超时时间初始化WDT寄存器;
    - WDT两次超时后，才执行系统复位操作；例如希望WDT 6s后复位，则应设置timeout=3;

    Input:

    - FWdtCtrl *pCtrl, WDT驱动实例数据 
    
    - u32 timeout, 设置的WDT超时时间，最大不超过89

    Return:

    - u32, 参考5.2章错误码定义


- WDT喂狗函数

```c
u32 FWdtRefresh(FWdtCtrl *pCtrl);
```

    Note:

    - 此函数会刷新wdt寄存器，重新开始计时

    Input:

    - FWdtCtrl *pCtrl, WDT驱动实例数据 

    Return:

    - u32, 参考5.2章错误码定义

- WDT使能函数

```c
u32 FWdtStart(FWdtCtrl *pCtrl);
```

    Note:

    - 此函数会使能wdt

    Input:

    - FWdtCtrl *pCtrl, WDT驱动实例数据 

    Return:

    - u32, 参考5.2章错误码定义

    
- WDT停止函数

```c
u32 FWdtStop(FWdtCtrl *pCtrl);
```

    Note:

    - 此函数会停止wdt

    Input:

    - FWdtCtrl *pCtrl, WDT驱动实例数据 

    Return:

    - u32, 参考5.2章错误码定义