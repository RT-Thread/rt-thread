# c906_little bsp
该 bsp 为 cv18xx 系列处理器中的协处理器，采用 RISCV C906 @ 700Mhz。
特性：
- 无 MMU   
- 集成浮点运算单元 (FPU)

## Toolchain 下载
下载 `riscv64-unknown-elf-gcc` 的工具链: [https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz](https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz)

> 注：
当前 bsp 只支持 Linux 编译

正确解压后，在`rtconfig.py`中将 `riscv64-unknown-elf-gcc` 工具链的本地路径加入 `EXEC_PATH` 或通过 `RTT_EXEC_PATH` 环境变量指定路径。

```shell
$ export RTT_EXEC_PATH=/opt/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1/bin
```

## 编译
1. 依赖安装

```shell
$ sudo apt install -y scons libncurses5-dev wget flex bison
```


2. Linux平台下，先执行：
```shell
$ scons --menuconfig
```

选择当前需要编译的目标开发板类型
```shell
Board Type (milkv-duo)  --->
    ( ) milkv-duo
    (X) milkv-duo256m
```

它会自动下载 env 相关脚本到 ~/.env 目录，然后执行
```shell
$ source ~/.env/env.sh
$ pkgs --update
```
更新完软件包后，执行 `scons -j10` 或 `scons -j10 --verbose` 来编译这个板级支持包。或者通过 `scons --exec-path="GCC工具链路径"` 命令，在指定工具链位置的同时直接编译。编译正确无误，会产生rtthread.elf 文件。

编译完成后脚本自动调用 `combine-fip.sh` 脚本进行打包，并生成 `fip.sd`, 该文件即为 SD 卡启动的 c906_little 文件。

第一次调用 `combine-fip.sh` 脚本时会自动下载打包需要的 `opsbsbi`、`fsbl`、`uboot` 等相关文件至 `bsp/cvitek/cvitek_bootloader` 目录，请耐心等待。

下载完成后会自动解压、编译，后续再次编译同一类型开发板只会调用相关文件打包合成 `fip.bin`。如需手工编译相关 `cvitek_bootloader` 文件，可在 `bsp/cvitek/cvitek_bootloader` 目录下执行 `bash build.sh lunch` 选择对应的开发板编译。

## 运行
1. 将 SD 卡分为 2 个分区，第 1 个分区用于存放 bin 文件，第 2 个分区用于作为数据存储分区，分区格式为 `FAT32`。
2. 将根目录下的 `fip.bin` 和 `boot.sd` 复制 SD 卡第一个分区中。后续更新固件只需要复制 `fip.sd` 文件即可。
其中：
- fip.bin：fsbl、 opensbi、 uboot、c906_little 打包后的 bin 文件
- boot.sd：大核打包后的 bin 文件

更新完 `fip.sd` 后， 重新上电可以看到串口的输出信息：
```shell
HW_HEAP_BEGIN:83f74dc0 RT_HW_HEAP_END:84000000 size: 569920

 \ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Jan 27 2024 22:45:49
 2006 - 2022 Copyright by RT-Thread team
Hello, RISC-V!
msh />
```