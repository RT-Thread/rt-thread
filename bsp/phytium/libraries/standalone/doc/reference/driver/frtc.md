# RTC 驱动程序

## 1. 概述

- 实时时钟(RTC)提供可靠的系统时间，包括年月日和时分秒。

- 通过采用电池供电，在系统处于关机状态时，RTC也能正常工作。

- RTC 驱动支持的平台包括 FT2000/4、D2000。

## 2. 功能

RTC 驱动程序主要完成RTC模块的初始化、时间设置和读取，该驱动程序具备以下功能：
- 初始化RTC模块
- 设置RTC时间
- 读取RTC时间

相关源文件为：
```
frtc
    ├── frtc.c
    ├── frtc.h
    ├── frtc_g.c
    ├── frtc_hw.c
    ├── frtc_hw.h
    ├── frtc_intr.c
    └── frtc_sinit.c
```


## 3. 配置方法

以下部分将指导您完成 RTC 驱动的软件配置:

- 配置驱动程序，新建应用工程，使能RTC驱动模块
- 设置配置参数
- 设置RTC时间
- 读取RTC时间

## 4. 应用示例


### [rtc_test](../../../baremetal/example/rtc_test/README.md)


## 5. API参考


### 5.1. 用户数据结构

- drivers/rtc/frtc/frtc.h

```c
typedef struct
{
	uintptr control_base_addr; /* rtc控制寄存器基地址 */
	const char *instance_name; /* instance name */
} FRtcConfig;				   /* rtc配置 */

typedef struct
{
	FRtcConfig config; 	/* rtc配置 */
	u32 is_ready;		/* rtc初始化完成标志 */
} FRtcCtrl;
```

- RTC时间实例配置

```c
typedef struct
{
	u16 year;  /*Specifies the RTC Date Year.
				This parameter must be a number between Min_Data = 2000 and Max_Data = 2099 */
	u8 month;  /*Specifies the RTC Date Month.
				This parameter must be a number between Min_Data = 1 and Max_Data = 12 */
	u8 mday;   /*Specifies the RTC day of Month.
				This parameter must be a number between Min_Data = 1 and Max_Data = 31 */
	u8 hour;   /*Specifies the RTC Time Hour.
				This parameter must be a number between Min_Data = 0 and Max_Data = 23 */
	u8 minute; /*Specifies the RTC Time Minute.
				This parameter must be a number between Min_Data = 0 and Max_Data = 59 */
	u8 second; /*Specifies the RTC Time Second.
				This parameter must be a number between Min_Data = 0 and Max_Data = 59 */
} FRtcDateTime;
```
### 5.2  错误码定义

- 模块错误码编号 `0x1020000`

- [0x0] FRTC_SUCCESS : success

- [0x1020001] FRTC_ERR_DATE_INVALID : invalid date parameters

- [0x1020002] FRTC_ERR_TIME_INVALID : invalid time parameters


### 5.3. 用户API接口

- 获取RTC驱动的默认配置参数

```c
const FRtcConfig *FRtcLookupConfig(void);
```

    Note:

    - 用户需要修改配置参数时，可以通过修改返回的FRtcConfig副本，作为后续使用函数的入参，

    Input:

    - void, 只有一个RTC模块    

    Return:

    - const FRTCConfig *, 返回驱动默认参数， NULL表示失败


- 初始化RTC驱动
```c
FError FRtcCfgInitialize(FRtcCtrl *instance_p, const FRtcConfig *config_p);
```

    Note:

    - 用户需要修改配置参数时，可以通过修改返回的FRtcConfig副本，作为后续使用函数的入参，

    Input:

    - FRtcCtrl *instance_p, RTC驱动控制块 
    - const FRtcConfig *config_p, RTC驱动配置数据

    Return:

    - 返回初始化错误码，FRTC_SUCCESS表示初始化成功

- 设置RTC时间

```c
FError FRtcSetDateTime(FRtcCtrl *pctrl, const FRtcDateTime *date_time);
```

    Note:

    - 此函数会根据传入的时间初始化RTC时间寄存器

    Input:

    - FRtcCtrl *pctrl, RTC驱动实例数据 
    
    - const FRtcDateTime *date, 设置的RTC时间年月日时分秒

    Return:

    - u32, 参考5.2章错误码定义

- 读取RTC时间

```c
FError FRtcGetDateTime(FRtcCtrl *pctrl, FRtcDateTime *date_time);
```

    Note:

    - 此函数会获取当前的RTC时间

    Input:

    - FRtcCtrl *pctrl, RTC驱动实例数据 
    
    - FRtcDateTime *date, 获取的RTC时间年月日时分秒

    Return:

    - u32, 参考5.2章错误码定义

- 读取RTC时间戳

```c
time_t FRtcReadTimeStamp(FRtcCtrl *pctrl, time_t *sec, time_t *msec);
```

    Note:

    - 此函数会读取RTC时间，并返回time_t格式的时间值

    Input:

    - FRtcCtrl *pctrl, RTC驱动实例数据

    - time_t *sec, 获取的秒时间戳，传入NULL表示不需要获取
    
    - time_t *msec, 获取的毫秒时间戳，传入NULL表示不需要获取

    Return:

    - time_t, 详见<time.h>中的定义
