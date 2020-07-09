# 新唐M451系列单片机
## 简介
这里参考[BrightPan](https://github.com/bright-pan)之前移植的[nuvoton_m05x](https://github.com/RT-Thread/rt-thread/tree/master/bsp/nuvoton_m05x)，将RT-thread移植到了Nuvoton(新唐/芯唐) M451单片机上。

目前的工程基于M451 Series_BSP_CMSIS_V3.01.001，运行在Nuvoton M451 NuEdu Board上，仅在application.c内开了一个线程实现了简单的闪灯功能。

目前已经测试过的平台有：

平台 | 版本 
-----|----------
Keil | MDK4&MDK5
GCC  | GNU Tools ARM Embedded 5.4

## 使用
### Keil
使用前请前往[新唐官网](http://www.nuvoton.com)下载驱动*NuLink_Keil_Driver*。MDK5请安装对应的*Nuvoton Pack*。

* 配置rtconfig.py里的`CROSS_TOOL`为keil以及`EXEC_PATH`为你的Keil根目录
* 使用`scons --target=mdk/mdk4/mdk5 -s`生成对应的工程文件。或者使用`scons`直接编译。

### GCC
这里使用的是*gcc-arm-none-eabi*

* 配置rtconfig.py里的`CROSS_TOOL`为gcc以及`EXEC_PATH`为你gcc-arm-none-eabi可执行文件的位置
* 使用`scons`直接编译。




