# 芯片引脚控制

## 1. 概述

- 芯片引脚控制 (Pin Ctrl)用于引脚功能配置和引脚延迟配置，开发板上常存在某些 IO 之间存在共用同一物理引脚情况，即引脚复用，同时，通用 IO 引脚还可以配置引脚延迟
- FPinCtrl 支持芯片引脚控制功能，支持 FT2000/4、D2000 和 E2000

## 2. 功能

- FPinCtrl 主要提供引脚控制相关的功能配置，包括
- 1. 控制复用功能
- 2. 控制引脚驱动能力，只支持E2000平台
- 3. 配置引脚的上下拉电阻
- 4. 调节引脚的输入输出延迟

- 相关的源文件包括
```
fpinctrl.h
    fiopad.h  --> E2000
    fiopad.c

    fioctrl.h --> FT2000/4, D2000
    fioctrl.c
```

## 3. 配置方法

- 不需要特别配置

## 4. 应用示例

- 设置引脚的复用，驱动能力和上下拉电阻等

### [fpin_test](../../../baremetal/example/peripheral/pin/fioctrl_test)

- IO 引脚延时配置索引，参考 D2000/FT2000-4 数据手册的"表 5-32 通用 IO 引脚延时配置寄存

> 调用 FIOCTRL_INDEX 生成PAD对应的索引，e.g.

| 偏移    | 位域 |  说明 |
| -------- | ------- | ------- |
|0x0208  |  [27 : 26] | 控制 i2c_0_scl_pad 的上下拉 2'b10 |
|        |  [25 : 24] | 控制 i2c_0_scl_pad 的复用功能 2'b00 |

```c
    #define FIOCTRL_I2C0_SCL_PAD        (FPinIndex)FIOCTRL_INDEX(0x208, 24) /* i2c0-scl: func 0 */
```
> 定义控制域为 i2c0_scl_pad 的PAD，其中延时配置寄存器偏移量为0x208, 输入延时配置位从第24位开始

## 5. API参考

Note:

- FT2000/4 和 D2000 平台，使用FIOCTRL_INDEX 宏定义的 index 作为引脚索引
- E2000 平台，使用 FIOPAD_INDEX 宏定义的 index 作为引脚索引

#### FPinGetFunc

```c
FPinFunc FPinGetFunc(const FPinIndex pin);
```

Note:

- 获取IO引脚当前的复用功能

Input:

- {FPinIndex} pin IO引脚索引

Return:

- {FPinFunc} 当前的复用功能

#### FPinSetFunc

```c
void FPinSetFunc(const FPinIndex pin, FPinFunc func);
```

Note:

- 设置IO引脚复用功能

Input:

- {FPinIndex} pin IO引脚索引
- {FPinFunc} func IO复用功能

Return:

- 无

#### FPinGetPull

```c
FPinPull FPinGetPull(const FPinIndex pin);
```

Note:

- 获取IO引脚当前的上下拉设置

Input:

- {FPinIndex} pin IO引脚索引

Return:

- {FPinPull} 当前的上下拉设置

#### FPinSetPull

```c
void FPinSetPull(const FPinIndex pin, FPinPull pull);
```

Note:

- 设置IO引脚当前的上下拉

Input:

- {FPinIndex} pin IO引脚索引
- {FPinPull} pull 上下拉设置

Return:

- 无

#### FPinGetDelay

```c
FPinDelay FPinGetDelay(const FPinIndex pin, FPinDelayDir dir, FPinDelayType type);
```

Note:

- 获取IO引脚当前的延时设置

Input:

- {FPinIndex} pin IO引脚延时设置索引
- {FPinDelayDir} dir 输入/输出延时
- {FPinDelayType} type 精调/粗调延时

Return:

- {FPinDelay} 当前的延时设置

#### FPinGetDelayEn

```c
boolean FPinGetDelayEn(const FPinIndex pin, FPinDelayDir dir);
```

Note:

- 获取IO引脚当前的延时使能标志位

Input:

- {FPinIndex} pin IO引脚延时设置索引
- {FPinDelayDir} dir 输入/输出延时

Return:

- {boolean} TRUE: 使能延时, FALSE: 去使能延时

#### FPinSetDelay

```c
void FPinSetDelay(const FPinIndex pin, FPinDelayDir dir, FPinDelayType type, FPinDelay delay);
```

Note:

- 设置IO引脚延时

Input:

- {FPinIndex} pin IO引脚延时设置索引
- {FPinDelayDir} dir 输入/输出延时
- {FPinDelayType} type 精调/粗调延时
- {FPinDelay} delay 延时设置

Return:

- 无

#### FPinSetDelayEn

```c
void FPinSetDelayEn(const FPinIndex pin, FPinDelayDir dir, boolean enable);
```

Note:

- 使能/去使能IO引脚延时

Input:

- {FPinIndex} pin IO引脚延时设置索引
- {FPinDelayDir} dir 输入/输出延时
- {boolean} enable TRUE: 使能, FALSE: 去使能

Return:

- 无

#### FPinGetDrive

```c
FPinDrive FPinGetDrive(const FPinIndex pin);
```

Note:

- 获取IO引脚的驱动能力
- 只支持 E2000 平台

Input:

- {FPinIndex} pin IO引脚索引

Return:

- {FPinDrive} 引脚的当前的驱动能力

#### FPinSetDrive

```c
void FPinSetDrive(const FPinIndex pin, FPinDrive drive);
```

Note:

- 设置IO引脚的驱动能力
- 只支持 E2000 平台

Input:

- {FPinIndex} pin, IO引脚索引
- {FPinDrive} drive, 引脚驱动能力设置

Return:

- 无

#### 

```c

```

Note:

- 

Input:

- 

Return:

- 