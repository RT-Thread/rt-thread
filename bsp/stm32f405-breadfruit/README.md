## board info:

    SM1432F405
    http://sanmuchina.taobao.com

## note:

in drivers/stm32f4xx_conf.h

```
    /* Redefine the HSE value; it's equal to 8 MHz on the STM32F4-DISCOVERY Kit */
    efine HSE_VALUE    ((uint32_t)8000000)
```
 
 **================= IAR WARNING =================**
 
After use `scons --target=iar -s` command to product IAR project, you have to add iar link file manually.

IAR IDE steps:
1. Project-->Options-->Linker
2. Config-->Linker Configuration file
3. select `Override Default`, then select `bsp/stm32f40x/stm32f40x_flash.icf`
4. rebuild project

**TODO**

auto add *.icf by scons script

**log**

add dfu tools/dfu/dfu.py
add bsp/stm32f405



# SM1432F405板级支持包

## 1. 简介

SM1432F405 是由三木电子科技有限公司推出的CotexM4内核的板卡
包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| STM32F405RGT6 |
|CPU| Cortex-M4 |
|主频| 168MHz |
|片内SRAM |192+4KB  |
|片内Flash | 1MB|

## 2. 编译说明

| 环境 | 说明 |
| --- | --- |
|PC操作系统|Linux|
|编译器|arm-none-eabi-gcc version 6.3.1 20170620 (release)|
|构建工具|scons|
1) 下载源码

```
    git clone https://github.com/slcmcu/rt-thread.git
```
2) 配置工程并准备env
```
    cd rt-thread/bsp/sm1432f405
    scons --menuconfig
    source ~/.env/env.sh
    pkgs --upgrade
    
```
3) 编译安装下载工具
```
    sudo apt-get install scons
```
4) 编译
```
    scons
```
如果编译正确无误，会产生rtthread.elf、rtthread.bin,rtthread.dfu文件。其中rtthread.dfu需要烧写到设备中进行运行。

## 3. 烧写及执行
**烧写工具目前仅支持Win7X64环境,请在Win7x64环境下进行烧写操作**
当正确编译产生出rtthread.dfu映像文件后可以使用下面的方式来烧写到设备中。

1)编译初始化引导文件
编译依赖 arm-eabi-gcc
```
    mkdir project
    cd project
    git clone https://github.com/slcmcu/rt-thread.git
    cd slcmcu/bsp/sm1432f405
    scons
    sh dfu.sh
    cp rtthread.dfu  ~/project
```
2)下载并运行

1.短接T0和3V3
2.在win7x64系统下打开dfu下载工具
3.连接开发板的usb到PC机
4.在dfu工具上选择下载镜像文件rtthread.dfu
5.更新镜像到开发板
### 3.1 连接usb转串口模块
| SM1432F405 | SM12H340F |
| -- | -- |
| PA3 |  TX |
| PA2 |  RX |
| GND |  GND |

串口波特率设置115200,8,n,1

### 3.1 运行结果

如果编译 & 烧写无误，会在串口2上看到RT-Thread的启动logo信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     3.0.2 build Feb  8 2018
 2006 - 2017 Copyright by rt-thread team
```


## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | :----:  | :------:  |



### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| PA3 | USART2 RX |
| PA2 | USART2 TX |



## 5. 联系人信息

维护人:
[sun-lichao@163.com ]


  [1]: https://www.rt-thread.org/page/download.html
  [4]: https://github.com/slcmcu/rt-thread
  [5]: mailto:sun-lichao@163.com

