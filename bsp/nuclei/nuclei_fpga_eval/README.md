# 芯来科技FPGA评估板

## 简介

**芯来科技FPGA系列板** 是由芯来科技公司推出的用于一系列测试评估芯来RISC-V内核处理器的FPGA评估板。

更多关于 **芯来科技FPGA评估板** 开发板的详细资料请参见:

* [Nuclei DDR200T开发板](https://nucleisys.com/developboard.php#ddr200t)
* [Nuclei MCU200T开发板](https://nucleisys.com/developboard.php#mcu200t)
* [蜂鸟开发板](https://nucleisys.com/developboard.php#demosoc100t)

### 板载资源

| 硬件 | 描述 |
| ---  | --- |
| 内核 | Nuclei RISC-V N/NX/UX 内核 |
| 架构 | RV32 or RV64 |
| 主频 | 16MHz or uncertain freq |

**注意**: 这个上面烧写的是FPGA bitstream文件，所以处理器内核版本根据型号来定，通过修改**rtconfig.py**中的**NUCLEI_SDK_CORE**.


## 工具安装

### 安装工具链

请根据[安装Nuclei RISC-V GCC Toolchain和OpenOCD](https://doc.nucleisys.com/nuclei_sdk/quickstart.html#setup-tools-and-environment) 来安装依赖的工具。

### 添加环境变量

将Nuclei RISC-V GCC Toolchain和OpenOCD的环境变量进行设置。

#### Windows

假设工具安装在 **D:\NucleiStudio\toolchain**目录下, 则可以修改系统环境变量**PATH**,
将**D:\NucleiStudio\toolchain\gcc\bin;D:\NucleiStudio\toolchain\openocd\bin;**增加到**PATH**中。

或者在ENV工具命令行中运行

~~~cmd
set PATH=D:\NucleiStudio\toolchain\gcc\bin;D:\NucleiStudio\toolchain\openocd\bin;%PATH%
~~~

#### Linux

假设工具安装在 **~/NucleiStudio/toolchain**目录下, 通过在Linux的``.bashrc``增加如下一行代码
来添加环境变量。

~~~bash
export PATH=~/NucleiStudio/toolchain/gcc/bin:~/NucleiStudio/toolchain/openocd/bin:$PATH
~~~

或者在ENV工具命令行中运行

~~~bash
export PATH=~/NucleiStudio/toolchain/gcc/bin:~/NucleiStudio/toolchain/openocd/bin:$PATH
~~~

**注意**: 对应的RISC-V GCC和OPENOCD的路径请替换成自己安装的路径。

## 烧写及执行

### 驱动设置

驱动安装设置，请参考[Nuclei FPGA开发板介绍](https://nucleisys.com/upload/files/fpga/doc/Nuclei_FPGA_DebugKit_Intro_202012.pdf)

### 编译程序

下载好[RT-Thread](https://github.com/RT-Thread/rt-thread)的代码和[ENV工具](https://www.rt-thread.org/download.html#download-rt-thread-env-tool)以后。

按照ENV工具的教程, 在**rt-thread\bsp\nuclei\nuclei_fpga_eval**目录打开ENV工具命令行。

**注意**: 请确保Nuclei GCC和Nuclei OpenOCD的路径设置正确无误。

1. 运行 ``pkgs --update``来下载最新的依赖的**Nuclei SDK**开发包，修改链接脚本。

   ```c
     .stack ORIGIN(RAM) + LENGTH(RAM) - __TOT_STACK_SIZE (NOLOAD) :
     {
   	...
       PROVIDE( _sp = . );
       PROVIDE( __rt_rvstack = . );//在链接脚本中补充该条语句
     } >RAM AT>RAM
   ```

2. **可选**: 运行 ``menuconfig``来进行内核配置

3. 运行 ``scons -c``清理之前的编译结果

4. 根据你当前评估的Nuclei RISC-V内核情况，修改 ``rtconfig.py``中的``NUCLEI_SDK_CORE``和``NUCLEI_SDK_DOWNLOAD``参数。
   - ``NUCLEI_SDK_CORE``可选的参数为[Supported Nuclei Cores](https://doc.nucleisys.com/nuclei_sdk/develop/buildsystem.html#core)
   - ``NUCLEI_SDK_DOWNLOAD``可选的参数为``ilm``,``flash``或者``flashxip``, 关于该选项的说明参见[Supported Download Modes](https://doc.nucleisys.com/nuclei_sdk/develop/buildsystem.html#download)
   - 假设你手头拿到的Nuclei评估处理器内核为N307(rv32imafc), 想程序运行模式为``flash``,
     则修改``NUCLEI_SDK_CORE``为``n307``, ``NUCLEI_SDK_DOWNLOAD``为``flash``.

5. 修改完对应的``rtconfig.py``参数配置并保存后，运行 ``scons``来进行代码的编译

### 下载程序

在保证程序能够正常编译后, 在相同ENV终端执行``scons --run upload``进行代码的下载。

正常下载的输出如下:

~~~
scons: Reading SConscript files ...
Supported downloaded modes for board nuclei_fpga_eval are ('ilm', 'flash', 'flashxip'), chosen downloaded mode is ilm
Upload application rtthread.elf using openocd and gdb
riscv-nuclei-elf-gdb rtthread.elf -ex "set remotetimeout 240"                     -ex "target remote | openocd --pipe -f D:/workspace/Sourcecode/rt-thread/bsp/nuclei/nuclei_fpga_eval/packages/nuclei_sdk-latest/SoC/demosoc/Board/nuclei_fpga_eval/openocd_demosoc.cfg"
              --batch -ex "monitor halt" -ex "monitor flash protect 0 0 last off" -ex "load"                     -ex "monitor resume" -ex "monitor shutdown" -ex "quit"
D:\Software\Nuclei\gcc\bin\riscv-nuclei-elf-gdb.exe: warning: Couldn't determine a path for the index cache directory.
Nuclei OpenOCD, i386 Open On-Chip Debugger 0.10.0+dev-g11f0cf429 (2020-07-15-04:09)
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
rt_list_insert_before (n=0xdeadbeef, l=0x90000f80 <timer_thread_stack+464>) at D:\workspace\Sourcecode\rt-thread\include/rtservice.h:79
79          n->next = l;
cleared protection for sectors 0 through 63 on flash bank 0

Loading section .init, size 0x284 lma 0x80000000
Loading section .text, size 0xb30a lma 0x800002c0
Loading section .rodata, size 0x3248 lma 0x8000b5d0
Loading section .data, size 0x340 lma 0x8000e818
Start address 0x80000198, load size 60182
Transfer rate: 48 KB/sec, 10030 bytes/write.
shutdown command invoked
A debugging session is active.

        Inferior 1 [Remote target] will be detached.

Quit anyway? (y or n) [answered Y; input not from terminal]
[Inferior 1 (Remote target) detached]
~~~

下载程序之后, 连接**串口(115200-N-8-1)**, 可以看到 RT-Thread 的输出信息:

> 最新发布出去的评估Bit一般都是16MHz, 串口工作在115200bps下串口读取可以正常工作.

```
initialize rti_board_start:0 done

 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Apr 23 2020
 2006 - 2020 Copyright by rt-thread team
do components initialization.
initialize rti_board_end:0 done
initialize dfs_init:0 done
initialize libc_system_init:0 done
initialize finsh_system_init:0 done
msh />
```

在串口终端(我这里使用的是TeraTerm)输入``ps``即可查看当前线程工作情况:

~~~
msh />ps
thread   pri  status      sp     stack size max used left tick  error
-------- ---  ------- ---------- ----------  ------  ---------- ---
serrxsim   5  suspend 0x00000134 0x0000018c    77%   0x00000005 000
tshell    20  running 0x000002b0 0x00001000    17%   0x00000005 000
tidle0    31  ready   0x00000164 0x0000018c    89%   0x0000000b 000
timer      4  suspend 0x00000120 0x00000200    56%   0x00000009 000
msh />
~~~

### 调试程序

在保证程序编译成功后, 在相同ENV终端执行``scons --run debug``进行代码在命令行下进行GDB调试。

正常的调试输出如下:

~~~
scons: Reading SConscript files ...
Supported downloaded modes for board nuclei_fpga_eval are ('ilm', 'flash', 'flashxip'), chosen downloaded mode is ilm
Debug application rtthread.elf using openocd and gdb
riscv-nuclei-elf-gdb rtthread.elf -ex "set remotetimeout 240"                     -ex "target remote | openocd --pipe -f D:/workspace/Sourcecode/rt-thread/bsp/nuclei/nuclei_fpga_eval/packages/nuclei_sdk-latest/SoC/demosoc/Board/nuclei_fpga_eval/openocd_demosoc.cfg"
D:\Software\Nuclei\gcc\bin\riscv-nuclei-elf-gdb.exe: warning: Couldn't determine a path for the index cache directory.
GNU gdb (GDB) 8.3.0.20190516-git
Copyright (C) 2019 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=i686-w64-mingw32 --target=riscv-nuclei-elf".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from rtthread.elf...
Remote debugging using | openocd --pipe -f D:/workspace/Sourcecode/rt-thread/bsp/nuclei/nuclei_fpga_eval/packages/nuclei_sdk-latest/SoC/demosoc/Board/nuclei_fpga_eval/openocd_demosoc.cfg
Nuclei OpenOCD, i386 Open On-Chip Debugger 0.10.0+dev-g11f0cf429 (2020-07-15-04:09)
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
0x0000000080000e80 in rt_thread_idle_entry (parameter=<optimized out>)
    at D:\workspace\Sourcecode\rt-thread\src\idle.c:253
253                     idle_hook_list[i]();
(gdb) load
Loading section .init, size 0x284 lma 0x80000000
Loading section .text, size 0xb30a lma 0x800002c0
Loading section .rodata, size 0x3248 lma 0x8000b5d0
Loading section .data, size 0x340 lma 0x8000e818
Start address 0x80000198, load size 60182
Transfer rate: 49 KB/sec, 10030 bytes/write.
(gdb) b main
Breakpoint 1 at 0x800002c0: file applications\main.c, line 35.
(gdb) c
Continuing.

Breakpoint 1, main () at applications\main.c:35
35          board_serial_init();
(gdb) n
rt_thread_exit () at D:\workspace\Sourcecode\rt-thread\src\thread.c:277
277         return rt_current_thread;
(gdb) c
Continuing.
~~~

调试例子参见如下文档:

* https://doc.nucleisys.com/nuclei_sdk/quickstart.html#debug-application

为了更方便的进行调试, 也可以下载**Nuclei Studio**集成开发环境, 创建一个Debug Configuration, 选择编译好的
ELF文件, 然后配置OPENOCD和GDB即可, OPENOCD配置文件路径为**bsp\nuclei\nuclei_fpga_eval\packages\nuclei_sdk-latest\SoC\demosoc\Board\nuclei_fpga_eval\openocd_demosoc.cfg**


## 驱动支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | 蜂鸟开发板载串口是UART0 |

**注:**

- 适配RT-Thread的驱动框架的代码在 [../libraries/demosoc/HAL_Drivers](../libraries/demosoc/HAL_Drivers)目录下。
- 如果有开发者想适配更多的驱动, 请在对应目录下增加驱动适配支持。
- 目前串口读取功能在主频为8MHz情况下需要工作在57600bps, 目前发布的Bit一般都是16Mhz
- 目前串口读取没有采用中断的方式进行，而是采用单独的任务来读取，等中断信号接入后可以直接中断方式读取

## 联系人信息

维护人:

- [fanghuaqi](https://github.com/fanghuaqi)

