# Raspberry PI 4-dm2.0BSP说明

## 1. 简介

树莓派4B的核心处理器为博通BCM2711（四核1.5GHz，Cortex A72架构，树莓派3是四核A53）。LPDDR4内存，由5V/3A USB-C供电或GPIO 5V。

外设支持上，引入了双频Wi-Fi，蓝牙5.0，千兆网卡，MIPI CSI相机接口，两个USB口，40个扩展帧。

这份RT-Thread BSP是针对 Raspberry Pi 4的一份移植，树莓派价格便宜, 使用者甚众，是研究和运行RT-Thread的可选平台之一。


## 2. 编译说明

推荐使用[env工具](https://www.rt-thread.org/download.html#download-rt-thread-env-tool)，可以在console下进入到`bsp\raspberry-pi\raspi4-64`目录中，运行以下命令：

```
scons
```

来编译这个板级支持包。如果编译正确无误，会产生 `rtthread.elf`, `rtthread.bin` 文件。

## 3. 支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | pl011驱动 |
| GPIO | 尚未支持 | 等待dm2.0相关代码合入主线 |
| SPI | 尚未支持 | 等待gpio合入主线 |
| WATCHDOG | 尚未支持 | 等待gpio合入主线 |
| HDMI | 尚未支持 | 等待gpio合入主线 |
| SDIO | 支持 | 能够正常运行在qemu，但是qemu对于raspi目前只支持pio传输，后续需要硬件进行详细测试 |
| ETH | 尚未支持 | 等待gpio合入主线 |

