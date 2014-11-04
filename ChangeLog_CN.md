版本: RT-Thread 2.0.0 RC

发布时间:2014/11/4

随着RT-Thread功能越来越多，如何发布版本也成为一件头疼的事情，因为需要仔细对比最近三个月来的修改记录。这次的发布距离上一次beta版本依然是三个月的时间，但按照发布计划已然推迟了一个月进行发布。 

在这三个月中，开源社区上也发生了很多有趣的事情：

阿嘉的使用RT-Thread的四轴飞行器毕业设计惊艳亮相，采用了1个STM32F4 + 8个STM32F1进行飞行控制，总计9个MCU的另类实现方式；沿循四轴飞行器的路线，与国内匿名团队合作，采用RW009 Wi-Fi控制的迷你四轴飞行器也在稳步推进过程中。

RT-Thread做为一个开源组织参与的CSDN开源夏令营结出了丰硕的果实：
由hduffddybz参与的IPv6协议栈移植（最新版本的lwIP-head版本移植）在这次发布中已经包括进来，从而能够在使用RT-Thread的小型设备上实现TCP/IP v4/v6双栈的支持；
由wzyy2参与的GDB stub实现，也完美的支持BeagleBoneBlack开发板和STM32F4平台；
CSDN开源夏令营其他的成果，例如bluedroid移植也有了初步的成果，希望能够在后续的版本（可能会是2.1.0系列版本？）包含进来。CSDN开源夏令营是一次非常棒的活动，能够让学生提前进入实战，了解软件开发的初步知识。对开源社区来说，也是一次非常有益的社区互动活动。希望明年这个活动可以继续，关注RT-Thread、嵌入式开发的同学可以关注明年的动向。

当前智能化设备是一个备受关注的领域，针对这一领域的特点，RT-Thread也相应的做出了积极的响应，所以这个版本开始加入sensor的应用框架（APP/算法 <--> sensor framework <--> RT-Thread device driver <--> 硬件外设）。希望在小型化的RT-Thread操作系统基础上融合智能化相关的技术，让RT-Thread成为这方面可选的OS系统之一。RT-Thread操作系统的sensor框架也尝试新的实现方式，即采用C++的方式来实现（当然也会考虑C方面的兼容，无疑C++的面向对象特性会更好，所以最终选择了C++），在这个基础上也可能融合其他的一些生态技术，例如ARM mbed平台上的一些社区组件技术。所以这个发布版本中既包括sensor框架，也包括了C++底层的一些基础支撑。

这个版本是RT-Thread 2.0.0系列正式版本的候选版本，正式版本预计会在年底正式发布，距离正式版本还会加入更完善的一些支撑（例如各种传感器驱动）。也计划2014年11月22日，在上海浦东举行RT-Thread嵌入式系统沙龙活动，欢迎大家关注并参与进行RT-Thread方方面面的技术交流。

以下是这个版本的更改记录:

 [内核]

* 修正当采用高级别优化编译时，idle任务中查询是否有僵尸线程的潜在bug；

* 修正memory pool中的竞争问题；

* 在console中打开设备时，加入流标志进行打开；

 [组件]

* 加入C++基础支撑组件。C++组件依赖于RT_USING_LIBC库，当使用GCC编译器时请注意查看其中的说明文档并更改ld script；

* 修正DFS中NFS打开目录的bug；

* 更改DFS ROMFS默认romfs_root为弱化符号；

* 添加DFS中dfs_file_lseek接口中关于fs的检查；

* 移除I2C core中无用的core lock锁；

* 添加sensor framework（采用C++的方式支持各种sensor）；

* 修正serial框架中DMA发送的bug（heyuanjie87）；

* 移除SPI框架中不必要的device初始化代码；

* 完善SPI Wi-Fi网卡RW009驱动并提供RSSI相关的命令；

* 修正MSH中未定义DFS_USING_WORKDIR时更改当前目录的bug；

* 修正MSH中未定义RT_LWIP_TCP时依然定义了netstat命令的bug；

* 修正MSH中未定义RT_USING_HEAP时依然定义了free命令的bug；

* 修正finsh中FINSH_USING_HISTORY相关的裁剪；

* 加入gdb stub组件，当前支持ARM Cortex-A8和Cortex-M3/4（wzyy2）；

* 统一不同编译器下使用LIBC的宏为RT_USING_LIBC，原有的宏定义RT_USING_NEWLIB/RT_USING_ARM_LIBC需要从rtconfig.h中移除，并替换成RT_USING_LIBC；

* 加入最新的lwIP分支：lwip-head，以提供IPv4/v6双栈的功能（hduffddybz）；

* YMode中打开串口设备时，添加open flag（armink）；

 [bsp]

* 加入北京京微雅格的M7（华山）低功耗FPGA的ARM Cortex-M3移植（aozima）；

* 加入北京京微雅格的M7 EMAC以太网驱动（aozima）；

* AT91SAM9260分支中更改RT_USING_NEWLIB为RT_USING_LIBC；

* BeagleBoneBlack分支中加入gdb stub支持（wzyy2）；

* LPC176x分支中加入C++支持；

* LPC176x分支中修正SD卡驱动返回卡信息的bug；

* 修正LPC408x分支中GCC编译时的问题；

* LPC408x分支中加入C++支持；

* 龙芯1B分支中加入UART3驱动；

* 加入飞索半导体的MB9BF568 FM4分支移植（yangfasheng）；

* mini2440分支中更改RT_USING_NEWLIB为 RT_USING_LIBC；

* stm32f0x分支中移除不同编译器下的LIBC定义，统一更改为RT_USING_LIBC；

* stm32f0x分支中加入串口接收溢出中断处理（armink）；

* stm32f40x分支中加入gdb stub支持并添加UART6驱动（wzzy2）；

* zynq7000分支中更改RT_USING_NEWLIB为RT_USING_LIBC；

* 加入ARM Cortex-M4芯片指令级的ffs实现；

* 修正MB0BF618S分支中缺少timer初始化的bug（mike mao）；

 [工具]

* 移除Python 2.6中未支持的语法（xfguo）；

* 移除Windows平台中的startupinfo信息（对Python版本兼容性更好）；

* 修正CPPPATH被打乱的bug；

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------

版本: RT-Thread 2.0.0 Beta

发布时间:2014/8/1

v2.0.0这个版本系列是RT-Thread当前的开发分支，如果要上新项目，建议使用这个版本来进行，预计这个版本的正式版会在年底发布。欢迎对这个版本进行测试、并反馈问题，能够早日进入到稳定版。

v2.0.0版本的开发相对活跃些，开源社区提供了强有力的支持：如Arda贡献的TM4C129x移植，Romeo贡献的frdm-k64f移植，xiaonong的LPC4300移植等，以及睿赛德服务公司捐赠的Zynq7000移植，MB9BF618S移植，以及SPI WiFi网卡的驱动代码等。

更改记录

[内核]

* 移除rt_device_init_all()函数：在系统启动时不需要再调用这个函数来初始化驱动，而是由上层应用执行rt_device_open时自动进行设备初始化；
* 修正设备对象引用计数在打开设备失败依然递增的问题；
* 增加WEAK宏用于定义/声明弱符号；
* 在执行静态内存块分配前，重置线程的errno；
* 修正timer未打开调试选项时，无用的静态函数定义（导致编译警告）；
* 启动timer前，对timer进行强制移除；
* 在执行soft timer超时函数时，打开调度器锁；
* 新增块设备的自动刷新参数，RT_DEVICE_CTRL_BLK_AUTOREFRESH；
 
[工具]

* 修正scons命令编译时，选择keil mdk (armcc)编译器时，命令行太长编译失败的问题；

[移植]

* 移除rt_device_init_all()相关的调用；
* 根据串口框架调整相关的驱动代码；
* 新增frdm-k64f移植（FreeScale K64芯片）；
* 移除K60Fxxxx移植；
* 新增LPC43xx移植（NXP LPC4357芯片）；
* 移除LPC176x中的组件初始化配置；
* 修正龙芯1B移植（ls1bdev）中链接脚本关于组件初始化部分的配置；
* 修正STM32F40x中UART3的配置；
* 修正STM32F40x中GNU GCC连接脚本中ROM/RAM大小的配置；
* 移除STM32F107中的组件初始化配置；
* 增强STM32F107 EMAC驱动性能，同时加入自动查找PHY芯片地址功能；
* 重写xplorer4330（NXP LPC4330芯片）移植（xiaonong完成）；
* 新增Zynq7000 ARM Dual Cortex-A9移植；
* 新增MB9BF618S移植；
* 新增tm4c129x移植，并加入相应的EMAC以太网驱动；

[组件]

* DFS: 新增根据设备对象获得其上装载文件系统路径的函数：dfs_filesystem_get_mounted_path(struct rt_device* device);
* DFS: 修正readdir在GNU GCC下的编译警告；
* DeviceDrivers：新增workqueue实现；
* DeviceDrivers: 修正USB Device栈中的一些拼写错误；
* DeviceDrivers: 重写serial框架，能够让串口设备驱动同时支持三种模式：poll、interrupt、DMA。模式选择需要在执行rt_device_open时，由open flags指定；
* DeviceDrivers: 加入更多的SPI设备驱动，例如RW009的SPI WiFi网口驱动（2.4G 802.11 b/g/n，WEP/WPA/WPA2，SoftAP/Station），SPI NorFlash块设备驱动，ENC28J60以太网网卡驱动；
* Finsh: list_device()命令中增加refcount的信息；
* Finsh: 修正'0'零常量无法识别的错误；
* Finsh: mv命令，实现把一个文件移动到一个目录中；
* Finsh: ifconfig命令支持对一个网络接口的基本配置；
* Finsh: 新增netstat命令，用于显示当前系统中TCP连接的状态；
* Finsh: 修正当命令行太长导致的缓冲区移除的问题；
* libc: 修正arm libc中未使用DFS时的编译警告；
* libc: 修正newlib中使用DFS时的系统调用编译警告（GNU GCC下）；
* lwIP 1.4.1: 默认打开LWIP_SO_SNDTIMEO以支持连接发送超时；
* lwIP 1.4.1: 修正MEMP_NUM_TCP_SEG定义错误的问题；
* lwIP 1.4.1: 加入RT_LWIP_REASSEMBLY_FRAG选项定义以支持IP分组及合并；
* lwIP 1.4.1: ethnet网络接口支持定义LWIP_NO_TX_THREAD/LWIP_NO_RX_THREAD，以关闭etx/erx线程；
* lwIP 1.4.1: 用户可以重新定义RT_LWIP_ETH_MTU，以修改网络中的MTU值；
* lwIP 1.4.1: 修正LWIP_NETIF_LINK_CALLBACK条件编译的问题；
* lwIP 1.4.1: 完善移植相关的注释；
* log trace: 增加log_session_lvl接口；
* log trace: log trace中的session引用更改成常量形式；
* ymodem: 增强数据接收的稳定性；

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------

版本: RT-Thread 2.0.0 Alpha
发布时间:2014/4/8
	
