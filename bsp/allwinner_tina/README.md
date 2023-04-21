# Allwinner tina板级支持包

## 1. 简介

Allwinner tina 是由全志公司推出的ARM9内核的SOC
包括如下硬件特性：

| 硬件 | 描述 | 
| -- | -- |
|芯片型号| tina系列 |
|CPU| ARM9 |
|主频| 408MHz |
|片内DDR | 32MB |
|板载SPI Nor Flash | 8/16MB|

## 2. 编译说明

| 环境 | 说明 |
| --- | --- |
|PC操作系统|Linux/MacOS|
|编译器|arm-none-eabi-gcc version 6.3.1 20170620 (release)|
|构建工具|scons|
### 2.1 下载源码

```
    git clone https://github.com/RT-Thread/rt-thread.git
```
### 2.2 配置工程并准备env
先下载安装 RT-Thread 的env工具([env工具下载链接][1]),再执行下面命令设置 RT-Thread 操作系统的开发环境
```
    cd rt-thread/bsp/allwinner_tina
    scons --menuconfig
    source ~/.env/env.sh
    pkgs --upgrade
    
```
### 2.3 编译安装下载工具
```
    pushd /tmp
    git clone https://github.com/Icenowy/sunxi-tools.git
    pushd sunxi-tools
    git checkout -b f1c100s origin/f1c100s
    make
    sudo make install
    popd
    popd
```
### 2.4 编译
```
    scons
```
如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。其中rtthread.bin需要烧写到设备中进行运行。

## 3. 烧写及执行
**烧写工具目前仅支持Linux/MacOS环境,请在Linux/MaxOS环境下进行烧写操作**
当正确编译产生出rtthread.bin映像文件后可以使用下面的方式来烧写到设备中。

### 3.1 编译初始化引导文件
编译依赖 arm-eabi-gcc
```
    pushd ../../..
    git clone https://github.com/lymzzyh/tina-spl.git
    pushd tina-spl
    make
    cp output/f1c100s.bin ../rt-thread/bsp/tina/tina-spl.bin
    popd
    popd
```
### 3.2 下载并运行


1. 短接flash 1、4脚(当flash中无可引导代码时无需此步骤)
2. 连接USB
3. 松开短接的引脚
4. 输入下列指令


```
    sudo sunxi-fel -p write  0x00000000 tina-spl.bin
    sudo sunxi-fel exec 0x00000000
    sudo sunxi-fel -p write  0x80000000 rtthread.bin
    sudo sunxi-fel exec 0x80000000
```

### 3.3 运行结果

如果编译 & 烧写无误，会在串口0上看到RT-Thread的启动logo信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     3.0.2 build Feb  8 2018
 2006 - 2017 Copyright by rt-thread team
periph_get_pll_clk:600000000
cpu_get_clk:408000000
ahb_get_clk:200000000
apb_get_clk:100000000
msh />
```


## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | ------  |
| UART | 支持 | UART0/1/2 |
| GPIO | 支持 | / |
| clock | 支持 | / |
| mmu | 支持 | / |


### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| PE8 | USART2 RX |
| PE7 | USART2 TX |
| PA3 | USART1 RX |
| PA2 | USART1 TX |
| PE1 | USART0 TX |
| PE0 | USART0 RX |


## 5. 联系人信息

维护人:
[lymzzyh][2] < [lymz@foxmail.com][3] >


  [1]: https://www.rt-thread.org/download.html#download-rt-thread-env-tool
  [2]: https://github.com/lymzzyh
  [3]: mailto:lymz@foxmail.com
