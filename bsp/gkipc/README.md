# gkipc板级支持包

标签： bsp说明文档

---

## 1. 简介

GK7102C是针对高清IP Camera产品开发的一款低功耗高性能 SOC芯片，支持 960@30p多路码流 H.264 编码及高质量的 ISP 处理，内置  3D降噪和动态对比度提升模块，支持主流的多种并口 8bit/10bit/12bit sensor。视频输出支持 RGB 小型 LCD 屏显示接口。 GK7102C 内封 DDR2 DRAM 芯片，内置 Ethernet PHY, Audio codec,USB PHY 等模拟 IP。 GK7102C 拥有
丰富的外设接口,如 USB2.0,SDIO,PWM,SPI,I2C 等等，支持最多 32 个GPIO，可灵活配置各功能模块的输出管脚，为实现高集成度 IPC提供了高性价比的解决方案。包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| GK7102C |
|CPU| ARM1176ZJFS |
|主频| 432MHz |
|片内DDR2|  512M bit@800MHz |


## 2. 编译说明

推荐使用[env工具][1]，可以在console下进入到`bsp/gkipc`目录中，运行以下命令：

    scons

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。其中rtthread.bin可以通过网络加载或者烧写到设备中进行运行。

## 3. 烧写及执行

[需要说明电源连接情况，串口连接情况]

连接好串口，可以使用115200-N-8-1的配置方式连接到设备上。设备使用的串口引脚是：`[GPIO25/GPIO26]`

当正确编译产生出rtthread.bin映像文件后，可以使用tftp的方式来加载到设备中运行。

### 3.1 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0/1/2 |
| clock | 支持 |  |
| SPI |  | SPI0 |
| ADC | 支持 |  |
| DMA | 支持 |  |
| GMAC | 支持 |  |
| I2C | 支持 |  |
| PWM | 支持 |  |
| SDIO | 支持 | SDIO0/1 |
| WDT | 支持 |  |
| MMC | 支持 |  |
| SSI | 支持 |  |

## 5. 联系人信息

维护人：gokemicro < gokemicro@yeah.net >

[1]: https://www.rt-thread.org/page/download.html