RT-Thread 2.0.0分支的第一个技术预览版本，仅用于展示2.0.0发展分支的演化动向(按照roadmap，2.0.0这个分支会有一部分RT-Thread和Linux互补性的技术，为Linux增加更好的实时性，为RT-Thread增加更多的功能性，这份技术预览版正是朝着这个目标而努力)，欢迎反馈建议和问题。

[组件变更]

* msh： bugfix 和功能性增强。新的 msh 在调用外部模块方面更加方便。
* DFS： nfs 的 bugfix 和内置命令的增强。ELM FatFS加入对扇区不匹配情况下的信息输出，这样能够及时定位问题。
* JS：新添了轻量级Javascript引擎，可以在RT-Thread中直接运行javascript脚本。
* VMM：可以在qemu中运行的 Virtual Machine Module 组件。暂时只支持 realview-pb-a8 的 bsp。
* CMSIS：版本更新至 3.20
* drivers：USB 协议栈的重构。新的框架中编写驱动变得更加容易了。

[BSP 变更]

* beaglebone：串口驱动更新
* realview-a8：添加了 VMM 组件

[编译脚本]

* 固件加入scons --target=ua -s，用于准备用户应用环境；

[发布后记]

RT-Thread 2.0.0. Alpha版本相比于RT-Thread 1.2.1，新的特性主要有两部分：
- RT-Thread + Linux双系统，这部分以RealView-A8处理器(ARM Cortex-A8单核)为蓝本，给出一个简单的双系统并行运行的demo；在没有硬件的环境下，可以使用QEMU软件虚拟方式的执行。这个链接中包含一个编译好的Linux及RT-Thread二进制包，可以直接下载进行体验。

目录中有 Linux 的内核镜像 zImage，ramdisk rootfs.cpio.gz。可以用
qemu-system-arm -M realview-pb-a8 -kernel zImage -initrd rootfs.cpio.gz -serial vc -serial vc
来启动。启动之后 Linux 的控制台在第一个串口上(Atl + Ctrl + 3)，可以直接无密码以 root 用户登录。登录之后加载内核模块：
insmod rtvmm.ko
来启动 RT-Thread。RT-Thread 启动之后控制台在第二个串口上(Atl + Ctrl + 4)。第一个串口Linux shell依然可以使用，第二个串口则是RT-Thread的shell。
- JavaScript解析器，这个是由牛头哥移植的，可以在一个非常小资料的MCU上以JavaScript脚本方式进行编程、开发。根据这种方式，也提供了RN001JS的以太网硬件模块：以JavaScript脚本语言作为二次开发，提供在线web(即WebIDE)进行编程并运行JavaScript程序。JavaScript作为一门轻量级、解释型的语言，更容易上手，配合WebIDE、及提供的一些example可以使得开发变得非常的轻松，也包括一些传感器的JavaScript例子，让做网页的人也可以玩硬件了！

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

版本: RT-Thread 1.2.1
发布时间: 2014/4/8
	
在原有的1.2.0版本的bug修正版本，也是1.2.0系列的第一个修正版本，原则上不添加任何的新功能，我们尽量会按照每个季度一个修订版本的方式推进。大家在使用的过程中有什么问题还请反馈给我们，这些问题很可能会在下个版本中修正！

以下是更改记录：
[内核]
* 用户应用，增加用户应用命令行参数支持；
* 在挂起一个任务时，把相应的定时器也关闭；

[BSP]
* BeagleBone，加入更多串口驱动支持；
* 移除BSP中rt_device_init_all函数调用，改成打开设备时自动进行初始化；
* LPC176x，移除components初始化管理器；
* LPC4088，修正LED驱动的问题；
* STM32F107，移除components初始化管理器；

[组件]
* 文件系统，ELM FatFS加入对扇区不匹配情况下的信息输出，这样能够及时定位问题；
* 文件系统，NFS网络文件系统修正相关的一些编译警告信息；
* 文件系统，copy命令加入文件夹方式复制功能；
* 文件系统，RAMFS，加入到components初始化管理器中；
* 文件系统，ROMFS，用于转换文件的工具mkromfs.py，增加Linux主机的支持；
* CMSIS更新到3.2.0版本；
* 串口驱动框架加入serial->ops->control的调用；
* 命令行系统，优化msh，支持用户应用的命令行参数；
* 命令行系统，当使用msh时，默认使用msh >的命令行提示符；
* TCP/IP协议栈，导出更多的lwIP接口给用户应用；
* POSIX thread，修正了同时使用lwIP组件时的编译警告；
* 第三方组件，加入TJPGD的移植，加入libpng的移植；

[编译脚本]
* 固件加入scons --target=ua -s，用于准备用户应用环境；

[发布后记]
* RT-Thread携带了众多的BSP，不一定能够一一保证每个分支上把RT-Thread上相应的功能使用起来。所以针对这种情况，我们有一款评估用的硬件开发板：RealBoard 4088，在上面力求把一些相关例程都添加上，这样在一个基本的BSP基础上，可以对照着把其他的组件、功能添加进去；
* RealBoard 4088使用的RT-Thread版本主要以RT-Thread 1.2.1版本为主。

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

版本: RT-Thread 1.2.0正式版本
发布时间: 2014/1/6 

实现roadmap中提到的大部分内容
	
1，文档方面已完成《RT-Thread编程手册》，同时还有论坛上jiezhi童鞋的《一起来学RT-Thread系列连载教程》
2，BSP分支方面新增cortext-A8(beaglebone)，cortext-R4(rm48x50)，UNITY-2(SEP6200),lpc408x的移植
3，组件方面：
- 加入msh(类似linux shell的风格)，能够直接执行应用程序
- 新增freemodbus 1.6.0的移植
- 新增开源的嵌入式关系数据库SQLite 3.8.1的移植
- 新增Ymodem协议
- 默认使用lwIP 1.4.1

下面是自RT-Thread 1.2.0 RC版本发布以来具体的变更履历：
内核：
* timer.c - 使用跳跃表(skip list)实现系统定时器链表，并在bsp中的startup.c中重新加入定时器初始化函数rt_system_timer_init()
* rtdebug.h - 新增宏定义RT_DEBUG_IN_THREAD_CONTEXT
* idle.c - 在函数rt_thread_idle_excute()中一次清除所有的死线程
* scheduler.c - 新增API rt_critical_level()返回调度器上锁次数

移植：
* cortex-m0 - 修正 cortex-m0 GCC移植中hardfault的问题点
* cortex-r4 - 在startup后释放IRQ堆栈空间
* cortex-r4 - 按字节长度分配堆栈空间

BSP分支：
* 新增lpc408x移植
* bsp/stm32f0x - 增加USART1，USART2驱动，支持finsh，支持组件初始化
* bsp/simulator - 当RTGUI配置无效时打印错误信息
* bsp/simulator - 默认情况下关闭RTGUI选项
* bsp/simulator - 增加createdef.py文件来生成VS的def文件
* bsp/simulator - 当使用VC++编译时去除_TIME_T_DEFINED的定义
* bsp/xplorer4330 - 重命名文件Retarget.c为retarget.c,否则linux系统中编译会报错
* bsp/xplorer4330 - 修正GCC编译链接时关于ENTRY的警告
* bsp/rm48x50 - 新增GCC的移植
* bsp/K60Fxxxx - 修正一个编译错误

组件：
* dfs - 正确处理mkfs未实现的情况
* dfs - 使用指针代替index变量
* dfs - 在函数dfs_filesystem_lookup()将含义模糊的指针变量名称empty重命名为fs
* dfs - 修正dfs_unmount问题点
* dfs - 在设备打开错误时令挂载失败
* dfs/elmfat - 令elmfatfs每次都检查扇区大小
* net - 新增freemodbus 1.6.0的移植
* finsh - 新增FINSH_USING_MSH_ONLY选项
* finsh - 只有当shell设备为空时调用rt_console_get_device()
* finsh - 修正FINSH_USING_SYMTAB未定义的错误
* finsh - 重构control按键的处理
* msh - 增加文件和路径名称自动补全的功能
* msh - msh内增加执行module的功能
* msh - msh内增加更多的命令
* libc - 修正 _sys_read()/_sys_write()问题点
* external - 增加开源的嵌入式关系数据库SQLite 3.8.1的移植
* pthreads - 避免ESHUTDOWN重复定义
* mtd_nand - 在MTD nand中增加更多的调试措施
* mtd_nand - 修正操作MTD nand时起始块错误的问题
* lwip-1.4.1 - 在lwIP内加入更多的RT-Thread选项设置
* log_trace - 修正函数memmove()参数使用错误的问题
* drivers/pipe - 增加一个control命令来获得pipe剩余的空间
* drivers/serial - 如果读写长度为0，则立即返回

例程：
* examples - 用rt_sem_control()中的RT_IPC_CMD_RESET命令rt_sem_trytake()来清除信号量
* examples - 始终打印输出测试结果
* examples - 在所有的测试结束后打印输出简报
* examples - 在TC线程中清除变量_tc_stat的TC_STAT_RUNNING状态
* examples - 重新实现loop功能，并新增finsh命令tc_loop
* examples - 在tc_stop中增加延时，由原来的延时RT_TICK_PER_SECOND/2调整为10 * RT_TICK_PER_SECOND
* examples - 在SConscript中判断TC如果被使能，在CPPPATH中增加TC路径
* examples - 新增一个in-mem-log的例子
* semaphore_priority.c - 在cleanup时释放信号量
* heap_realloc.c - 检查调用realloc(ptr, 0)是否成功
* thread_delete.c - tc线程的延时应该比tid2的延时长，保证其测试过程中正常运行
* thread_delay.c - 放宽超时判断条件，因为当RT_TICK_PER_SECOND为1000时，容易产生1个tick的误差
* semaphore_static.c - 放宽超时判断条件，因为当RT_TICK_PER_SECOND为1000时，容易产生1个tick的误差
* semaphore_dynamic.c - 放宽超时判断条件，因为当RT_TICK_PER_SECOND为1000时，容易产生1个tick的误差

其他：
* 更新README.md
	
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
	
版本: RT-Thread 1.2.0RC	
发布时间: 2013/10/10/ 10:19
	 
主要说明: 该版本新增ARM Cortex-A8的支持(BeagleBone)，新增UNITY-2内核的支持(SEP6200)，新增Ymodem协议。

变更履历
========

[内核]

* 修正rtdef.h中的拼写错误(_MSC_VER_ -> _MSC_VER)
* 修正scheduler.c中的调试打印输出错误
* ipc - 在函数rt_event_recv()中增加对参数option有效性的检查
* device - 增加统计设备引用次数的变量ref_count
* memheap - 修正内存块分割问题点
* memheap - 优化函数rt_memheap_realloc()
* kservice - 函数声明使用rt_vsnprintf代替vsnprintf


[组件]

