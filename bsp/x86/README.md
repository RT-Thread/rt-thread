# RT-Thread for x86

这是一份基础的RT-Thread针对x86的版本、移植，主要是能够在qemu中执行。以下说明主要针对Linux的环境，如果是Windows环境，请使用Env工具，同时请自行处理生成iso的方法。

## 编译

编译RT-Thread for x86版本，还需要一份支持newlib的工具链，可以通过以下地址获得：

*[i386-unknown-elf_for_x86_64-pc-linux-gnu_latest.tar.bz2](http://117.143.63.254:9012/www/rt-smart/i386-unknown-elf_for_x86_64-pc-linux-gnu_latest.tar.bz2)

下载后解压，然后在rtconfig.py中配置其中的EXEC_PATH变量

```python
if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = os.getenv('RTT_EXEC_PATH') or 'E:/Program Files/CodeSourcery/Sourcery_CodeBench_Lite_for_IA32_ELF/bin'

```

然后在x86 bsp目录下执行scons命令来编译：

```bash
scons
```

### 配置

RT-Thread for x86的版本也支持menuconfig的配置方式，在Linux下可以使用`scons --menuconfig`的方式进行配置。

因为menuconfig是一份字符界面的配置（Kconfig），在ubuntu下需要安装ncurses5的库

```bash
sudo apt install libncurses5-dev
```

## 运行

在ubuntu下运行，请确保你安装了`qemu-system-i386`，`grub` 以及 `xorriso`软件包：

```bash
sudo apt install qemu-system-x86 grub-common xorriso
```

然后执行`./run.sh`命令可以使用qemu来模拟执行(它也会生成可启动的iso文件)

```bash
~/workspace/rt-thread/bsp/x86$ ./run.sh
xorriso 1.4.8 : RockRidge filesystem manipulator, libburnia project.

Drive current: -outdev 'stdio:bootable.iso'
Media current: stdio file, overwriteable
Media status : is blank
Media summary: 0 sessions, 0 data blocks, 0 data,  135g free
Added to ISO image: directory '/'='/tmp/grub.uLz91i'
xorriso : UPDATE : 578 files added in 1 seconds
Added to ISO image: directory '/'='/home/bernard/workspace/rt-thread/bsp/x86/root'
xorriso : UPDATE : 582 files added in 1 seconds
xorriso : NOTE : Copying to System Area: 512 bytes from file '/usr/lib/grub/i386-pc/boot_hybrid.img'
ISO image produced: 6007 sectors
Written to medium : 6007 sectors at LBA 0
Writing to 'stdio:bootable.iso' completed successfully.


 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Aug 22 2021
 2006 - 2021 Copyright by rt-thread team
Floppy Inc : NEC765B controller  Floppy Type : 2.88MB
hello!
msh />
```

在qemu下可以按Ctrl-A + X退出qemu。
