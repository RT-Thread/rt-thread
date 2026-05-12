# RT-Thread for x86

这是一份基础的RT-Thread针对x86的版本、移植，主要是能够在qemu中执行。以下说明主要针对Linux的环境，如果是Windows环境，请使用Env工具，同时请自行处理生成iso的方法。

## 编译

编译RT-Thread for x86版本，还需要一份支持newlib的工具链，可以通过以下地址获得：

* [i386-unknown-elf_for_x86_64-pc-linux-gnu_latest.tar.bz2](http://117.143.63.254:9012/www/rt-smart/i386-unknown-elf_for_x86_64-pc-linux-gnu_latest.tar.bz2)
* [ GCC 15.2.0 w/ Newlib 4.6.0.20260123: https://github.com/atxhua/i686-atxhua-newlib-elf/releases/download/15.2.0/i686-atxhua-newlib-elf-linux.tar.gz ](https://github.com/atxhua/i686-atxhua-newlib-elf/releases/download/15.2.0/i686-atxhua-newlib-elf-linux.tar.gz)


下载后解压，然后配置RTT_EXEC_PATH & RTT_CC_PREFIX 变量
```bash
export RTT_EXEC_PATH='/path/to/i686-atxhua-newlib-elf-linux/bin'
export RTT_CC_PREFIX='i686-atxhua-newlib-elf-'
```

rtconfig.py
```python
if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = os.getenv('RTT_EXEC_PATH') or 'E:/Program Files/CodeSourcery/Sourcery_CodeBench_Lite_for_IA32_ELF/bin'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = os.getenv('RTT_CC_PREFIX') or 'i386-unknown-elf-'
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

然后使用qemu来模拟执行

```bash
$ qemu-system-i386 -M pc -kernel rtthread.elf -nographic

SeaBIOS (version 1.16.3-debian-1.16.3-2)


iPXE (https://ipxe.org) 00:03.0 CA00 PCI2.10 PnP PMM+06FCAE00+06F0AE00 CA00
                                                                               


Booting from ROM..
 \ | /
- RT -     Thread Operating System
 / | \     5.3.0 build May 10 2026 21:25:36
 2006 - 2024 Copyright by RT-Thread team
Floppy Inc : NEC765B controller  Floppy Type : 2.88MB
[I/DBG] root filesystem mounted.
hello!
msh />

```

在qemu下可以按Ctrl-A + X退出qemu。