* dfs - 修正dfs_file.c中一处变量参数类型错误的问题
* dfs - 增加mount table
* dfs - 在building脚本中加入ramfs的支持
* dfs - 修正ramfs中O_APPEND write的问题
* dfs/elm - 在mkfs中加入device_open/close
* dfs/jffs2 - 修正jffs2_opn/opendir中的f_flag初始化问题
* dfs/jffs2 - 修正jffs2卸载问题
* pthread - 修正一处编译警告
* drivers/pipe - 增加rt_pipe_init/rt_pipe_detach
* drivers/pipe - 增加非阻塞读写和强制写模式
* drivers/pipe - 当恢复读的时候调用函数rx_indicate()
* drivers/pipe - 增加一个设备类型(pipe类型)
* drivers/portal - 实现portal设备类型
* drivers/ringbuffer - 修改一些模糊不清的函数名称
* drivers/ringbuffer - 新增put_force和putchar_force接口函数
* finsh - 当set_device时增加设备检查
* finsh - 在rx_ind中增加对shell设备的自动设置
* finsh - 增加pipe和portal设备的描述
* finsh - 在变量定义时使用别名
* finsh - 当关闭设备时注销rx_indicate
* finsh - 修正命令行太长的问题
* finsh/msh - 只有当DFS_USING_WORKDIR使能时才声明cd/pwd
* init - 为新的组件初始化机制更新连接脚本
* init - 增加组件初始化调试代码
* logtrace - 整理代码，去除编译警告
* logtrace - 增加LOG_TRACE_VERBOSE
* logtrace - 调整log values
* logtrace - 只有当finsh使能的时候才声明cmd
* libc/minilibc - 在sys/time.h中增加gettimeofday的声明
* utilities - 新增ymodem

工具:

* building.py - 增加clang静态缝隙器的支持
* building.py - 为Keil MDK增加buildlib功能
* building.py - 在clang-analyze中执行'clang -Wall -fsyntas-only'
* clang-analyze.py - 增加一个定制工具实现clang静态分析

分支:

* 新增BeagleBone的移植
* 新增SEP6200的移植
* 新增K60Fxxxx的移植
* 修正Linux中的编译错误(lm4f232, stm32f40x, xplorer4330)
* cortex-m3 - 加强hard fault的异常处理函数
* at91sam9260 - 更新串口驱动，使用组件中的通用串口驱动
* at91sam9260 - 更新工程目录结构
* at91sam9260 - 修正编译错误
* at91sam9260 - 内嵌GPLv2许可
* stm32f10x - 删除无用的文件
* stm32f10x - 更新工程目录结构
* stm32f10x - 更新工程文件
* stm32f10x - 为使用新的组件初始化更新连接脚本
* stm32f10x - 为使用新的组件初始化更新SD card驱动
* stm32f10x - 为使用新的组件初始化更新DM9000驱动
* stm32f10x - 更新串口驱动，使用组件中的通用串口驱动
* stm32f10x - 修正rtgui初始化问题
* simulator - 为使用新的组件初始化更新代码，以便支持mingw
* simulator - 支持Linux系统
* simulator - 修正Linux系统中的SDL初始化问题
* simulator - 在rt_components_init之后初始化SDL
* simulator - 将对SDL设置的内容移入drivers/SConstruct
* simulator - 在env中获得CORSS_TOOL和EXEC_PATH的值
* simulator - 支持clang-analyze
* simulator - 增加tap netif driver

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------


版本: RT-Thread 1.2.0 Beta 版本

发布时间: 2013/6/30
		
进过开发人员三个月的努力，RT-Thread 1.2.0 Beta 版本如期发布。
该版本默认采用lwIP 1.4.1协议栈，USB device stack也进一步完善。加入 log_trace 子系统，加入组件初始化升级版本，加入 ARM Cortex-R 的移植。

主要变化：

* 1，新增组件初始化功能
- 详情请看论坛帖子[新功能] 组件初始化
* 2，支持ARM Cortex-R系列处理器
- Grissiom 完成 ARM Cortex-R 的移植，目前BSP中已有TI RM48x50分支（仅支持TI CCS开发环境）
* 3，文件系统中新增 RAMFS
* 4，加入 log_trace 子系统
* 5，优化Cortex-M4线程上下文切换，使用了浮点运算的线程才保存及恢复FPU寄存器
- 详情请看论坛帖子[优化]cortex-m4f线程切换，优化FPU寄存器
* 6，新增API rt_memheap_realloc()
* 7，重新实现ringbuffer，采用镜像的方法区分“满”和“空”，同时支持任意大小的buffer
* 8，内核中加入RT_KERNEL_MALLOC/RT_KERNEL_FREE/RT_KERNEL_REALLOC宏。
如果用户未定义这些宏，将默认指向rt_malloc/rt_free/rt_realloc。
同时内核仅局限于使用这些宏来使用动态内存
* 9，在 building.py 中新增生成 cscope database 的选项
* 10，USB组件新增reset函数，支持热插拔
* 11，scons编译系统支持CCS开发环境
* 12，USB组件新增状态信息（USB_STATE_NOTATTACHED，USB_STATE_ATTACHED，USB_STATE_POWERED...）

修复问题点：

* 1，USB组件HOST可以挂起endpoints
* 2，simulator分支，修复 serial_write 问题
* 3，udisk可以被弹出
* 4，iar.py中修复绝对路径的问题
* 5，dfs_fs.h内增加dfs_mkfs()函数的申明
* 6，生成MDK工程文件的时候加入library文件
* 7，当PC不再接受数据的时候，重置VCOM相应的状态
* 8，USB组件：返回正确的LangID字符串长度给HOST
* 9，Cortex-M0，Cortex-M3，Cortex-M4上下文切换时，回收系统初始化时用到的栈空间

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------



版本: RT-Thread 1.2.0 Alpha版本

发布时间: 2013/4/10
	
遵循2013年RT-Thread roadmap，RT-Thread 1.2.0 Alpha版本发布，Alpha意味着此版本为技术预览版，仅用于展示RT-Thread 1.2.0未来的发展方向，并不适合于开发正式产品。RT-Thread 1.2.0版本是1.1.x系列的下一个分支，这个分支主要体现的是RT-Thread 1.x系列的文档情况。当然也有一些功能、代码方面的增强。

伴随着新版本的到来，RT-Thread有几个重大的转变：
1，代码托管从google code(SVN)迁移到github(GIT)
2，RT-Thread与RTGUI区分开来，并成为两个独立的开发分支
3，重视文档，将文档建设作为1.2.0版本的首要任务来抓

内核主要变化：
1，加入__rt_ffs函数用于实现32位整数中获取第一个置1的位；同时调度器中位图相关算法直接使用__rt_ffs函数；CPU移植时，可定义RT_USING_CPU_FFS，使用芯片指令完成。

2，新的中断注册机制
weety加入interrupt description功能，用于为interrupt增加更多的信息，同时中断服务例程也可以携带用户自定义的参数类型。
* 这部分对ARM7、ARM9、MIPS等影响很大，需要对CPU移植做相应的一些修改。
* 这部分对ARM Cortex-M系列芯片没有影响。

3，调整定时器插入位置，为相同超时定时的后面。

组件主要变化：
1，添加lwIP 1.4.1。
2，在finsh shell中加入module shell功能。finsh shell本身是一个C语言表达式的shell命令行，而module shell更类似于一个传统的命令行，由命令，参数等方式构成。

分支主要变化：
1，完善simulator分支，支持RTGUI，支持应用模块。
2，完善at91sam9260分支的移植及驱动更新。

编译系统主要变化：
1，开启省略编译时长命令特性，如果需要查看编译时命令行，可以使用scons --verbose查看。
2，加入生成CodeBlocks工程特性。
3，修正当系统安装使用Keil MDK 4.6+版本的问题。

github主要提交履历:
5646189b29: elm fatfs支持mkfs，并且无需提前执行dfs_mount; mount/umount/mkfs操作也不会引起reset
22786f8817: 允许用户自定义PID和VID
0001344105: 更明确的定时器运行机制，如果两个定时器在同一个时刻发生超时，那么先开始的定时器先处理
5d68ef8ec1: 修正使用64位GCC时编译finsh过程中发生错误的问题
a4d661dcf1: 修正dfs_elm.c中一处内存泄露，并且在mount fatfs失败时执行 umount fatfs操作
43228aeb9c: 修正list_tcps问题：ipaddr_ntoa不是可重入的函数。
3de4b92a68: 修正AT91SAM9260分支中PHY link状态错误的问题。
1abaa0492d: 在kservice.c中增加__rt_ffs的实现。
ec6f9e3b5a: 修正在dfs.c中一处空指正的问题。
92d4c1939b: 修正at91sam9260分支上下文切换问题点，避免idle任务堆栈溢出。
fb9ea5eada: 在at91sam9260分支中使能MMU，并且更新SDIO和EMAC驱动。
009eccf640: 修正函数list()中错误使用strncpy的问题点。
83751c63e3: 在dlopen.c中增加出错处理。	
	
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
版本: RT-Thread 1.1.1稳定版本
发布时间: 2013/6/30

这个版本是一个基于RT-Thread 1.1.0正式版的bug修正版，相比于1.1.0版本，基本上没有添加什么新的功能，以下是修改记录：
内核：
* 修正timer激活时，插入队列顺序的问题；
* 内核中加入RT_KERNEL_MALLOC/RT_KERNEL_FREE/RT_KERNEL_REALLOC宏。如果用户未定义这些宏，将默认指向rt_malloc/rt_free/rt_realloc。同时内核仅局限于使用这些宏来使用动态内存；
* 加入Miscellaneous Device类型设备；
* 当未定义RT_USING_CONSOLE时，将把rt_kprintf置空以节省字符串占用空间；
* memheap对象加入rt_memheap_realloc函数接口；
* rt_exit_critical函数可以在调度器未启动时使用；
* keil工程文件生成中支持加入库文件；

组件：
* 修正lwIP 1.4.0中ipv4/ip.c中IP_ACCEPT_LINK_LAYER_ADDRESSED_PORT宏定义错误的问题；
* 加入RAMFS，内存文件系统；
* 统一working目录特性不支持的字符串位置；
* DFS中加入内存分配失败的保护；
* DFS中df输出更多有意义的信息；

分支：
* lm3s8962/lm3s9b9x 增加EMAC驱动在接收时，如果内存不够，（丢弃数据包）并重新打开EMAC中断；

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

版本: RT-Thread 1.1.0 正式版发布
发布时间: 2012/12/31
	
2012年玛雅人预言的世界末日没有到来，但是我们的 RT-Thread 1.1.0 正式版却如约而至。

看看 1.1.0 突出的更改及改进情况，首先 1.1.0 版本是 1.0.x 系列的一个升级版本，并未包括实质性、大的改动，改动主要体现在：
内核：强化应用模块。通过 1.1.0 开发时主要使用的平台：ART、realtouch-stm32f4，对应用模块进行相应的修正，并真正的在 Cortex-M 系列上使用起来。

驱动框架：这部分是 1.1.0 分支所主要新增的部分，包括：
=>USB device/host stack;
=>SDIO 框架（支持 SDIO 设备、SD/MMC 设备）
=>SPI BUS，IIC device；
=>WDT、RTC 等设备；
=>MTD NOR 及 Nand 设备；

