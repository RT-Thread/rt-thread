开发板：Renesas YRDKRX62N
芯片：  R5F562N8BDFP   RX62N8
编译器: IAR Embedded Workbench for Renesas RX 2.60.5
		IAR Embedded Workbench common components 7.0.6.3257
		(30天评估版)
LIBCPU: rx文件夹，当前只是针对iar版本。
注意：串口驱动部分配置函数个别串口管脚可能对应不上，所以最好用库的或者自己弄一个。当前确定能用的是2、6、1，其他没试。
	  该BSP只是作为rtt验证，因此只跑最小系统并测试FINSH,其他功能没有测试。