# RV32M1-VEGA 板级支持包

## 1. 简介

RV32M1 VEGA开发板是一款多核异构的RISC-V 32开发板，包含了两个RISC-V 32位核心，同时也包括了BLE外设。

| 硬件 | 描述 |
| -- | -- |
|芯片型号| VEGA RV32M1 |
|CPU| RV32IMC, with extensons for post-incrementing load and stores, |
| | multiply-accumulate extensions, ALU extensions, hardware loops. |
| | RV32IEMC |
|主频| 48MHz或72MHz |
| | 48MHz或72MHz |
|片内SRAM| 256kB + 128kB |
|片内Flash| 1MB + 256kB |

## 2. 编译说明

当前测试的工具链是以标准的GNU GCC 7.2.0 & newlib 2.5.0方式，并以标准的RV32IMC构架进行编译，所以RVIMC核的扩展指令未支持。RT-Thread ENV版本是1.0。

Windows上编译推荐使用[env工具][1]，可以在console下进入到`vega/ri5cy`目录中，运行以下命令：

    scons

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。其中rtthread.bin需要烧写到设备中进行运行。

## 3. 烧写及执行

使用USB线连接到openocd的USB口，在PC上也讲会出现一个串口设备，可以使用115200-N-8-1的配置方式打开这个串口。设备使用的串口引脚是：`[PTC7/PTC8]`

当正确编译产生出rtthread.bin映像文件后，可以使用...的方式来烧写到设备中。

### 3.1 运行结果

如果编译 & 烧写无误，当按`SW1`复位按钮复位设备后，会在串口上看到RT-Thread的启动logo信息：

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------  |
| UART | 支持 | UART0, RX(PTC7), TX(PTC8) |
|  | 未支持 | UART1, RX(PTA25), TX(PTA26) |
| clock | 支持 |  |

### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级代码中的定义 |
| -- | -- |
| PTA22 | LED_BLUE |
| PTA23 | LED_GREEN |
| PTA24 | LED_RED |
| PTA24 | LED_STS |
| PTE8 | BTN_SW3 |
| PTE9 | BTN_SW4 |
| PTE12 | BTN_SW5 |
| PTA0 | BTN_SW2/BTN_NMI |

## 5. 联系人信息

维护人：xxx < abc@name.com >

## 6. 参考

* 板子[数据手册][2]
* 芯片[数据手册][3]

  [1]: https://www.rt-thread.org/page/download.html
  [2]: http://abc.com/datasheet.pdf
  [3]: http://abc.com/um.pdf