文件系统部分也有显著的更改：由 prife 移植了 JFFS2、UFFS 以及 YAFFS2。这部分已经比国外的 ecos、RTEMS 支持更广泛。
YiHui 加入并验证了 LUA 脚本的功能。
prife 新增了全面的 Windows Simulator 的分支，并把内核，shell，各个文件系统，TCP/IP 以及 GUI 组件都运行通过。
现在虽然已经出了 1.1.0 RC 版本，但在 1.1.0 正式版出来前，还会新加一个功能：scons 前端工具。
这个增加的是工具部分，对 RT-Thread 代码的修改尽量少，它主要通过使用图形界面的方式来动态生成 RT-Thread 的各个工程文件，当然也包括编译功能。目的是方便于（新）用户使用，而不是直接面对命令行（命令行模式还会保留，以方便例如 RT-Thread 开发人员这样的尽情进行 Hacking）。
以上摘录自《写在 RT-Thread 1.1.0 发布之前》

新版的 RTGUI 仍需要完善，此次 1.1.0 正式版本中暂不包括，之后会有单独的 RTGUI 版本发布。
想获取更多 RTGUI 信息的同学，请关注 https://github.com/RT-Thread/RTGUI

以下是自 RT-Thread 1.1.0 RC 版本发布后，详细的更新内容：
内核：
=====
- 在设备注册时增加设备检查步骤
- 在 kservice.c 中修正一处未定义 compiler 时的编译错误
- 在 memheap.c 中增加对 heap object 的互斥操作
- 重新定义宏 RT_NULL 由 ((void*)0) 变更为 0
- 在 module.c 中使用 RT_DEBUG_LOG 代替 rt_kprintf
- 应用模块中删除 rt_current_module
- 应用模块中用户可以使用 rt_module_unload() 来卸载一个模块
- 修正函数 clock_time_system_init() 中对变量 _timevalue.tv_usec 初始化错误的问题点
- 软件定时器中修正 next timeout 处理错误的问题点
- 函数 rt_kprintf() 中修正一处由 Grissiom 发现的 BUG
- 修正函数 rt_components_init() 中对 pthread 初始化问题点
- device.c 中，如果设备不存在则返回 RT_EOK

文件系统：
=========
- 完善 jffs2 移植，支持 GCC 编译器（使用 NEWLIB）
- 修正函数 dfs_unmount() 中存在的一处 BUG
- 修正函数 dfs_uffs_seek() 中存在的一处 BUG
- 修正 DFS 中 O_APPEND 和 lseek 问题点
- 在 DFS 中增加对 dfs_fd 的合法性检查
- 修正 uffs 中未初始化所有设备操作函数
- 更新 uffs，支持 MTD 接口
- 增加 DFS_NFS_MAX_MTU 选项，修复读写 NFS 时包长度超过1个 mtu 长度的 bug
- 修复 NFS 中 seek 的一处 BUG
- 修复向 NFS server 上创建文件/目录时路径和权限的 BUG

组件：
=====
- 加入 LUA 脚本的功能
- finsh 组件中完善对 win32 移植分支的支持
- 完善 USB device stack
- RTC 驱动框架中新增对 RTC alarm 的支持
- 串口驱动框架中增加对 DMA 传输的支持
- LwIP 组件中增加对 MSC 编译器的支持
- LwIP 组件中增加 RT_LWIP_ALIGN_SIZE 设置
- 网络接口可以再 LwIP 初始化以后再进行初始化
- minilibc 中增加更多的 errno
- newlib 中完善模块加载后的退出功能
- 新增 RT_USING_MEMHEAP_AS_HEAP 功能，可以使用 memheap 作为系统默认的 memory heap

工具：
=====
- 在 building.py 中支持自动生成 Visual Studio 工程
- 新增 SConsUI 图形界面工具

分支：
=====
- 新增 PPC405 分支
- 新增 NXP LPC4330 分支

- 新增 win32 的 simulator 分支
--完善对编译环境 Visual Studio 2005 及以上版本的支持
--支持 finsh
--支持 LWIP
--支持 jffs2，elm fatfs，uffs

- mini2440 分支
-- 支持 SDHC

- efm32 分支
--修正 ubuntu 下 GCC 编译的错误

- sam7x 分支
--修正使用Lwip后，编译错误的问题

以下是此次版本发布时的测试环境：
windows 7
ubuntu 10.04 LTS 64-bit
python 2.7.3
scons 2.1.0
IAR 6.30
MDK 4.53
arm-2011.09-69-arm-none-eabi.exe
mips-2011.09-86-mips-sde-elf.exe
以下是 google code SVN 中自 RT-Thread 1.0.0 发布后的统计数据，感谢各位同学做出的努力，使得 RT-Thread 1.1.0 正式版顺利发布	

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread 1.1.0 RC
发布时间: 2012/10/12
	
原计划在2012年9月30日发布的 RT-Thread 1.1.0 Beta2 版本变更为 RT-Thread 1.1.0 RC 现在发布了。
RC 版本的发布意味着离 RT-Thread 1.1.0 正式版的发布已经不远了，在RC版本之后，将不再有新功能加入。欢迎大家测试，让我们一起迎接 RT-Thread 1.1.0 正式版的到来。

此次发布主要是加入了 USB device stack；RTGUI 组件与 github 上的 RTGUI 开发分支保持同步；

以下是详细的更新内容：
内核：
=====
- 删除 rtm.c 文件
- 修正 timer control 中 timer 标志设置错误的问题点
- rtdef.h 中新增对 Microsoft Visual C++ 编译器的检查
- 新增设备控制命令 RT_DEVICE_CTRL_BLK_SYNC
- 新增图形设备控制命令 RTGRAPHIC_CTRL_FILL_RECT 和 RTGRAPHIC_CTRL_DRAW_RECT
- 将模块的线程优先级从原来的 RT_THREAD_PRIORITY_MAX - 1 变为 RT_THREAD_PRIORITY_MAX - 2
- module 中修正 section 拷贝问题点
- module 中修正 模块删除失败的问题

文件系统：
=========
- 修正 elm fatfs 中 f_seekdir 存在的问题
- dfs_elm.c 中新增接口 ff_memalloc() 和 ff_memfree()
- 修正 dfs_elm.c 中函数 dfs_elm_open() 存在的内存泄露的问题
- 修正 dfs_elm.c 中函数 dfs_elm_mount() 存在的未初始化的问题
- 在函数 disk_ioctl() 中增加对 CTRL_SYNC 的处理
- 新增 RT_DFS_ELM_CODE_PAGE 选项
- DFS POSIX 中增加 O_BINARY 标志
- 修正 ff.c 中函数 mem_cpy() 增加对字节未对齐的处理

组件：
=====
- 新增 USB device stack
- components_init.c 重命名为 componets.c
- components_init.h 重命名为 componets.h
- 串口驱动框架中增加默认的 configuration
- 修正 serial.c 中函数rt_serial_control() 一处变量未初始化的问题
- 删除函数 rt_ringbuffer_get_datasize()
- 新增 pipe 读，写，创建，销毁 API
- 新增 data queue 的实现
- 修正 ring buffer 越界问题点
- 修正函数 rt_spi_release_bus() 中断言判断错误的问题点
- rtc.c 中 time() 函数增加 open 操作
- MTD NAND 中新增 move_page 接口，添加mtd_nand成员oob_free，更改成员block_size为pages_per_block
- LWIP 中新增连接失败后关闭 sock 的操作
- USB stack 中新增 ADK 协议的实现
- LWIP 中函数 eth_device_init() 中当定义 LWIP_DHCP 时，设置 NETIF_FLAG_DHCP 标志；当定义 LWIP_IGMP 时，设置 NETIF_FLAG_IGMP 标志
- minilibc 中新增接口 isspace() 和 atol()
- 删除了重复定义的 rt_list_entry

工具：
=====
- 在 building.py 中新增 MakeCopy(), GlobSubDir() 和 GetConfigValue() 函数
- 新增 wizard.py - 自动生成 SConscript 的脚本
- 增加 --copy-header 选项，拷贝 RT-Thread 头文件到本地
- 修正 win32 系统中 GNU GCC 路径设置错误的问题点
- 增加 remove_components 功能

分支：
=====
- m16c62p 分支
--修正任务堆栈初始化时未设置任务返回地址的问题

- upd70f3454 分支
--修正任务堆栈初始化时未设置任务返回地址的问题
--整理 BSP 目录结构，统一划分为 application 和 drivers 目录
--支持 scons + IAR 编译
--增加 IAR 工程模版

- stm32f0x
--libcpu 移植代码中增加 r8 - r11 出栈，入栈操作

- mini2440
--使用新的 RTGUI

以下是此次版本发布时的测试环境：
windows 7
ubuntu 10.04 LTS 64-bit
python 2.7.3
scons 2.1.0
IAR 6.30
MDK 4.53
arm-2011.09-69-arm-none-eabi.exe
mips-2011.09-86-mips-sde-elf.exe

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread 1.1.0 Beta1
发布时间: 2012/6/30	
按照 2012 年 RT-Thread roadmap，经过各位同学的努力，RT-Thread 1.1.0 Beta1 版本按时发布了，此版本依然是技术预览版，展示 RT-Thread 未来的发展方向，但不适合用于产品开发。
该版本主要是全面更新了 RTGUI 组件；加入了新的驱动框架（usb host, i2c，serial, rtc）；组件中新增官方的 CMSIS 库；新增 Blackfin BF533 的移植，成为 RT-Thread 支持的第一个 DSP 分支。

同时恭喜 prife 同学成为 RT-Thread DFS 虚拟文件系统组建维护人

以下是详细的更新内容：
内核：
=====
- 新增3个API：rt_timer_next_timeout_tick(), rt_timer_check(), rt_system_module_init()
- 修正 module 卸载的问题
- 删除函数 rt_soft_timer_tick_increase()
- rt_object_is_systemobject() 返回类型变更为 rt_bool_t

文件系统：
=========
- 修正 fd 引用越界判断错误的问题
- posix API 中，错误返回时设置正确的 errno

组件：
=========
- 新增标准的 CMSIS 库，可供 ARM CORTEX 各分支使用，实现统一
- 新增设备驱动框架（USB host，I2C，RTC，serial）
- 新增设备驱动的 IPC
- finsh 中新增 list_memheap 命令
- finsh 中增加自动补全的功能
- finsh 中增加行注释功能
- finsh 中修正了由 Grissiom 发现的 finsh_var_delete() 中的问题
- 组件初始化中增加 RTGUI 系统服务初始化函数 rtgui_system_server_init()
- minilibc 中解决了未定义 RT_USING_DEVICE 时，GCC 编译出错的问题
- newlib 中解决了未定义 RT_USING_DEVICE 时，GCC 编译出错的问题
- RTGUI 组件全面更新，与 RT-Thread 1.0.x 中的 RTGUI 不兼容

