说明: 本BSP可以如下演示
依赖软件包
    python2.7 (python2.6无法生成vs工程）

一 平台及组件支持
目前rtconfig.py中支持的编译器有

1). msvc 用于windows平台
  此平台支持的组件
    kernel
    finsh
    LWIP
    DFS, ELM FatFS, UFFS, JFFS2, DFS_WIN32
    RTGUI
    APP MODULE
2). mingw 用于windows平台
    kernel
    finsh
    DFS, ELM FatFS, UFFS, DFS_WIN32
    RTGUI
    APP MODULE
3). gcc 用于linux平台
    kernel
    finsh
    DFS, ELM FatFS, UFFS
    RTGUI

请根据自己的实际情况，修改rtconfig.py中CROSS_TOOL为上述某一值。

二 组件配置
1) RTGUI
RTGUI的最新源码目前托管在github上：https://github.com/RT-Thread/RTGUI
下载最新的RTGUI源码，将RTGUI源码包中components下的rtgui目录复制到Rt-thread的components目录下。

三 编译
1) 使用Visual Studio(2005以上版本)
在当前目录中打开cmd，输入命令
`scons --target=vs -s`
生成vs2005的project.vsproj，使用vs2005及以上版本可以打开(VS2005需要转换工程）。

或直接生成vs2012工程
`scons --target=vs2012 -s`

2) 命令行编译
修改rtconfig.py, 配置合适的编译器(msvc/mingw/gcc)，及其路径
在当前目录中打开cmd，输入命令
`scons -j4`
编译完成后会在当前目录下生成 rtthread-win32.exe，双击即可运行。

四 程序测试
1) 测试文件系统
此时当前目录下，新增了三个文件
 sd.bin--模拟SD卡，挂载fat，大小为16M
 nand.bin-模拟nand flash，挂载uffs，参数page=2048+64bytes，block=64pages，16M
 nor.bin--模拟nor flash，挂载jffs2，型号为sst25vf，2M
第一次启动时，会看到fatfs挂在失败，因为文件系统没有格式化，需要键入以下命令：
`mkfs sd0`
重启运行程序，可以正确挂载、使用FATFS文件系统。

2) 测试RTGUI
打开RTGUI组件后编译，启动在finsh中输入snake_main()并回车，可运行贪吃蛇程序

3) 测试APP module
在rtconfig.h中打开RT_USING_MODULE

测试app module需要执行3步，如下a, b, c所示。

a. 生成rtthread.def文件
执行`scons --def`可以自动生成rtthread.def。
当修改了rtconfig.h，打开或禁用了某些组件时，需要重新生成rtthread.def文件.

b. 生成主程序

  `scons -j4`

c. 生成app module
  进入testdll目录，再次修改 testdll/SConstruct， 同样需要配置RTT_RTGUI路径，同 1中3)
  在此目录下执行
    `scons --app=basicapp`
  就会在 basicapp/building目录下生成 basicapp.dll。 

  然后运行simulator目录下的 rtthread-win32.exe, 在finsh中运行   
    `exec("/testdll/basicapp/build/basicapp.dll")` 
  如果觉得这个路径太长，可以将basicapp.dll复制到 simualtor目录下，执行
    `exec("/basicapp.dll")`

  编译贪吃蛇程序
  执行`scons --app=snake`，会在snake/build/下生成snake.dll，按照同样的方式加载即可
