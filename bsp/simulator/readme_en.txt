compile bsp:
There are two ways.
1). Visual Studio(2005 or newer version), open vs2005.vcproj with visual studio
    compile, then run it.
   
2). use scons, open cmd console, change  to current path, then do
      scons -j4
scons will compile this bsp with cl(the compiler of vs), then rtthrad-win32.exe will be created in current directory. Run it by double click it.

run:
  Run, then you can see the following message on CMD window.

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

Then you may note that, three file (sd.bin, nand.bin, nor.bin) are created. These three files are used to simulate as SD CARD, nand flash and nor flash.
		sd.bin--SD card, fatfs, 16M
		nand.bin--nand flash, uffs, page=2048+64bytes, block=64pages, 16M
		nor.bin--nor flash, jffs2, block size is 64K, 2M

Note, it failed to mount fatfs,uffs and jffs2, because there is valid partition on sd card, and there is no directory to mount uffs and jffs2.

So, we should mount sd card at first.
Press ENTER, and run the command "mkfs", like, 

	finsh>>mkfs("elm", "sd0")
			0, 0x00000000
	finsh>>

Then close CMD, and then re-run it. This time, you can see that fatfs is mounted correctly, While uffs and jffs2 are still failed to mount for the reason that there is no any directories for uffs and jffs2.
	 \ | /
	- RT -     Thread Operating System
	 / | \     1.1.0 build Oct 21 2012
	 2006 - 2012 Copyright by rt-thread team
	init jffs2 lock mutex okay
	hello, world
	finsh>>fatfs initialized!
	uffs initialzation failed!
	jffs2 initialzation failed!
	
so, in order to mount uffs and jffs2, we should create directories for them. Do the following commands.

	finsh>>mkdir("/nand")
			0, 0x00000000
	finsh>>mkdir("/nor")
			0, 0x00000000
	finsh>>

Close the CMD console, and restart, then you can see this:

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

Ok, everything is okay, you can develop rt-thread with visual studio. 

Any questions about this bsp, please email me,  goprife@gmail.com

Enjoy~~
                                            prife 2012/10/21