分支：
=====
- 支持 Blackfin DSP 的移植，新增加 BF533 分支
- 新增加 stm32f0x 分支

- at91sam9260 分支
--新增 i2c 驱动

- efm32 分支
--新增 emu 驱动
--更新 CMSIS 版本到 3.01

- lpc176x 分支
--rtconfig.h 中增加 CMSIS 选择项，选择使用 BSP 内的 CMSIS 或者是 RTT 组件中的 CMSIS
--更新 IAR 工程模版
--修正 IAR 工程使用的 link 文件内容

- lpc178x 分支
--修正 GCC 编译错误的问题
--配合 RTGUI 的更新，在 application.c 中作相应的调整

- ls1bdev
--规范移植分支目录结构，分为 applications 和 drivers 两个目录
--调整 rtconfig.h，支持 eclipse 的可视化配置

- m16c62p 分支
--规范移植分支目录结构，分为 applications 和 drivers 两个目录
--增加 IAR 工程模版

- mb9bf500r 分支
--配合 RTGUI 的更新，在 application.c 中作相应的调整

- mb9bf506r 分支
--rtconfig.h 中增加 CMSIS 选择项，选择使用 BSP 内的 CMSIS 或者是 RTT 组件中的 CMSIS
--规范移植分支目录结构，分为 applications 和 drivers 两个目录

- mini2440 分支
--更新 keil project
--修正 mini2440 移植中，上下文切换时的 bug，由 yuxun2k 提交补丁
--配合 RTGUI 的更新，在 application.c 中作相应的调整
--配合 RTGUI 的更新，在 calibration.c 中作相应的调整

- mini4020 分支
--规范移植分支目录结构，分为 applications 和 drivers 两个目录

- sam7x 分支
--规范移植分支目录结构，分为 applications 和 drivers 两个目录

- stm32f10x 分支
--rtconfig.h 中增加 CMSIS 选择项，选择使用 BSP 内的 CMSIS 或者是 RTT 组件中的 CMSIS
--配合 RTGUI 的更新，在 application.c 中作相应的调整
--增加 IAR 工程模板

- stm32f20x 分支
--规范移植分支目录结构，分为 applications 和 drivers 两个目录

- stm32f107 分支
--rtconfig.h 中增加 CMSIS 选择项，选择使用 BSP 内的 CMSIS 或者是 RTT 组件中的 CMSIS

以下是此次版本发布时的测试环境：
windows 7
python 2.7.3
scons 2.1.0
IAR 6.30
MDK 4.53
arm-2011.09-69-arm-none-eabi.exe
mips-2011.09-86-mips-sde-elf.exe	
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread 1.1.0 Alpha
发布时间:　2012/4/16
	
按照 2012 年 RT-Thread roadmap，RT-Thread 1.1.0 Alpha 版本发布，此版本为技术预览版，展示 RT-Thread 未来的发展方向，但不适合用于产品开发，此版本主要是新增了组件初始化模块，加入了新的驱动框架（SPI，SDIO），新增 jffs2，yaffs2 文件系统的移植，eclipse 可视化配置 rtconfig.h 选项，具体的更新内容如下：
内核：
=====
- 完成components init模块，通过 API rt_componets_init(void)，统一组建初始化流程，参考 lpc176x
- src/kservice.h 移动并重命名为 include/rtservice.h
- 新增rt_malloc_align/rt_free_align接口用于分配、释放对齐的内存
- 打开kservice.c中的RT_PRINTF_PRECISION宏以支持rt_kprintf中的带精度格式输出
- 新增 memheap用于在额外连续内存块上构建一个内存堆，提供新API rt_memheap_init()，rt_memheap_detach()，rt_memheap_alloc()，rt_memheap_free()
- 修正函数 rt_mp_init() 和 rt_mp_create() 中内存对齐的问题
- finsh/cmd.c 中删除函数 rt_list_isempty()，统一使用 rtservice.h
- 修正动态加载模块 module.c 中 module unload 问题
- 新增宏 RTTHREAD_VERSION，版本1.1.0的格式是10100
- minilibc/stdint.h 中，新增 int64_t 和 uint64_t
- 1.1.0 版本后弃用函数 rt_system_tick_init()
- 新增 buildbot 模块，实现批量编译 scons 工程

- 新的 DeviceDriver 框架：
* SPI BUS及SPI Device
* SD卡及面向非存储类型的SDIO卡
* MTD Nand设备及MTD NorFlash设备

文件系统：
=========
- 新增 jffs2 文件系统移植
- 新增 yaffs2 文件系统移植
- 更新 uffs 到最新版本，并使用MTD Nand设备接口
- 修正 tid->error 被无故修改的问题

网络组件：
=========
- lwip 默认使用 v1.4.0 替换原来的 v1.3.2

分支：
=====
- 支持 FPGA 软核的移植，新增加 microblaze 分支，nois-ii 分支
- 新增加 pic32ethernet 分支

- at91sam9260 分支
--更新网络驱动，新增 sido 驱动

- efm32 分支
--新增 key 和 joystick 驱动，更新 usart 驱动

- lm3s8962 分支
--更新 ethernet 驱动，Enable reception of multicast packets

- m16c62p 分支
--支持 SCONS/GCC 编译

- fujistu fm3 分支
--拆分 fm3 分支为 mb9bf506r 和 mb9bf500r 两个独立的分支

- stm32f40 分支
--更新 usart 驱动，更新 STM32F4xx_StdPeriph_Driver 到版本 V1.1.0

- mini2440 分支
--新增 keil project

- x86 分支
--支持 SCONS/GCC 编译

- lpc178x 分支
--新增 LCD 驱动，增加 SDRAM 初始化

- lpc176x 分支
--树立 RT-Thread 1.1.0 BSP 示范分支
--提供全套编译方案(KEIL 工程，IAR 工程，SCONS/GCC，SCONS/KEIL，SCONS/IAR)
--提供 IAR 工程模板和 KEIL 工程模板，可以通过 scons --target=iar -s 自动生成 IAR 工程
--重新定义 rtconfig.h 文件结构，实现 eclipse 中可视化配置 rtconfig.h 选项
--调整 BPS 目录结构，应用相关归入 applications 目录，驱动相关归入 drivers 目录，库相关归入 CMSIS 目录


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
	
版本: RT-Thread 1.0.4 
发布时间: 2012/12/30
	
RT-Thread 1.0.4 是 1.0.0 版本的 bug 修正版,也是 1.0.0 系列的最终版本。
RT-Thread 1.0.x 自正式版本发布到现在已经维护了一年整时间，期间发布了 4 个修订版本，目前已经趋于成熟、稳定，完全满足商用需求。
后续的重点我们会转移到 RT-Thread 1.1.0 版本的维护以及 RT-Thread 1.2.0 版本的开发。

1.0.4 版本仅在原来的基础上对已有的功能进行修正（新功能基本上没有），相对于 1.0.3 版本的更改如下：

1，修正 DFS 中 O_APPEND 和 lseek 问题点
2，在设备注册时增加设备检查步骤
3，finsh shell 中支持行注释
4，修正函数 clock_time_system_init() 中对变量 _timevalue.tv_usec 初始化错误的问题点
5，在函数 fd_get() 中增加对 dfs_fd 的合法性检查
6，删除 rtthread.h 中 rt_sprintf() 函数的重复声明	
	
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread 1.0.3
发布时间: 2012/10/12
		
RT-Thread 1.0.3 是 1.0.0 版本的 bug 修正版，仅在原来的基础上对已有的功能进行修正（新功能基本上没有）。
1.0.3 版本相对于 1.0.2 版本的更改：

1，lm4f232 分支更新 rtconfig.ph
2，修正 timer control 中 timer 标志设置错误的问题点
3，修正模块组件卸载问题点
4，修正当 multi-drivers 使能后 dfs_elm_open()调用失败后存在的一处内存泄露问题点
5，在 ELM FatFs 文件系统中增加 mount 检查
6，修正 f_seekdir 中存在的问题点
7，修正 finsh_var_delete 中的问题点
8，修正 LPC178x 分支中 scons 配合 armcc 编译时发生错误的问题点
9，修正 LPC176x 分支中 scons 配合 gcc 编译时发生错误的问题点
10，LWIP 中函数 eth_device_init() 中当定义 LWIP_IGMP 时，设置 NETIF_FLAG_IGMP 标志

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread 1.0.2
发布时间: 2012/6/30		
RT-Thread 1.0.2 是 1.0.0 版本的 bug 修正版，仅在原来的基础上对已有的功能进行修正（新功能基本上没有）。
1.0.2 版本相对于 1.0.1 版本的更改：

1，DFS 组件中，修正 fd 引用越界判断错误的问题
2，DFS posix API 中，错误返回时设置正确的 errno
3，LWIP 组件中，发送 mail 到 TCP 线程，用 rt_mb_send_wait() 代替 rt_mb_send()
4，在 rtthread.h 中新增两个 API：rt_timer_check(), rt_timer_next_timeout_tick()	

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread 1.0.1
发布时间: 2012/4/16
	
RT-Thread 1.0.1是1.0.0版本的bug修正版，仅在原来的基础上对已有的功能进行修正（新功能基本上没有）。1.0.1版本相对于1.0.0版本的更改：
内核
- 修正rt_sem_control/rt_event_control/rt_mb_control/rt_mq_control中可能引起的任务未及时调度的问题；
- 修正rt_memmove函数的问题；
- 增加rt_malloc_align/rt_free_align的接口用于地址对齐方式的分配和释放；（使用rt_malloc_align分配的内存块必须使用rt_free_align接口释放）
- 修正memory pool中内存块地址对齐的问题；
- 修正应用模块卸载的问题；

文件系统
- 修正umount时内存泄漏的问题；
- 修正文件系统中errno赋值的问题；

shell
- 修正finsh_sysvar_append添加变量的问题；

libc
- minilibc
* 增加int64_t/uint64_t类型定义；
- newlib
* 分离newlib与DFS的关联；
* 修正使能lwip时，timeval结构体定义将使用newlib提供的类型；

分支
- Cortex-M4
* 修正使能FPU时任务切换的问题；
- MB9BF506
* 修正SysTick时钟中断函数名错误的问题；

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread 1.0.0正式版
发布时间: 2011/12/31	

RT-Thread从2006年诞生到现在已经5年了，历经多次版本更迭（0.2.x，0.3.0，0.3.3，0.4.0 beta1，0.4.0 beta2，0.4.0 RC1）
内核更稳定：
增强上下文检查的功能，更多的错误检查

组件更丰富：
有文件系统，有RTGUI，支持TCP/IP协议栈，支持动态模块加载，支持posix，在使用GCC时可以打开newlib选项，支持全套C标准运行库

分支移植更完善：
支持ARM7，ARM9，ARM Cortex-M3，ARM Cortex-M4，MIPS，AVR32，V850E等32位MCU，同时也支持瑞萨的16位MCU M16C系列

