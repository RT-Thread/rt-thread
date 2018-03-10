# V2M-MPS2

## 1. 简介

[V2M-MPS2](https://www.keil.com/boards2/arm/v2m_mps2/)是MDK提供的开发板，配合**Fast Models Debugger**，就可以不依赖任何硬件，在Cortexm-M平台调试代码。板载主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|CPU| 可选Cortex-M0/M0 plus/M3/M4/M7/M23/M33 |
|主频| 50MHz |
|SRAM| 4MB |
|Flash| 4MB |

## 2. 编译说明

V2M-MPS2板级包支持MDK5（已测试MDK5.23~MDK5.25）

## 3. 烧写及执行

### 3.1 配置和仿真

因为Fast Models Debugger的串口功能是通过telnet实现的，所以需要打开Windows的telnet功能：

- [Windows 7: Enabling Telnet Client](https://social.technet.microsoft.com/wiki/contents/articles/910.windows-7-enabling-telnet-client.aspx)
- [Windows 10: Enabling Telnet Client](https://social.technet.microsoft.com/wiki/contents/articles/38433.windows-10-enabling-telnet-client.aspx)

打开project.uvprojx，编译，点击Debug->Start/Stop Session就可以进入仿真了。

### 3.2 如何选择其他内核 

Fast Models Debugger支持Cortex M全系列内核。如果想切换成其他内核，需要完成一些配置，下面以Cortex-M4为例：

- 修改bsp\v2m-mps2\rtconfig.py里的 CPU="cortex-m7"为CPU="cortex-m4"（全小写）
- 点击Project->Option for Target 'RT-Thread V2M-MPS2'：
  - 在Device里选择ARM选项下需要的内核CMSDK_CM4
  - 在Debug里选择Models Cortex-M Debugger，点击Settings：
    - 在Command里选择Cortex-M4的exe：FVP_MPS2_Cortex-M4_MDK.exe
    - 在Target里选择armcortexm4ct

### 3.2 运行结果

进入仿真后全速运行，将会在telnet窗口上看到RT-Thread的启动logo信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.0.3 build Feb 28 2018
 2006 - 2018 Copyright by rt-thread team
finsh />

```

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0/1/2 |
| GPIO | 未支持 |  |
| LED | 未支持 |  |
| BUTTOM | 未支持 | |
| LCD | 未支持 | 需要完成LCD驱动和TOUCH驱动 |


### 4.1 IO在板级支持包中的映射情况（需补充）

| IO号 | 板级包中的定义 |
| -- | -- |
|  | LED0 |

## 5. 联系人信息

维护人：

- [tanek](https://github.com/TanekLiang)

## 6. 参考

* [V2M-MPS2](https://www.keil.com/boards2/arm/v2m_mps2/)
* [Fast Models Debugger](http://www.keil.com/support/man/docs/fstmdls/default.htm)

