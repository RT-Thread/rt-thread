 **中文** | [English](README_en.md)

## 概述
CV18xx 系列芯片面向民用消费监控 IP 摄像机、居家智能等多项产品领域而推出的高性能、低功耗芯片，集成了 H.264/H.265 视频压缩编码器和 ISP；支持数字寛动态、 3D 降噪、除雾、镜头畸变校正等多种图像增强和矫正算法，为客户提供专业级的视频图像质量。

1. 处理器内核

- 主处理器 RISCV C906 @ 1.0Ghz
  - 32KB I-cache, 64KB D-Cache
  -  集成矢量(Vector)及浮点运算单元 (FPU) .
- 协处理器 RISCV C906 @ 700Mhz
  - 集成浮点运算单元 (FPU)

2. 存储器接口
- 内建 DRAM : DDR2 16bitx1, 最高速率达 1333Mbps , 容量512Mbit (64MB)
- 支持SPI NOR flash 接口 (1.8V / 3.0V)
  - 支持 1, 2, 4 线模式
  - 最大支持 256MByte
- 支持 SPI Nand flash 接口 (1.8V / 3.0V)
  - 支持 1KB/2KB/4KB page (对应的最大容量 16GB/32GB/64GB)
  - 使用器件本身内建的 ECC 模块

3. 外设
- Up to 26 GPIO pins on the MilkV-Duo 40-pin header provide access to internal peripherals such as SDIO, I2C, PWM, SPI, J-TAG, and UART
- Up to 3x I2C
- Up to 5x UART
- Up to 1x SDIO1
- Up to 1x SPI
- Up to 2x ADC
- Up to 7x PWM
- Up to 1x RUN
- Up to 1x JTAG
- 集成 MAC PHY 支持 10/100Mbps 全双工或半双工模式
- 一个 USB Host / device 接口

4. [GPIO 引脚分布](https://milkv.io/zh/docs/duo/getting-started/duo256m#gpio-%E5%BC%95%E8%84%9A%E5%88%86%E5%B8%83)

## Toolchain 下载
1. RT-Thread 标准版工具链：`riscv64-unknown-elf-gcc` 下载地址  [https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz](https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz)

2. RT-Smart 版工具链： `riscv64-unknown-linux-musl-gcc` 下载地址 [https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2](https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2)

> 注：
当前 bsp 只支持 Linux 编译，推荐 ubuntu 22.04

正确解压后，在`rtconfig.py`中将 `riscv64-unknown-elf-gcc` 或 `riscv64-unknown-linux-musl-gcc` 工具链的本地路径加入 `EXEC_PATH` 或通过 `RTT_EXEC_PATH` 环境变量指定路径。

```shell
# RT-Thread 标准版按照以下配置：
$ export RTT_CC_PREFIX=riscv64-unknown-elf-
$ export RTT_EXEC_PATH=/opt/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1/bin

# RT-Samrt 版按照以下配置：
$ export RTT_CC_PREFIX=riscv64-unknown-linux-musl-
$ export RTT_EXEC_PATH=/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin
```

## 编译

### 依赖安装
```shell
$ sudo apt install -y scons libncurses5-dev device-tree-compiler
```

## 修改当前工程配置

Linux平台下，执行：
```shell
$ scons --menuconfig
```

1. 默认编译为 RT-Thread 标准版，如果需要编译为 RT-Smart 版，请按照如下方式修改：
```shell
RT-Thread Kernel  --->
    [*] Enable RT-Thread Smart (microkernel on kernel/userland)

    (0x80000000) The virtural address of kernel start
```

2. 选择当前需要编译的目标开发板类型：
```shell
Board Type (milkv-duo)  --->
    ( ) milkv-duo
    ( ) milkv-duo-spinor
    (X) milkv-duo256m
    ( ) milkv-duo256m-spinor
```

它会自动下载env相关脚本到~/.env目录，然后执行
```shell
$ source ~/.env/env.sh
$ pkgs --update
```
更新完软件包后，执行 `scons -j10` 或 `scons -j10 --verbose` 来编译这个板级支持包，编译正确无误，会产生 rtthread.elf 文件。

编译完成后脚本自动调用 `./mksdimg.sh` 脚本进行打包，并生成 `boot.sd`, 该文件即为 SD 卡启动的 kernel 文件。


## 运行
1. 将 SD 卡分为 2 个分区，第 1 个分区用于存放 bin 文件，第 2 个分区用于作为数据存储分区，分区格式为 `FAT32`。
2. 将根目录下的 `fip.bin` 和 `boot.sd` 复制 SD 卡第一个分区中。后续更新固件只需要复制 `boot.sd` 文件即可。
其中：
- fip.bin：fsbl、 opensbi 和 uboot 打包后的 bin 文件
- boot.sd：kernel 打包后的 bin 文件

更新完 `boot.sd` 后， 重新上电可以看到串口的输出信息：
```shell
U-Boot 2021.10 (Jun 26 2023 - 14:09:06 +0800)cvitek_cv180x

DRAM:  63.3 MiB
gd->relocaddr=0x82435000. offset=0x2235000
MMC:   cv-sd@4310000: 0
Loading Environment from <NULL>... OK
In:    serial
Out:   serial
Err:   serial
Net:
Warning: ethernet@4070000 (eth0) using random MAC address - 62:80:19:6c:d4:64
eth0: ethernet@4070000
Hit any key to stop autoboot:  0
Boot from SD ...
switch to partitions #0, OK
mmc0 is current device
132692 bytes read in 12 ms (10.5 MiB/s)
## Loading kernel from FIT Image at 81400000 ...
   Using 'config-cv1800b_milkv_duo_sd' configuration
   Trying 'kernel-1' kernel subimage
   Verifying Hash Integrity ... crc32+ OK
## Loading fdt from FIT Image at 81400000 ...
   Using 'config-cv1800b_milkv_duo_sd' configuration
   Trying 'fdt-cv1800b_milkv_duo_sd' fdt subimage
   Verifying Hash Integrity ... sha256+ OK
   Booting using the fdt blob at 0x8141b590
   Uncompressing Kernel Image
   Decompressing 296768 bytes used 42ms
   Loading Device Tree to 0000000081be5000, end 0000000081becb60 ... OK

Starting kernel ...

heap: [0x802766b0 - 0x812766b0]

 \ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Apr  7 2024 23:33:20
 2006 - 2024 Copyright by RT-Thread team
Hello RISC-V!
msh />
```