所以我们很高兴可以发布RT-Thread 1.0.0版本了，此次正式版的发布离不开各位同学的支持，
感谢李恒发起的线下网友聚会
感谢上海浦东软件平台公司提供主题沙龙场地
感谢grissiom翻译的coding style文档,及提交的RTGUI相关补丁
感谢onelife维护EFM32分支
感谢。。。

与RT-Thread 0.4.0 RC1比起来，RT-Thread 1.0.0主要有以下的更新内容：

内核：
=====
- 强制newlib组件配合GCC使用，否则将在编译时提示错误
- 修正object名字复制问题
- 新增RT-Thread I/O error code(RT_EIO)
- 新增三个设备类型（RT_Device_Class_SPIBUS, RT_Device_Class_SPIDevice, RT_Device_Class_SDIO）
- building.py
---- 新增SrcRemove函数
---- 新增MergeGroup函数
---- 修正源文件含有中文名的问题点
- 增加coding style说明文档

组件：
=====
- DFS
---- 修正elmfs移植中statfs问题
---- 修正dfs_elm.c中rename问题
---- 修正dfs_file.c中rename问题
---- 修正lseek下溢问题
-LWIP
---- 更新finsh命令（list_if,set_if），支持multple interface
-RTGUI
---- 定义宏RTGUI_NOTEBOOK_TAB_WIDTH代替原先使用的魔数
---- 修正ack_mb在错误发生时没有detach的问题
---- 修正RTGUI_USING_MOUSE_CURSOR选项打开时，编译出错问题
---- 优化notebook代码结构，提高_rt_notebook_ondraw()执行效率
---- 优化notebook.c中mouse事件处理
- 修正zmordem一处语法错误

例程：
=====
---- RTGUI例程中增加notebook的demo
---- 新增mem_test例程
---- 更新kernel测试例程

分支：
=====
ARM Cortex-M3系列芯片的移植统一使用/libcpu/cortex-m3
ARM Cortex-M4系列芯片的移植统一使用/libcpu/cortex-m4

- 新增stm32f40x分支
- 新增lm4f232分支
- 完善m16c
---- 在汇编中正确使用BYTE操作指令操作rt_thread_switch_interrupt_flag变量
---- 修正scons配合IAR编译出错的问题
- 完善lm3s9b9x分支
---- 更新eth驱动
---- 新增sdram驱动
- 完善stm32分支
---- 更新enc28j60驱动，修正无响应问题点
- 完善stm32f10x分支
---- 更新touch驱动
---- 更新eth驱动
---- 更新rtc驱动
---- 修正DMA_clear_Flag设置错误的问题
- 完善stm32f20x分支
---- 更新eeprom驱动
---- 更新RTC驱动
---- 新增SPI FRAM驱动
- 完善efm32分支
---- 更新CMSIS和efm32lib到2.3.2
- 完善lpc24xx分支
---- 增加异常处理函数
- 完善lpc2148分支
---- 修正scons+keil编译出错问题
---- 新增thumb模式的移植代码	
	
	
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread 0.4.0 RC1
发布时间: 2011/10/1
		
RT-Thread经过三个月时间的开发测试（SVN有100多次更新），RT-Thread 0.4.0 beta2顺利演变为RT-Thread 0.4.0 RC1。

RC版本的发布意味着离RT-Thread 0.4.0 正式版的发布已经不远了，在RC版本之后，将不再有新功能加入。欢迎大家测试，让我们一起迎接RT-Thread 0.4.0 正式版的到来。

更新履历
内核：
=====
* ARM cortex M3支持应用模块
* RT-Thread中实现errno
* 任务开始时调用任务调度函数
* 重写应用模块的memory allocator
* 修正当前任务被抢占时调用rt_thread_exit()出错的问题
* 修正函数rt_mb_send_wait()，禁止修改当前任务的error
* 修正一处拼写错误
-- rt_thread_switch_interrput_flag -> rt_thread_switch_interrupt_flag
* 内核代码统一代码风格
* 内核代码统一使用unix换行符'\n'

