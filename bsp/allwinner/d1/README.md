# RT-Thread全志D1移植

全志 D1 是采用玄铁 C906 RV64 处理器的 RISC-V SoC。本 BSP 已在
Sipeed Lichee RV 86 Panel 类 D1 硬件上验证 RT-Smart 启动和交互式
`msh />` shell。

## 硬件配置

- SoC：Allwinner D1
- CPU：T-Head/XuanTie C906 RV64
- 验证板卡：Sipeed Lichee RV 86 Panel 类 D1 板卡
- 控制台：UART0，115200 8N1
- 内核加载地址：`0x45000000`

## 编译环境

- 拉取 RT-Thread Smart的代码仓库 `git clone https://gitee.com/guozhanxin/rtthread-smart.git`

### windows 环境

- 打开 RT-Thread ENV 工具

- 进入 tools 目录 `cd tools`

- 拉取 `riscv64`平台的编译工具 `python get_toolchain.py riscv64`

- 返回上级目录 `cd ..`

- 设置环境变量 `./smart-env.bat`

### ubuntu 环境

- 打开 ubuntu shell 终端

- 进入 tools 目录 `cd tools`

- 拉取 `riscv64`平台的编译工具 `python get_toolchain.py riscv64`

- 返回上级目录 `cd ..`

- 设置环境变量 `source smart-env.sh riscv64`

### 编译环境验证

- 输入：`riscv64-unknown-linux-musl-gcc -v`

## 开发与编译

- windows 下使用 RT-Thread ENV 工具，`menuconfig` 配置工程，`scons` 编译工程

- Linux 下进入本 BSP 目录，设置包含
  `riscv64-unknown-linux-musl-` 工具链的目录后编译：

```sh
cd bsp/allwinner/d1
RTT_EXEC_PATH=/path/to/riscv64-musl-toolchain/bin scons -j
sh generateimg.sh
```

生成的 `rtthread.img` 是加载地址和入口地址均为 `0x45000000` 的
U-Boot legacy kernel image。

## 下载验证

- 编译完后，通过：mkimage 生成 img 镜像文件，这个img 镜像文件可以使用 U-boot 引导启动

- 启动方式一般有：SD卡启动、NandFlash启动、网络引导启动

- windows 下使用全志的：`AllwinnertechPhoeniSuitRelease20201225`

- 可以使用 xfel 工具进行烧写NandFlash

## 运行效果

```c
## Booting kernel from Legacy Image at 45000000 ...
   Image Name:   
   Image Type:   RISC-V Linux Kernel Image (uncompressed)
   Data Size:    249576 Bytes = 243.7 KiB
   Load Address: 45000000
   Entry Point:  45000000
   Verifying Checksum ... OK
[01.861]
Starting kernel ...
heap: [0x45077bb0 - 0x48277bb0]
 \ | /
- RT -     Thread Smart Operating System
 / | \     5.0.0 build Jun 18 2022
 2006 - 2020 Copyright by rt-thread team
file system initialization done!
Hello RISC-V
msh />

```

## 参考文档

- [https://club.rt-thread.org/ask/article/389ac36250b57737.html](https://club.rt-thread.org/ask/article/389ac36250b57737.html)





