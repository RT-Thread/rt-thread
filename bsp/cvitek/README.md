# cvitek bsp


## 支持芯片
针对算能系列 RISC-V 芯片的 bsp，包括：

- 大核

| 芯片名称 | 芯片架构 | 内存大小 | 默认日志串口 | 备注 |
| ------- | ------- |------- | -------- | -------- |
| cv180x | RISC-V C906 | 64MByte | uart0 | 默认开启 MMU，运行 RT-SMART 模式 |

- 小核

| 目录 | 内存大小 | 默认日志串口 | 备注 |
| ---- | ------- | -------- | --- |
| c906-little | 与大核共享 | uart1 | 无 MMU，运行 RT-Thread 标准 |

> 注：异构芯片需单独编译每个核的 OS

## 编译
异构芯片需单独编译每个核的 OS，在大/小核对应的目录下，依次执行:

1. 开发板选择
Linux平台下，可以先执行：
```shell
$ scons --menuconfig
```

选择当前需要编译的目标开发板类型
```shell
Board Type (milkv-duo)  --->
    ( ) milkv-duo
    (X) milkv-duo256m
```

2. 编译
```shell
$ scons
```

## 运行

编译成功后，会在 `bsp/cvitek/output` 对应开发板型号目录下自动生成 `fip.bin` 和 `boot.sd` 文件，其中大核运行文件在 `boot.sd` 中，小核的运行文件在 `fip.bin` 中。

1. 将 SD 卡分为 2 个分区，第 1 个分区用于存放 bin 文件，第 2 个分区用于作为数据存储分区，分区格式为 `FAT32`。
2. 将根目录下的 `fip.bin` 和 `boot.sd` 复制 SD 卡第一个分区中。
	- fip.bin：fsbl、 opensbi、uboot、小核运行文件打包后的 bin 文件
	- boot.sd：大核打包后的 bin 文件

## 驱动支持列表

| 驱动 | 支持情况 | 备注              |
| :--- | :------- | :---------------- |
| uart | 支持     | 默认波特率115200 |
| gpio | 支持 |  |
| i2c  | 支持 |  |
| adc | 支持 |  |

## 支持开发板
- milk-v duo: [https://milkv.io/duo](https://milkv.io/duo)
- milk-v duo256m: [https://milkv.io/duo256m](https://milkv.io/docs/duo/getting-started/duo256m)

## FAQ
1. 如遇到不能正常编译，请先使用 `scons --menuconfig` 重新生成配置。

2. 错误：./mkimage: error while loading shared libraries: libssl.so.1.1: cannot open shared object file: No such file or directory

可在 [http://security.ubuntu.com/ubuntu/pool/main/o/openssl](http://security.ubuntu.com/ubuntu/pool/main/o/openssl) 下载 `libssl1.1_1.1.1f-1ubuntu2_amd64.deb` 文件后安装即可解决。
或使用以下命令下载安装:
```shell
$ wget http://security.ubuntu.com/ubuntu/pool/main/o/openssl/libssl1.1_1.1.1f-1ubuntu2_amd64.deb
$ sudo dpkg -i libssl1.1_1.1.1f-1ubuntu2_amd64.deb
```

## 联系人信息

维护人：[flyingcys](https://github.com/flyingcys)

更多信息请参考 [https://riscv-rtthread-programming-manual.readthedocs.io](https://riscv-rtthread-programming-manual.readthedocs.io)