组件：
=====
* Lwip
-- 重新设计Lwip 1.4.0 ethernetif接口函数及初始化流程
-- 新增eth_device_linkchange()函数
-- 修正在中断处理中调用rt_mb_send()时，当前任务的error会被修改的问题
-- 重写sys_arch_protect()函数，在该函数内关中断并且关调度
-- 修正Issue 11(http://code.google.com/p/rt-thread/issues/detail?id=11)
-- 优化netio代码
-- 新增finsh shell命令list_tcps()
-- 更新Lwip 1.4.0，兼容旧的驱动程序

* RT GUI
-- 修正画点时坐标超出DC缓存的问题
-- 修正函数dc_buffer_fill_rect()中，前后背景颜色显示错误的问题
-- 修正hz字体解除问题
-- 修正中文字体显示错误问题
-- 修正list控件的键盘事件处理问题

* dfs
-- 修正dfs_romfs_lookup(), dfs_romfs_open()及dfs_romfs_lseek()实现中的问题

* finsh
-- 修正node分配失败的问题

分支：
=====
* 新增龙芯LS1B分支
-- 支持finsh
-- 支持RT-Gui
* 更新AT91SAM9260分支
-- 支持Keil MDK编译
-- 针对Lwip API的变更，相应的更新了EMAC驱动
* 更新stm32f107分支
-- 更新eth驱动
-- 更新uart驱动
* 修正renesas M16C移植
-- 完善移植代码
-- 用C实现上下文切换，修正汇编代码中的参数传递寄存器不确定的情况
* 修正NEC V850E移植
-- 完善移植代码
-- 用C实现上下文切换函数用C语言实现代替之前的汇编实现
* 更新EFM32分支
-- 新增Accelerometer驱动
-- 新增ethernet驱动
* 更新mini2440
-- 新增x35 LCD驱动
-- 完善touch驱动
* 更新avr32uc3b0分支
-- 支持scons
* 更新lpc24xx分支
-- 支持thumb模式
* 更新FM3分支
-- 增加scons+iar的编译支持
* 更新pic32ethernet分支
-- 完善移植代码
-- 增加uart驱动
* 更新lpc1114分支
-- 修正systick设置问题
* 更新stm32f20x分支
-- 增加I2C驱动
-- 增加SD卡驱动
-- 增加RTC支持	

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread 0.3.4
发布时间: 2011/12/31
	
0.3.x系列的又一修订版本

- 更新STM32分支enc28j60驱动，修正无响应问题
- 修复mini2440编译出错问题
- 修复lpc2478分支scons编译出错的问题
- 修复RT_LWIP_DNS重复定义问题
- 统一kernel部分的代码风格
- 更新版本号为0.3.4	

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread 0.3.3
发布时间: 2011/9/30

与上一版本比较RT-Thread 0.3.3版本内核只有一处修改，该版本的发布只有一个目的：稳定！
建议所有使用RT-Thread 0.3版本的用户升级到RT-Thread 0.3.3。

内核:
=====
* 修正接收侧线程 error 号被中断服务例程错误更改，从而出现从邮箱中接收消息会发生重复接收的问题	
	
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread 0.3.2正式版
发布时间: 2011/7/4

帖子由 lgnq ? 2011年 7月 4日 15:46
发布说明
========
RT-Thread 0.3.2是RT-Thread 0.3.0发布以来的第二次修订版本，虽无新特性增加，但稳定性有所提高，建议用户及时更新。

这个版本支持的硬件平台数量与0.3.0正式版本的一致：
* ARM Cortex-M3系列：STM32，LM3S以及LPC1766。
* ARM7TDMI系列：LPC2148，LPC2478，AT91SAM7X256，AT91SAM7S
* ARM920T系列：S3C2440（mini2440）
* IA32：QEMU及真实的x86机器

修正的问题包括：
* 内核中使用0.4.x系列的定时器实现；
* 内核中当不使用RT_USING_DEVICE，即设备模型时，编译错误的修正；
* 内核中添加邮箱满时发送线程挂起等待的接口：rt_mb_send_wait。
* 内核中修正在为空的memory块上进行rt_realloc时的问题；
* 内核中rt_mp_create函数添加对申请失败的处理；
* 内核中rt_thread_detach函数主动对线程状态更改为CLOSE状态；
* ELM文件系统中支持多个驱动器；
* ELM文件系统中支持超过512字节大小的扇区；
* LwIP协议栈移植中使用rt_mb_send_wait来做为邮箱发送接口；
* 修正lm3s网卡驱动的问题；
* 修正STM32F107网卡驱动的问题；
* 修正lpc176x网卡驱动的问题；
* 修正libcpu/arm/AT91SAM7X/interrupt.c中一处语法错误
* 完善RT-Thread代码注释

RT-Thread在Google SVN服务器上的开发分支亦做了相应调整：
原来的branches/rtt_0_3_2分支更改为branches/rtt_0_3_3。

代码：http://code.google.com/p/rt-thread/downloads/detail?name=RT-Thread-0.3.2.zip

文档：
RT-Thread实时操作系统编程指南与0.3.0正式版的相同，以后会逐渐由API说明文档替代，朝着正规化的方向发展。

(*) 希望使用新特性的开发人员请关注后续0.4.0版本的发布情况，0.4.0版本添加了很多的新特性，例如：16位的瑞萨M16分支，大端模式的AVR32分支，以及MIPS分支等。

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	

版本: RT-Thread 0.4.0 beta2
发布时间: 2011/7/4

这是RT-Thread 0.4.x系列的第二个测试版本。这个测试版本，依然更多的面向测试目的，不建议直接应用到实际的产品中。RT-Thread 0.4.0的非正式版本依然沿用GPL v2许可证进行发布，欢迎测试。

RT-Thread 0.4.0版本初始提出的几个功能亦基本达到，提供了相对完善的POSIX thread接口，动态库载入接口libdl以及应用模块支持。这些新功能的加入使得RT-Thread能够初步的兼容于POSIX标准。

自RT-Thread 0.4.0 beta1版本以来的更改：
内核：
* 增加邮箱满时发送线程挂起等待的接口：rt_mb_send_wait
* 增加RT_USING_CONSOLE选项
* 新增4个设备类型(RT_Device_Class_Graphic, RT_Device_Class_I2C, RT_Device_Class_USBDevice, RT_Device_Class_USBHost)
* 修正未定义RT_USING_DEVICE，即设备模型时，编译错误的问题

组件：
* net
** 新增LWIP 1.4.0的移植
** LwIP协议栈移植中使用rt_mb_send_wait来做为邮箱发送接口
* minilibc
** 增加 malloc, realloc, free, calloc接口
* newlib
** 增加跟多的数学函数(coef, horner, sqrt, ln, exp, pow)
* pthreads
** pthreads脱离对newlib的依赖
* 文件系统完善
** fatfs版本由原来的R0.07e升级到R0.08b
** 修正fatfs目录搜索不正确的问题
* finsh
** 修正finsh GCC编译时variable section end错误的问题
** 修改list_module_obj命令为list_mod_detail
* RT-Thread/GUI
** 重新设计RTGUI图形驱动接口
** 修正多边形填充问题

分支：
在原有的基础上（ARM7，ARM9，ARM Cortex-M3, IA32）,新增了MIPS，AVR32（大端模式），瑞萨M16C/62P（16位），瑞萨（原NEC）V850E
* 新增at91sam9260分支
* 新增avr32uc3b0分支
* 新增efm32分支
* 新增fm3分支
** mb9bf500r分支
*** 支持RTGUI
** mb9bf506r分支
*** 支持NAND FATFS
* 分离lm3s分支
** lm3s8962分支
** lm3s9b9x分支
* 新增lpc122x分支
* 新增m16c62p(Renesas M16C/62P)分支
** 支持IAR for M16C编译
** 支持scons+IAR编译
* 新增mini4020分支
* 新增nios_ii分支
* 新增pic32ethernet分支
* 分离stm3210分支
** stm32f107分支
** stm32F20x分支
** stm32f10x分支
*** 更新 STM32F10x_StdPeriph_Lib_V3.5.0
* 新增upd70f3454(Renesas V850E)分支

tools:
* 精简tools目录，只留下building.py，其他工具转移到www.rt-thread.org
* 进一步完善building.py
** 修正编译mini2440工程时，提示the command line too long的问题
** 自动创建IAR工程
** 自动创建MDK4工程 

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	

版本: RT-Thread 0.4.0 beta1
发布时间: 2010/11/30
自RT-Thread 0.3.0正式版发布以来，经过开发人员密集的整8个月开发，大众用户的积极反馈、测试，终于完成了RT-Thread 0.4.x系列的第一个测试版本。这个测试版本，依然更多的面向测试目的，不建议直接应用到实际的产品中。RT-Thread 0.4.0的非正式版本依然沿用GPL v2许可证进行发布，欢迎测试。
RT-Thread 0.4.0版本初始提出的几个功能亦基本达到，提供了相对完善的POSIX thread接口，动态库载入接口libdl以及应用模块支持。这些新功能的加入使得RT-Thread能够初步的兼容于POSIX标准。
自RT-Thread 0.3.0版本以来的更改：
内核：
* 添加应用模块支持；支持两者应用方式：.mo 符号预解析应用；.so 符号未解析应用。.so应用需要在加载时动态解析符号。能够执行本地文件系统的应用模块，也能够执行网络文件系统上的应用模块。
* 修正在rt_realloc参数中传入一个NULL指针时，分配失败的问题。修正slab管理器中对0xffffffff尺寸内存分配的问题；
* 修正OS节拍数溢出的问题。(charlie weng提供相应的patch)
* 块设备中读写偏移、大小等都更改成按块为单位；
* 更改rt_device中成员private名为user_data；
* 线程TCB中添加cleanup域，它将在线程运行结束时回调。

组件：
* 添加newlib移植，当前仅能够支持GNU GCC编译环境；
* 添加POSIX thread兼容接口（支持barrier，cond，mutex，rwlock，spin，tls等），采用IEEE Std 1003.1, 2004 Edition为参考进行实现；
* 添加libdl兼容接口，能够使用dlopen，dlsym，dlclose等接口动态加载库；
* 文件系统完善
* 对设备虚拟文件系统代码部分进行调整，精简；
* 修正device file system中struct stat的问题（能够兼容于newlib、minilibc、Keil MDK）
* 修正dfs_filesystem_lookup函数中空项操作的问题；
* 增加fstat接口；文件系统实现中增加mkfs，statfs接口以获得文件系统相关的信息。
* 添加romfs文件系统，可以采用mkromfs.py脚本生成相应的ROM文件系统；
* 添加devfs文件系统，增加/dev/console设备，它是一个虚拟设备，用于标准输入、输出、错误等；
* 添加NFS v3客户端文件系统，可以配合FreeNFS/Linux NFS使用，以访问主机上的目录和文件；
* elm fat文件系统
* 添加非512扇区的宏定义；
* 添加卸载的功能。
* 修正重命名的问题；
* RT-Thread/GUI
* 增加bmp图像格式支持；
* 原来的hardware dc更改为client dc；重写新的hardware dc，新的hardware dc绘图速度会更快。
* 加入了非等宽字体支持。
* 加入TTF字体支持，但内存空间占用估计比较大，对于unicode的问题还存在些问题。
* 修正filelist_view控件析构的问题。
* 对DC操作进行调整完善 (由richard lion完成)

分支：
STM3210
* 完善SDIO驱动，并提供超过4G卡的支持；
mini2440
* 能够使用0.4.0分支上所有的特性，能够开启newlib支持，能够开启POSIX thread支持，能够开启libdl支持。
增加LPC的ARM Cortex-M0/3系列移植分支；
增加新唐的ARM Cortex-M0 NU1xx分支；
增加龙芯I SoC3210分支(MIPS 32位体系结构)

<其他分支，例如avr32，瑞萨m16，SEP4020等分支，由于分支维护人来不及准备，此次发布未包括在内，可以自行从RT-Thread的google svn中获取>

移植的组件：
* wyoujtg完成国内知名的开源项目FTK移植。FTK是一套极为绚丽，完整的GUI系统。

文档：
RT-Thread 0.4.0在线API文档
下载：
RT-Thread 0.4.0 beta1下载

【RT-Thread 0.4.x分支的额外说明】似乎很多人误以为0.4.x分支是面向资源丰富的平台，不太适合类似STM32这样的CM3平台。这里要说的是，0.4.x分支绝大部分是兼容0.3.x分支，并且也非常适合于STM32等面向微控制器的硬件平台。例如POSIX thread部分，它能够运行于STM32平台，如果使用Code Sourcery GCC工具链，同样能够支持其中的newlib C库。这部分同样对内存的需求非常少，并且后续会移植到其他编译环境下。0.4.x分支一些特性不适合于微控制器的包括：
- 应用模块加载。
- FTK GUI。

对于Cortex-M3等平台，我们目前也在对 应用模块特性 进行评估，看看从技术上是否能够从另外的途径解决动态运行速度慢的问题。
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
	
版本: RT-Thread 0.3.1正式版	
发布时间: 2010/9/29
是发布0.3.1正式版的时候了：在0.3.1的维护过程中，得到了大家很多的反馈，其中一些bug及修正也是由大家指出，这里感谢大家一直以来的支持，RT-Thread的发展进步离不开大家的帮助，谢谢！ 相较RT-Thread 0.3.0版本，0.3.1版本是一个bug修正版，并无添加新的特性(*)，使用上与0.3.0版本完全兼容。建议使用RT-Thread 0.3.0版本的用户，如果需要长时间不间断运行（大于1年），请切换到0.3.1正式版本来。

这个版本支持的硬件平台数量与0.3.0正式版本的一致：
* ARM Cortex-M3系列：STM32，LM3S以及LPC1766，STM32中新添加STM32F100系列芯片支持。
* ARM7TDMI系列：LPC2148，LPC2478，AT91SAM7X256，AT91SAM7S
* ARM920T系列：S3C2440（mini2440）
* IA32：QEMU及真实的x86机器

修正的问题包括：
* 修正OS Tick溢出的问题。
* 修正定时器有时会被延期操作的问题。
* 修正heap分配器尾部数据浪费的问题。
* 修正rt_realloc时内存可能被浪费使用的问题。
* 调整各内核对象结构使得内存布局更合理。

* 修正ELM FatFs接口中rename的问题。
* 修正LwIP中IGMP的问题。
* 完善当发送mail失败时LwIP的处理。
* 增强、完善RT-Thread/GUI的功能。

RT-Thread在Google SVN服务器上的开发分支亦做了相应调整：
原来的branches/rtt_0_3_1分支更改为branches/rtt_0_3_2。

代码：见附件。

文档：
RT-Thread实时操作系统编程指南与0.3.0正式版的相同，以后会逐渐由API说明文档替代，朝着正规化的方向发展。

STM32分支
---------
请注意STM32分支的工程文件组织方式和0.3.0版本中的不一样，原来的几个目录是不相独立的工程，而0.3.1中为了避免混淆，把它们变成了独立的工程(注：因为0.3.1与0.3.0是完全兼容的，所以不一定要更新BSP目录)。

project_107是针对STM32F107芯片的工程，project_valueline是针对STM32F100芯片 STM32 Discovery开发版的工程，其余的芯片默认是STM32F103ZE。如果要修改成自己所需要的芯片，请遵循一下步骤：
* 在board.h文件中修改STM32_SRAM_SIZE宏定义，它的单位是KB，所以针对于STM32F103VB类型的芯片，只需要把它定义成20即可。
* 在使用Keil MDK打开board.h文件时，也能够使用Keil MDK带的界面配置方式进行配置。
* 在工程选项的C编译器预定义上，修改成和芯片匹配的类型，例如STM32F10X_HD、STM32F10X_MD等。

另外，STM32分支支持IAR编译器，在使用IAR ARM时，如果你使用了finsh，请注意，最好在链接配置文件中加入
keep { section FSymTab };
keep { section VSymTab };
它的作用是为了保留finsh中使用到的符号表，因为这些符号表仅在命令行被调用，所以他们可能在最后生成目标文件时被优化掉。

具体请看stm32f10x_flash.icf文件。

LM3S分支
--------
LM3S分支默认采用LM3S8962芯片，针对的是TI这次发的48￥ 8962开发板。

LPC176x分支
-----------
工程默认包括finsh shell，文件系统，网络协议栈的支持。

(*) 希望使用新特性的开发人员请关注后续0.4.0版本的发布情况，0.4.0版本添加了很多的新特性，例如：16位的瑞萨M16分支，大端模式的AVR32分支，以及MIPS分支等。	


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	

版本: RT-Thread 0.3.0正式版
发布时间: 2010/3/30
		
相较以前的RT-Thread 0.3.0 RC版本，无大的修改（console调整为支持设备的模式），但依然建议所有使用0.2.x、0.3.0 beta/rc版的用户都开始使用0.3.0正式版。当前版本支持如下移植分支：
- ARM Cortex-M3系列：STM32（包含STM32F107），LM3S，LPC1766
- ARM7TDMI系列：LPC2148，LPC2478，AT91SAM7X256，AT91SAM7S
- ARM920T系列：S3C2440（mini2440）
- IA32：QEMU及真实的x86机器

RT-Thread在Google SVN服务器上的开发分支亦做了相应调整：
原来的开发主干（trunk）更改为branches/rtt_0_3_1
当前的开发主干（trunk）作为当前的RT-Thread 0.4.x开发分支继续前进。

RT-Thread 0.3.1版本将在目前的0.3.0正式版上进行补丁修正，并且当0.4.x分支一些有用的、稳定功能也会迁移会0.3.x 分支。

后续会陆续加入一些AppNotes。

补充说明：
STM3210分支
Keil MDK工程文件位于bsp\stm3210目录下，仅是基本的led工程；
系统默认采用STM32F103ZE芯片，其他芯片需要修改的位置：
- 根据芯片片内SRAM大小修改board.h文件
- 如果是STM32F107，请直接使用project_107目录下的工程(见下面详细的使用说明)

同时在bsp\stm3210目录下还存在多个以project_开头的目录，这些相应的针对不同类型的工程，例如project_finsh针对在RT-Thread中使用finsh shell的情况。当需要使用这些工程时，需要把相应project_xxx目录中的文件都复制到 stm3210目录中(直接同名覆盖的方式)，然后再行打开stm3210目录下的工程文件。

LM3S分支
LM3S的Keil MDK工程文件放在bsp\lm3s目录下；针对LM3S8962芯片(因为这个TI送的是带这个芯片的开发板)，需要在 board.h中
// For lm3s8962, it should be SYSCTL_XTAL_8MHZ
#define LM3S_XTAL_TYPE SYSCTL_XTAL_6MHZ

把如上这个定义更改为SYSCTL_XTAL_8MHZ，否则得话会锁死JTAG。	
	
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread/LM3S 0.3.0 RC1版发布
发布时间: 2010/1/4

实时线程操作系统是一款面向实时领域的操作系统，这个和通常的通用操作系统有着很大的不同。通用操作系统通常面对的是日常应用，例如打开浏览器上网，播放音乐，采用字处理软件编辑文档。
在古老的时代，通用操作系统一般只能处理一件事，而随着计算机技术日新月异的发展，硬件更新换代，上GHz主频、上GB内存、多核技术走进普通人的生活中，通用操作系统也就朝着并行化计算的方向发展。通用操作系统更多讲究的是，对这并行事务处理的公平性上，例如一个个民工在不同的窗口进行排队购买火车票，好的调度系统能够保证每个民工的公平性。
实时系统和这种通用系统有很大的差别。实时系统指的是，当外界有系统关注的相应事件发生时，系统能够在指定的时间内（deadline）进行正确的响应。用于实时系统的操作系统就叫做实时操作系统。从系统的定义也可以看得出，实时操作系统和通用操作系统在事务的处理上有明显的区别，实时操作系统有非常强的针对性，对相应的事件力求做到这固定的时间内进行响应；而通用操作系统则需要努力地做到各个事务的公平性（某些系统也会非常注意数据的吞吐量，例如网络服务器）。
实时线程操作系统（英文名RT-Thread）面向的正是这么一类的实时系统，因为其小型的特点也可以看成是一个嵌入式操作系统（嵌入式系统一般是针对一些专有目的而存在，比较吝啬于成本。而基于专有目的的特点，也注定了嵌入式系统或多或少的具有一些实时性的特点）。这种系统可以用于自动售票机，税控机，移动通信设备，mp3/mp4等便携式音乐设备，飞行器控制，车体导航控制，打印机，复印机，各类监控设备，路由器，ADSL，机顶盒等网络设备，医疗设备等等。
TI流明LM3S系列芯片是基于ARM Cortex M3 v7构架的32位芯片，其中LM3S S6000，S8000，S9000系列芯片携带网络功能。RT-Thread的标准内核可以运行在除LM3S S100系列外的所有系列芯片上。这次RT-Thread针对于LM3S进行移植验证并经过压力测试的是LM3S6918芯片，芯片携带64K片内静态内存，256K闪存，频率是50MHz。在这个平台上，RT-Thread支持的特性包括：
? 完善的实时核心
- 面向对象方式的实时核心（但依然保留了C语言的优雅、小巧风格）；
- 默认32线程优先级的全抢占式实时内核（亦可配置成256线程优先级）；相同优先级线程时间片轮转调度；
- 相同优先级线程实施时间片可配置的分时时间片轮转调度；
- 线程间同步机制：信号量和防止优先级翻转的互斥锁；
- 完善高效的线程间通信机制，包括邮箱，消息队列和事件；
- 支持线程挂起和唤醒的固定内存块管理及线程安全的动态内存堆管理；
- 向上层提供基于名字的统一接口设备驱动模型；

? FinSH shell命令行
- 命令即C代码的命令行方式；
- 直接在命令行中调用系统内核函数；
- 直接在命令行中访问系统全局变量；
- 历史记录及命令自动补全；

? 面向小型设备的虚拟文件系统
- 向上层应用提供POSIX风格的API接口；
- 支持多种具体文件系统实现；
- LM3S分支内置SD卡驱动程序；

? LwIP轻型TCP/IP协议栈
- 标准的BSD Socket接口；
- IP、ICMP、UDP、TCP标准协议支持；
- DNS，DHCP，PPP协议支持；
- TFTP、HTTP、FTP应用协议支持（见netutil组件）；
- LM3S分支内置以太网驱动；

? 开发环境支持：
- GNU GCC (scons做为构建工具)
- Keil MDK


以上是RT-Thread/LM3S 0.3.0的特性，这些特性在RT-Thread 0.3.x分支中不会有大的改变。

技术指标及优势
看完RT-Thread的特性后，看看一些其他有吸引力的地方。

首先是体积。看网上有网友说，RT-Thread是否是基于Linux，或者直接使用Linux，这里不得不说，Linux并不是任何事情都做得到，它做不到在数KByte的内存占用上依然能够非常好的运行，而这类设备非常多。例如LM3S这类芯片，本身只有大约64K或更少的片内静态内存，另外就是闪存（通常在128K - 512K之间）。外扩内存基本上不太可能，这类芯片是完全的成本敏感型芯片，硬件决定了它已经不能外扩内存（LM3S最新款的已经支持能够外扩内存了，不过手上还没拿到）。

看几个体积指标：
RT-Thread标准Kernel（标准Kernel指得是没经过剪裁的内核）：
9.5K只读数据和执行代码占用，1.5K内存占用（通常只读数据和执行代码放置在闪存中）

包括上面说的完整组件，即标准Kernel，finsh shell，文件系统，网络协议栈：
80K只读数据和执行代码占用，13.5K内存占用，当运行时，会有5K左右的动态内存占用。即当系统运行时，大约剩余45K内存给用户使用。

和LM3S提供的无操作系统LwIP，FatFS文件系统比较：
120K只读数据和执行代码占用，35K内存占用。即当系统运行时，大约剩余20K内存给用户使用。

再看看针对网络的一些性能指标
对比情况采用了相同的netio测试得到的数据统计
RT-Thread/LM3S
NETIO - Network Throughput Benchmark, Version 1.26
(C) 1997-2005 Kai Uwe Rommel
TCP connection established.
Packet size 1k bytes: 704 KByte/s Tx, 5131 Byte/s Rx.
Packet size 2k bytes: 704 KByte/s Tx, 1950 KByte/s Rx.
Packet size 4k bytes: 704 KByte/s Tx, 2197 KByte/s Rx.
Packet size 8k bytes: 704 KByte/s Tx, 2200 KByte/s Rx.
Packet size 16k bytes: 706 KByte/s Tx, 2196 KByte/s Rx.
Packet size 32k bytes: 709 KByte/s Tx, 2136 KByte/s Rx.
Done.

TI/无操作系统情况下的LwIP
NETIO - Network Throughput Benchmark, Version 1.26
(C) 1997-2005 Kai Uwe Rommel
TCP connection established.
Packet size 1k bytes: 870 KByte/s Tx, 5187 Byte/s Rx.
Packet size 2k bytes: 870 KByte/s Tx, 2463 KByte/s Rx.
Packet size 4k bytes: 870 KByte/s Tx, 3322 KByte/s Rx.
Packet size 8k bytes: 870 KByte/s Tx, 3239 KByte/s Rx.

（上面的是PC端NETIO输出的结果，Tx对应LM3S开发板上的接收，Rx对应LM3S开发板上的发送）
从上面可以看出，在大数据块发送时，RT-Thread/LM3S的移植会有一些损耗，但总的来说损耗不算太大，特别是报文在1k - 2k范围时数据相差不大。如何看待这个差异：通常没有操作系统时，系统能够更专注的做一件事。而有操作系统的情况下，它能够额外的做一些事务，这些事务在进行切换时，会产生一定的系统资源开销。总的来说，体积上的改善一定程度上弥补了性能的差距（例如RT-Thread/LM3S能够支持16k、32k bytes大小的网络包发送接收，而无操作系统的LwIP则不能）。

最后看看一些实时性能指标
这组数据是与著名的开源实时操作系统ecos的比较。测试代码完全相同，硬件平台相同（采用的是PXA310），编译器相同（GNU GCC），编译参数相同：
基本任务测试 RTT/ecos 1.40倍
协作调度测试 RTT/ecos 1.20倍
抢占调度测试 RTT/ecos 1.33倍
同步处理测试 RTT/ecos 1.86倍
内存分配测试 RTT/ecos 2.50倍

当一个实时操作系统能够做到稳定运行、性能比拟普遍运行的系统有一定优势、后续能够稳定发展时，那么她将是一款能够得到普遍使用的系统，而事实也正是如此：在中国，已经有十来家公司采用RT-Thread运用于他们的产品中，而后续打算在产品中采用RT-Thread的公司还有更多。

许可证
作为一套基础组件，就例如电脑中的中文输入法一样，它不应该收费，因此它能够免费的使用于商业产品中（0.3.x系统仅需要在我们这边进行产品信息备案，更换GPLv2许可证为商业许可证！0.4.x将更换产品许可证为BSD或Apache开源许可证）。

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
	
版本: RT-Thread RTOS v0.2.3版本
发布时间: 2008/10/6
		
更新记录
- 添加slab内存管理器；
- 添加用于小型内存系统的动态内存管理器 （使用动态内存时，小型内存管理器与slab内存管理器中使用其中之一）；
- 添加lwip做为RT-Thread的TCP/IP协议栈 （0.2.3包含AT91RM9200网卡驱动，及QEMU/s3c2410虚拟的rtl8019网卡驱动）；
- 添加C++特性支持；
- finsh中添加动态添加系统调用及系统变量的API；
- 修正rt_int*_t定义为显式的signed定义；
- 修正线程超时函数的问题；
- 修正链表中初始化问题；
- 修正Object中调用钩子函数的问题；

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------	
版本: RT-Thread v0.2.2
发布时间: 2008/6/12	
RT-Thread v0.2.2单内核正式版发布，这个版本主要是增加更多的BSP移植：
- s3c44b0的移植 [Xu Xinming]
- AT91SAM7S64的移植 [Bernard Xiong，感谢icdev.com.cn提供开发板]

以下的移植仍然是试验性质的
- NDS掌上游戏机的移植[vai]
- ia32的移植[Qiu Yi]，在QEMU虚拟机中测试完成

以下是各个移植的一些说明：
AT91SAM7S64: (系统资源：16k RAM，64k ROM Flash)
为配合小内存情况，RT-Thread 0.2.2支持任务最大优先级为32的情况，以保证内存占用更小（所有二进制代码小于10k）
在AT91SAM7S64移植中，串口并没打开，finsh也没启用。
在bsp/icdevs64/build目录下附带uVision的工程文件，需要机器上安装有keil的gcc编译器

ia32:
支持i386-elf-gcc for windows的编译，linux下的还没试，应该也可以顺利编译。
编译完成后在bsp/qemu目录下生成rtthread-qemu.elf
把这个elf文件配置到grub的配置文件中，具体的grub配置请参看grub文档				