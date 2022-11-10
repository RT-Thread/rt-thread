# I2C 驱动程序

## 1. 概述

- E2000 的 MIO 接口可配置为 UART 或 I2C，具体时序特性要求需满足复用功能的时序特性要求。当需要使用对应的功能时，只需要软件进行相应配置.
- MIO 仅仅支持E2000系列芯片

## 2. 驱动功能

MIO 驱动程序管理MIO的功能复用，该驱动程序具备以下功能：

- 选择设置I2C模式或者串口模式
- 获取状态信息和版本信息

## 3. 使用方法

以下部分将指导您完成 MIO 驱动的硬件配置：

- 1. MIO驱动支持 E2000 Q D S，在E2000上完成测试
- 2. 本驱动仅仅作为IIC、串口的功能开启关闭使用，搭配串口驱动，与IIC驱动去使用，无法单独调用去实现具体功能

以下部分将指导您完成 MIO 驱动的软件配置：

- 1. 配置驱动程序，新建应用工程，传入设备ID参数，获取设备参数
- 2. 得到设备参数，操作设置配置项目
- 3. 进行I2C或者uart操作配置流程

## 5. API参考

### 5.1. 用户数据结构

- drivers/mio/fmio/fmio.h

```c

typedef struct
{
    FMioConfig config;  /* mio config */
    u32 is_ready;   /* mio initialize the complete flag */
}FMioCtrl;

```

```c

typedef struct
{
    u32     instance_id;        /*mio id*/
    uintptr func_base_addr; /*I2C or UART function address*/
    u32     irq_num;     /* Device intrrupt id */
    uintptr mio_base_addr;  /*MIO control address*/
    u32     version;            /*mio version*/
    u32     function_type;      /*mio function type*/
    u32     mio_status;         /*mio function type status*/
} FMioConfig;               /*mio configs*/

```
- MIO驱动实例

### 5.3 用户API接口

```c
const FMioConfig *FMioLookupConfig(u32 instance_id);
```
- 获取MIO驱动的默认配置参数

Note:
    
    - 用户需要修改配置参数时，可以通过修改返回的FMioConfig副本，作为FMioSelectFunc函数的入参，

Input:

    - u32 instance_id, 当前控制的MIO控制器实例号    

Return:

    - const FMioConfig *, 返回驱动默认参数， NULL表示失败


```c
FError FMioSelectFunc(uintptr addr, u32 mio_type);
```
- 设置MIO驱动的功能配置

Note:
    - 设置Mio功能

Input:
    - uintptr addr, 当前控制器的MIO基地址
    - u32 mio_type, 想要设置的MIO功能
Return:
    - @return {FError *} 返回错误码

```c
u32 FMioGetFunc(uintptr addr);
```
- 获取当前MIO的配置

Note:
    - 获取Mio功能

Input:
    - uintptr addr, 当前控制器的MIO基地址

Return:
    - @return {u32} 返回MIO的状态

```c
u32 FMioGetVersion(uintptr addr);
```
- 获取版本信息

Note:
    - 获取Mio版本

Input:
    - uintptr addr, 当前控制器的MIO基地址

Return:
    - @return {u32} 返回MIO的版本

```c
FError FMioFuncInit(FMioCtrl *instance_p, u32 mio_type)
```
- 初始化MIO

Note:
    - 初始化MIO的功能

Input:
    - FMioCtrl *instance_p, 当前控制器的结构体
    - u32 mio_type，需要配置的选项,串口还是IIC

Return:
    - @return {u32} 返回初始化的状态

```c
FError FMioFuncDeinit(FMioCtrl *instance_p)
```

- 去初始化MIO

Note:
    - 去初始化MIO的结构体，和相关寄存器

Input:
    - FMioCtrl *instance_p, 当前控制器的结构体

Return:
    - @return {u32} 返回去初始化的状态

```c
uintptr FMioFuncGetAddress(FMioCtrl *instance_p,u32 mio_type);
```
- 获取功能配置的基地址

Note:
    - 获取功能配置的基地址,如果当前配置和目标配置不一致，则失败

Input:
    - FMioCtrl *instance_p, 当前控制器的结构体
    - u32 mio_type, 目标配置的类型UART或者I2c

Return:
    - @return {uintptr} 返回基地址的值

```c
u32 FMioFuncGetIrqNum(FMioCtrl *instance_p,u32 mio_type);
```
- 获取功能的中断号

Note:
    - 获取功能配置的中断号,如果当前配置和目标配置不一致，则失败

Input:
    - FMioCtrl *instance_p, 当前控制器的结构体
    - u32 mio_type, 目标配置的类型UART或者I2c

Return:
    - @return {u32} 返回中断号