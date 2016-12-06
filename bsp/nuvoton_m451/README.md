# 新唐M451系列单片机
## 简介
这里参考[BrightPan](https://github.com/bright-pan)之前移植的[nuvoton_m05x](https://github.com/RT-Thread/rt-thread/tree/master/bsp/nuvoton_m05x)，我将RT-thread移植到了Nuvoton(新唐/芯唐) M451单片机上。

目前的工程基于M451 Series_BSP_CMSIS_V3.01.001，运行在Nuvoton M451 NuEdu Board上，仅在application.c内开了一个线程实现了简单的闪灯功能。

暂时只支持KEIL，使用前请前往官网下载Nuvoton驱动，可以使用`scons --target=mdk/mdk4/mdk5 -s`生成工程文件。
