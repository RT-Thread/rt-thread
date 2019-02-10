# RT-Thread for Nucleo-STM32H743ZI board	--20170825 MLF
-----------------------------------------------------------
现象：
1、程序运行时LED指示灯闪烁、USART1有系统信息打印、网口可自动获取IP

注意：
1、用MDK5打开工程时，请删掉stm32h7xx_hal_qspi.c文件。
2、auto_rebuild.bat脚本可直接清理、编译并生成MDK、IAR工程。
2、clean.bat脚本可用于清理旧工程。