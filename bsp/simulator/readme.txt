说明: 本BSP可以如下演示
默认演示realtouch GUI效果，并提供了一个贪吃的demo用于演示

目前支持的功能有
1). LWIP（可以打开LWIP选项，不过尚存在bug，不建议使用）
2). 文件系统支持，支持ELM FatFS，UFFS，JFFS2
3). RTGUI支持
   目前SVN中的RTGUI源码可以直接用于simulator。
   如果读者想快速在simulator上体验RTGUI，那么不需要修改任何文件，首先在命令行中使用
   scons --target=vs -s
   生成工程后，打开project.vsproj编译，即可看到realtouch的ui出现，然后执行
   在finsh中执行snake_main()，即可运行贪吃蛇demo
   
   再补充说明一点，RTGUI的最新源码目前是托管在git上。
	   github网页：https://github.com/RT-Thread/RTGUI
   如果要使用rtgui中的最新源码，共有两种方法。
方法1 添加环境变量
   向系统环境变量中加入RTT_RTGUI，其值为刚才github上下载的rtgui源码包的路径。
   例如笔者的rtgui源码包解压至 F:\Project\git\rt-gui\下
   则将此环境变量配置为 F:\Project\git\rt-gui\components\rtgui
方法2 不添加环境变量
   打开SConstruct文件，
 ....
 10 if os.getenv('RTT_RTGUI'):
 11     RTT_RTGUI = os.getenv('RTT_RTGUI')
 12 else:
 13     # set the rtgui root directory by hand
 14     # empty string means use the RTGUI in svn
 15     # RTT_RTGUI = os.path.normpath(r'F:\Project\git\rt-gui\components\rtgui')
 16     RTT_RTGUI =''         
 ....
将15，16行修改为
 14     # empty string means use the RTGUI in svn
 15     RTT_RTGUI = os.path.normpath(r'F:\Project\git\rt-gui\components\rtgui')
 16     # RTT_RTGUI =''         
简单说明一下：
   1)#号表示注释，类似于c语言中的//，
   2)其中15行的路径为你的RTGUI路径源码，注意不是压缩包路径，而是压缩包路径下的 components\rtgui目录的绝对路径。

1 编译：
1.1 使用Visual Studio(2005以上版本）
    在命令行中执行 scons --target=vs -s 可以生成vs2005的工程，名为project.vsproj
    
    编译后运行
   
1.2 使用scons编译，在当前目录中打开cmd，输入
    scons -j4
    编译完成后会在当前目录下生成 rtthrad-win32.exe，双击即可运行。

2. 测试文件系统
运行：
	编译后运行，会弹出CMD命令行窗口，可以看到控制台的输出信息，如下所示

	 \ | /
	- RT -     Thread Operating System
	 / | \     1.1.0 build Oct 21 2012
	 2006 - 2012 Copyright by rt-thread team
	init jffs2 lock mutex okay
	hello, world
	finsh>>fatfs initialzation failed!
	uffs initialzation failed!
	jffs2 initialzation failed!
	thread 29e4 exit
	hello, world
	hello, world
	hello, world
	hello, world
	hello, world
	hello, world
	hello, world
	hello, world
	hello, world
	thread 2898 exit

	注意上面的信息显示，fatfs/uffs/jffs2均挂载失败，这是因为我们还没有为sd.bin创建fat分区，并且sd上也没有目录用于挂载jffs2和uffs。

	并且此时当前bsp目录下，新增了三个文件用于模拟sd卡，nand flash与nor flash，它们是
		sd.bin--模拟SD卡，挂载fat，大小为16M
		nand.bin-模拟nand flash，挂载uffs，参数page=2048+64bytes，block=64pages，16M
		nor.bin--模拟nor flash，挂载jffs2，型号为sst25vf，2M
	
	按下回车，出现finsh，然后输入如下命令格式化sd.bin

	finsh>>mkfs("elm", "sd0")
			0, 0x00000000
	finsh>>

	关闭程序重新运行，此时可以看到fatfs挂载成功，不过jffs2和uffs依然失败，如下所示。
	 \ | /
	- RT -     Thread Operating System
	 / | \     1.1.0 build Oct 21 2012
	 2006 - 2012 Copyright by rt-thread team
	init jffs2 lock mutex okay
	hello, world
	finsh>>fatfs initialized!
	uffs initialzation failed!
	jffs2 initialzation failed!
	
	这是因为sd上还没有目录来用于挂载jffs2和uffs，在finsh中输入如下命令在sd上创建nand与nor文件夹，分别用于挂载uffs与jffs2文件系统。

	finsh>>mkdir("/nand")
			0, 0x00000000
	finsh>>mkdir("/nor")
			0, 0x00000000
	finsh>>
	然后再次关闭程序后重新运行，此时可以看到jffs2与uffs挂载成功。	

	最终输出如下所示：

	 \ | /
	- RT -     Thread Operating System
	 / | \     1.1.0 build Oct 21 2012
	 2006 - 2012 Copyright by rt-thread team
	init jffs2 lock mutex okay
	hello, world
	finsh>>fatfs initialized!
	os  : system memory alloc 320 bytes
	flsh: ECC size 24
	flsh: UFFS consume spare data size 34
	os  : system memory alloc 83520 bytes
	os  : system memory alloc 52400 bytes
	os  : system memory alloc 2048 bytes
	tree: DIR 0, FILE 0, DATA 0
	uffs initialized!
	jffs2 initialized!
	thread 2fb4 exit
	hello, world
	hello, world
	hello, world
	hello, world
	hello, world
	hello, world
	hello, world
	hello, world
	hello, world
	thread 312c exit

Ok，到现在，一个完整的文件系统测试环境就搭建完毕了，enjoy～～

3 测试RTGUI
   启动后就会看到GUI窗口，分辨率800×480串口，并出现图形界面。
   此时在finsh中输入 snake_main()并回车，即可运行贪吃蛇程序。
