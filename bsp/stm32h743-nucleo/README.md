# RT-Thread for Nucleo-STM32H743ZI board	--20170825 MLF
-----------------------------------------------------------
现象：
1. USART3(即板子自带的调试口)有系统信息打印

BSP功能:
1. 支持GPIO设备框架,使用引脚号标识IO口. 如:根据原理图,蓝色LED(LD2)为137脚
2. 支持以太网设备框架, 在LWIP-2.0.2上测试网络可以使用.

注意：
1. 用MDK5打开工程时，请删掉stm32h7xx_hal_qspi.c文件。
2. auto_rebuild.bat脚本可直接清理、编译并生成MDK、IAR工程。
3. clean.bat脚本可用于清理旧工程。
4. scons编译暂不可用. 以MDK5为例
    a. scons --target=mdk5 -s
    b. 打开project, 编译下载后即可运行