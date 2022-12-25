# 博流智能 BL808板级支持包说明

## 1. 简介

BL808 是高度集成的 AIoT 芯片组，具有 Wi-Fi/BT/BLE/Zigbee 等无线互联单元，包含多个 CPU 以及音频编码译码器、视频编码译码器和 AI 硬件加速器，适用于各种高性能和低功耗应用领域。

BL808 系列芯片主要包含无线和多媒体两个子系统。

无线子系统包含一颗 RISC-V 32-bit 高性能 CPU（m0），集成 Wi-Fi/BT/Zigbee 无线子系统，可以实现多种无线连接和数据传输，提供多样化的连接与传输体验。
多媒体子系统包含一颗 RISC-V 64-bit 超高性能 CPU（d0），集成 DVP/CSI/ H264/NPU 等视频处理模块，可以广泛应用于视频监控/智能音箱等多种 AI 领域

多媒体子系统组成部分如下：

- NPU HW NN 协处理器 (BLAI-100)，适用于人工智能应用领域
- 摄像头接口
- 音频编码译码器
- 视频编码解码器
- 传感器
- 显示接口

电源管理单元控制低功耗模式。此外，还支持各种安全功能。

外围接口包括 USB2.0、 Ethernet、 SD/MMC、 SPI、 UART、 I2C、 I2S、 PWM、 GPDAC/GPADC、 ACOMP、 PIR、 Touch、
IR remote、 Display 和 GPIO。

支持灵活的 GPIO 配置， BL808 最多可达 40 个 GPIO。  

芯片规格包括如下：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| bl808 |
|CPU| 三核异构RISC-V CPUs： <br />RV64GCV 480MHz<br/>RV32GCP 320MHz<br/>RV32EMC 160MHz |
|RAM| 768KB SRAM + 64MB UHS PSRAM |
| 外设 | 内嵌AES与SHA256算法加速器 |
| AI NN 通用硬件加速器 | BLAI-100 用于视频/音频检测/识别，100GOPS 算力 |
| 摄像头接口 | DVP 和 MIPI-CSI |
| 显示接口 | SPI、DBI、DPI(RGB) |
| 无线 | 支持 Wi-Fi 802.11 b/g/n<br/>支持 Bluetooth 5.x Dual-mode(BT+BLE)<br/>支持 Wi-Fi / 蓝牙 共存 |

## 2. 编译说明

BL808是多核异构架构，每个核需要单独编译，并烧录到对应的位置。

Windows下推荐使用[env工具][1]，然后在console下进入bsp/bl808目录中，选择需要编译的核心，m0或d0，运行：

    cd bsp/bl808/m0
    menuconfig
    pkgs --update

如果在Linux平台下，可以先执行

    scons --menuconfig

它会自动下载env相关脚本到~/.env目录，然后执行

    source ~/.env/env.sh
    
    cd bsp/bl808/m0
    pkgs --update
下载risc-v的工具链，[下载地址](https://occ.t-head.cn/community/download?id=4073475960903634944)或[下载地址](https://dl.sipeed.com/shareURL/others/toolchain)

更新完软件包后，在`rtconfig.py`中将risc-v工具链的本地路径加入文档。

然后执行scons编译：  

```
    set RTT_EXEC_PATH=C:\Users\xxxx\Downloads\Xuantie-900-gcc-elf-newlib-x86_64-V2.6.1/bin
    scons
```
来编译这个板级支持包。

或者通过 `scons --exec-path="GCC工具链路径"` 命令，在指定工具链位置的同时直接编译。

如果编译正确无误，会产生rtthread.elf、rtthread_m0.bin文件。其中rtthread_m0.bin需要烧写到设备中进行运行。  

## 3. 烧写及执行

连接好串口，然后使用[Bouffalo Lab Dev Cube](https://dev.bouffalolab.com/download)工具进行烧写bin文件。

![Bouffalo Lab Dev Cube](figures/program.jpg)

### 3.1 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

![terminal](figures/bl808.jpg)

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0，用于shell，默认波特率2000000 |

## 5. 联系人信息

维护人：[flyingcys](https://github.com/flyingcys)

## 6. 参考

* 芯片[datasheet][2]

  [1]: https://www.rt-thread.org/page/download.html 
  [2]: https://github.com/bouffalolab/bl_docs
