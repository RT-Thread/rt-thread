说明: 本BSP可以如下演示

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

二 组件配置
1) RTGUI
当前代码中已经不含RTGUI源码，因此读者需要配置一下才能在simulator中使用RTGUI
RTGUI的最新源码目前是托管在github上：https://github.com/RT-Thread/RTGUI
共有两种方法。
方法1 添加环境变量
   向系统加入RTT_RTGUI环境变量，其值为刚才github上下载的rtgui源码包的路径。
   例如笔者的rtgui源码包解压至 F:\Project\git\rt-gui\下， 则将此环境变量配置为 F:\Project\git\rt-gui\components\rtgui
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

三 编译
1) 使用Visual Studio(2005以上版本)
在当前目录中打开cmd，输入命令
`scons --target=vs -s`
可以生成project.vsproj，双击运行

2) 命令行编译
修改rtconfig.py, 配置合适的编译器(msvc/mingw/gcc)，及其路径
在当前目录中打开cmd，输入命令
`scons -j4`
编译完成后会在当前目录下生成 rtthrad-win32.exe，双击即可运行。

四 程序测试
1) 测试文件系统
此时当前目录下，新增了三个文件
 sd.bin--模拟SD卡，挂载fat，大小为16M
 nand.bin-模拟nand flash，挂载uffs，参数page=2048+64bytes，block=64pages，16M
 nor.bin--模拟nor flash，挂载jffs2，型号为sst25vf，2M
第一次启动时，会看到fatfs挂在失败。
按下回车，出现finsh，然后输入`mkfs("elm", "sd0")`格式化SD卡，如下所示
	finsh>>mkfs("elm", "sd0")
			0, 0x00000000
然后重启程序，就可以看到fatfs挂载成功了

2) 测试RTGUI
启动后就会看到GUI窗口，分辨率800x480，此时在finsh中输入snake_main()并回车，即可运行贪吃蛇程序

3) 测试APP module
rtconfig.h中需要打开RT_USING_MODULE

a. 生成rtthread.def文件
使用msv编译主程序时需要此文件，使用MingW编译主程序时不需要
msvc需要此文件才能生成正确导出符号的rtthread.dll和rtthread-win32.exe。
此目录下默认自带了一个rtthread.def文件，当修改了rtconfig.h，禁用了某些组件时，则需要重新生成rtthread.def文件.
生成方法：
需要借助MingW工具，修改rtconfig.py中CROSS_TOOL为'mingw'，然后打开CMD执行`scons --def`就会自动更新rtthread.def。

b. 生成主程序
  主程序可以使用msvc和mingw生成
  如果rtconfig.h中的使能了RTGUI，则需要参考第二节第1小节配置RTGUI
  a.1 使用msvc
	  修改rtconfig.py中CROSS_TOOL为'msvc'
	  首先要保证当前目录下有合适的rtthread.def文件，如果没有对默认的rtconfig.h作修改，则使用默认的rtthread.def即可
	  CMD命令行执行`scons -j4`，即可生成rtthread.dll和 rtthread-win32.exe
  a.2 使用mingw
	  修改rtconfig.py中CROSS_TOOL为'mingw'
	  CMD命令行执行`scons -j4`，这就会生成 rtthread.dll和 rtthread-win32.exe

c. 生成app module
  进入testdll目录，再次修改 testdll/SConstruct， 同样需要配置RTT_RTGUI路径，同 1中3)
  在此目录下执行
    `scons --app=basicapp`
  就会在 basicapp/building目录下生成 basicapp.dll。 

  然后运行simulator目录下的 rtthread-win32.exe, 在finsh中运行   
    `exec("/testdll/basicapp/building/basicapp.dll")` 
  如果觉得这个路径太长，就把 basicapp.dll复制到 simualtor目录下，执行
    `exec("/basicapp.dll")`

如果想编译RTGUI应用，如testdll目录下的snake，则需要对RTGUI打一点补丁，共有两个方法
1. 注释掉 //#define RTGUI_USING_CAST_CHECK`
找到rtgui_config.h源码，注释掉如下语句 
//#define RTGUI_USING_CAST_CHECK`

然后在testdll目录下打开CMD窗口，执行`scons --app=snake`，才可以正确编译，如果不注释掉上面的宏，则会出现链接错误。

2. 不注释掉#define RTGUI_USING_CAST_CHECK`
那么需要如下两个补丁
1) 修改testdll/SConstruct文件
diff --git a/bsp/simulator/testdll/SConstruct b/bsp/simulator/testdll/SConstruct
index 3324f88..005289c 100644
--- a/bsp/simulator/testdll/SConstruct
+++ b/bsp/simulator/testdll/SConstruct
@@ -70,6 +70,7 @@ env.Append(CCFLAGS=rtconfig.CFLAGS)
 env.Append(LINKFLAGS=rtconfig.LFLAGS)
 env.Append(CPPPATH=CPPPATH)
 env.Append(LIBS='rtthread', LIBPATH='../')
+env.Append(CPPDEFINES=['RTT_IN_MODULE'])
 env.PrependENVPath('PATH', rtconfig.EXEC_PATH)
 
 PrepareModuleBuilding(env, RTT_ROOT)

2) 修改RTGUI源码
diff --git a/components/rtgui/include/rtgui/rtgui_object.h b/components/rtgui/include/rtgui/rtgui_object.h
index 57fd47f..b32ee17 100644
--- a/components/rtgui/include/rtgui/rtgui_object.h
+++ b/components/rtgui/include/rtgui/rtgui_object.h
@@ -56,7 +56,12 @@ extern "C" {
     typedef struct rtgui_type rtgui_type_t;
 #define RTGUI_TYPE(type)            (struct rtgui_type*)&(_rtgui_##type)
 
+#ifdef RTT_IN_MODULE
+#define DECLARE_CLASS_TYPE(type)    _declspec(dllimport) const struct rtgui_type _rtgui_##type
+#else
 #define DECLARE_CLASS_TYPE(type)    extern const struct rtgui_type _rtgui_##type
+#endif
+
 #define DEFINE_CLASS_TYPE(type, name, parent, constructor, destructor, size) \
     const struct rtgui_type _rtgui_##type = { \
     name, \

然后再编译snake，可以正确生成。测试方法同basicapp
