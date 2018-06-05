# HIFIVE1 #

## 简介

[HIFIVE1](https://www.sifive.com/products/hifive1/)是SiFive提供的一款基于RISCV的开发板，搭载SiFive Freedom E310。

板载主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|CPU| SiFive E31 RISC-V Core |
|架构| 32-bit RV32IMAC |
|主频| 320+ MHz |
|SRAM| 16KB |
|Flash| 16MB QSPI + 16KB 指令Cache |

## 编译说明

HIFIVE1可以自行编译工具链，或者使用SiFive提供的[二进制版本](https://www.sifive.com/products/tools/)。


## 烧写及执行

供电方式：开发板使用 Micro USB 线连接电脑和开发板。

下载程序：参看[hifive1-getting-started](https://static.dev.sifive.com/dev.../hifive1/hifive1-getting-started-v1.0.2.pdf)完成开发环境的配置，运行bsp里的openocd.sh脚本就可以下载程序了。

### 运行结果

下载程序之后，连接串口(115200-N-8-1)，可以看到RT-Thread的输出信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     3.0.4 build May 30 2018
 2006 - 2018 Copyright by rt-thread team
msh >
```

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 |  |
| GPIO | 未支持 |  |
| SPI | 未支持 |  |
| I2C | 未支持 |  |

### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| GPIO19 | LED_GREEN |
| GPIO21 | LED_BLUE |
| GPIO22 | LED_RED |

## 5. 联系人信息

维护人：
- [tanek](https://github.com/TanekLiang)

## 6. 参考

* [HIFIVE1 Info](https://www.sifive.com/products/hifive1/)
* [HIFIVE1 Software Development Tools](https://www.sifive.com/products/tools/)
* [hifive1-getting-started-guide](https://www.sifive.com/documentation/boards/hifive1/hifive1-getting-started-guide/)
* [hifive1-schematics](https://www.sifive.com/documentation/boards/hifive1/hifive1-schematics/)


