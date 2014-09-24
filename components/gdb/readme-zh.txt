说明: 

一 当前版本进度

1).分类
考虑到arm各种版本的调试寄存器地址和种类都有很大不同
所以分为两个版本,均只在GCC下编译

	1.基础ARM(软件断点(使用undef指令的办法),需要ram运行，模拟单步)
	2.cortex M系列(不支持M0,基于寄存器操作,支持硬件断点，数据观察点,硬件单步)

理论上cortexA系列和cortexM的调式单元是一样的,有需要的话也可以在基础arm版本里单独为cortexA做出可选的数据断点,硬件单步

二 安装说明

1) 下载
	下载最新RT-THREAD GDB STUB代码,并解压

2) 加入RT-Thread
	先将得到的components文件夹覆盖RTT根目录
	然后若要使用BBB板测试GDB,就用BSP/beaglebone和libpcu/am335x覆盖RTT下的同名文件夹

	若要使用STM32F407测试GDB,就用BSP/stm32F4xx覆盖RTT下的同名文件夹,同时更改编译器为gcc

3) 宏
	打开RT_USING_GDB

三 宏配置说明

1) RT_GDB_HAVE_HWBP
	1硬件断点

2) RT_GDB_HAVE_SWBP
	1软件断点

3) RT_GDB_MAX_BREAKPOINTS
	最大软件断点数量
	不加默认20

4) RT_GDB_ICACHE
	是否使用ICACHE
	若使用了ICACHE则要开启此宏,保证断点覆盖后及时刷新

5) RT_GDB_DEBUG
	测试开发用
	会打印GDB收发信息到默认串口上,以供获取数据
 
四 使用说明

1) 设置serial设备
	首先需要调用
		void gdb_set_device(const char* device_name);    (gdb_stub.h)
	设置相应的GDB通信端口
	PS:
	首先serial的驱动不能是中断
	其次收发函数最好是poll的,要不就是9600,不然可能会出现问题
	若出现问题,请打开 RT_GDB_DEBUG ,观察收发是否正常。

2) 进入GDB stub
	调用
		void gdb_start();  (gdb_stub.h)
	触发异常,即可进入等待状态 等待GDB连接
	也可以将该函数加入按键中断中,可以实现外部打断程序的效果(条件有限,未测试)

3) pc连接
	确认GCC 打开-g选项后编译
	然后arm-none-eabi-gdb xxxx.elf or axf
	进如GDB界面后
	set serial baud 115200(or 9600)
	target remote /dev/ttyUSB0(linux)  or COM1 (windows)
	即可实现GDB对接

PS:
	BBB板默认uart4作为GDB通信口
	STM32F407默认uart6作GDB通信

五 移植说明

若要移植到不同架构上
软件实现请参考gdb/libcpu/arm下的文件
硬件实现请参考gdb/libcpu/cortexm下的文件
需要rsp协议的话 请参考https://www.sourceware.org/gdb/current/onlinedocs/gdb/Remote-Protocol.html

若要移植到已有架构的芯片上
1) arm9,11以及cortexA
	修改udef和dabt的函数,在/libcpu/arm/am335x/trap.c里,加入ifdef GDB的内容
	将libcpu/arm/am335x/start_gcc.s的相关异常向量汇编复制到自己的undef和dabt异常向量里
	分配足够的栈空间给undef

2) cortexM3以及M4
	删除已有的debugmon_handler
	优先级分组有变化的话,重定义宏GDB_CORTEXM_PRIORITY_MAX,就是basepri的设置值,满足屏蔽中断的同时不屏蔽debugmon
	使用有需要的话,重定义cortexm_stub.c的data_acess数组,也就是允许GDB访问的地址空间
	增大_system_stack_size,也就是MSP栈的大小


六 易错或者bug(出错了看这里)

编译器选项是否打开-g,是否使用GCC编译
硬件断点使用超过(max-1)个后,单步可能会出现不正常
检查串口通信是否正常,可以打开RT_GDB_DEBUG
堆栈大小是否设置合适(因为gdb要在handler模式下运行,所需要的栈大小比较大,大概0x200)
cm系列切记如果优先级分组不同于默认设置,就要重定义宏GDB_CORTEXM_PRIORITY_MAX,使抢占优先级等于1,不然单步可能会出现问题(被中断抢占)
cm系列在中断里设置断点会出现错误(目测程序还是正常工作,就是压栈的寄存器还是进入中断前的,所以返回的寄存器信息有误)
cm系列可能会因为访问不可访问的地址造成出错,有需求自己手动修改cortexm_stub.c的data_acess数组(没找到好的办法,falut后寄存器全乱了)


##
	嫌速度慢的话就把串口速度9600改成115200
	不过如此就要把注册的驱动里的getc改成阻塞的,不然会收不到
	类似
		    while(!(UART_LSR_REG(uart->base) & 0x01));
		    ch = UART_RHR_REG(uart->base) & 0xff;
	原先是
		    if (UART_LSR_REG(uart->base) & 0x01)
		    {
			ch = UART_RHR_REG(uart->base) & 0xff;
		    }
