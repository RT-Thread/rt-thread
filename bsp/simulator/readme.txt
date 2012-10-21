两种方法编译当前bsp

编译：
1). 使用Visual Studio(2005以上版本）打开vs2005.vcproj
    编译后运行
   
2). 使用scons编译，在当前目录中打开cmd，输入
    scons -j4
    编译完成后会在当前目录下生成 rtthrad-win32.exe，双击即可运行。

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
