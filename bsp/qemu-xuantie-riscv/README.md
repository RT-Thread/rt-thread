# XUANTIE QEMU SYSTEM RISC-V BSP


本工程是玄铁 RISC-V 系列 IP QEMU System RISC-V 模拟器运行。

## 支持情况汇总
当前支持 IP 列表：

| IP | 支持情况 | toolchain |
| --- | --- | --- |
| c910 | 支持 M 态下运行 rt-thread | riscv64-unknown-elf-gcc |



## 编译与运行

### Toolchain 下载
`riscv64-unknown-elf-gcc` 下载地址  [https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz](https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz)

正确解压后，在`rtconfig.py`中将 `riscv64-unknown-elf-gcc` 工具链的本地路径加入 `EXEC_PATH` 或通过 `RTT_EXEC_PATH` 环境变量指定路径。

```shell
$ export RTT_CC_PREFIX=riscv64-unknown-elf-
$ export RTT_EXEC_PATH=/opt/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1/bin
```

### xuantie qemu 下载
xuantie qemu 下载地址：[https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1732784413896/Xuantie-qemu-x86_64-Ubuntu-20.04-V5.0.4-B20241127-1130.tar.gz](https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1732784413896/Xuantie-qemu-x86_64-Ubuntu-20.04-V5.0.4-B20241127-1130.tar.gz)

将 qemu 解压后的目录加入 `PATH` 环境变量。

可运行如下命令检测 qemu 是否正常。
```shell
$ qemu-system-riscv64 --version
QEMU emulator version 8.2.94 (cskysim V5.0.4 B-20241127)
Copyright (c) 2003-2024 Fabrice Bellard and the QEMU Project developers
```


### 编译
进入对应 IP 名目录下，执行 scons 命令即可。

编译完成后会生成 `rtthread.elf` 文件。

## 运行
编译完成后，运行对应 IP 名目录下的 qemu-nographic.sh 脚本即可。

```shell
$ cd c910
$ ./qemu-nographic.sh
RT_HW_HEAP_BEGIN:500220d0 RT_HW_HEAP_END:500ffff8 size: 909096

 \ | /
- RT -     Thread Operating System
 / | \     5.2.0 build Dec 29 2024 19:23:42
 2006 - 2024 Copyright by RT-Thread team
Hello, RISC-V!
msh />
```



## 参考链接

1. 玄铁官方： [https://www.xrvm.cn](https://www.xrvm.cn)