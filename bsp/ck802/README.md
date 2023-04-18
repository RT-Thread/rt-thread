CK802

## 简介

CK802是杭州中天微系统有限公司自主开发的极低功耗、极低成本嵌入式CPU核产品，它以8位CPU的成本获得32位CPU的运行效率与性能。 BSP基于中天微提供的一块FPGA开发板完成。

| 介绍 | 描述 |
| ---- | ---- |
| 主CPU平台 | CK802 |
| 最高频率 | 600MHz |
| SRAM | 128K |
| FLASH | 256K |

## 编译说明

CK802板级包支持CDK集成开发环境和scons编译。使用的编译器是csky-abiv2-elf-toolchain。

| IDE/编译器 | 已测试版本 |
| ---------- | --------- |
| CDK | CDK 1.6.0 |
| GCC | (C-SKY Tools V2.10.00(Minilibc), ABIV2, B20161206) 4.5.1 |

使用scons编译，需要指定环境变量RTT_EXEC_PATH为正确的编译器路径，例如：

Windows：

```shell
RTT_EXEC_PATH=r'D:\c-sky\CSKY\MinGW\csky-abiv2-elf-toolchain\bin'
```

Linux：

```shell
RTT_EXEC_PATH=r'/opt/csky-abiv2-elf-tools-x86_64-minilibc-20161211/bin'
```

或者通过`scons --exec-path="GCC工具链路径"`命令，在指定工具链位置的同时直接编译，推荐使用该方法。

## BSP使用

### CDK
#### 编译仿真
打开project.cdkproj工程，点击菜单栏的`Project->Build Active Project`进行编译，编译完成后点击`Debug->Start/Stop Debugger`，就可以进入仿真。点击`Debug->Continue Debugger`全速运行。
#### 更新工程
在需要添加或者删除组件的时候，可以使用`menuconfig`进行配置。配置完成后输入`scons --target=cdk`更新工程
### Scons

#### 编译

配置好环境变量`RTT_EXEC_PATH`后，使用[env工具](https://www.rt-thread.org/download.html#download-rt-thread-env-tool)，可以在console下进入到bsp目录中，运行以下命令就可以编译该BSP：

```
scons
```

或者通过 `scons --exec-path="GCC工具链路径"` 命令，在指定工具链位置的同时直接编译。

#### 仿真

Windows平台打开CSkyDebugServer.exe，该软件会连接到仿真器并且提供一个gdb server。使用DebugServerConsole.exe在命令行下进行调试。

Linux平台使用CSkyDebugServer.elf来连接仿真器，使用DebugServerConsole.exe在命令行下进行调试。

### 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

```
\ | /
- RT -     Thread Operating System
 / | \     3.0.4 build Jun  5 2018
 2006 - 2018 Copyright by rt-thread team
msh >
```

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  | 备注 |
| ------ | ----  | ------ |
| UART | 支持 | UART 1 |


## 5. 联系人信息

维护人：

- [tanek](https://github.com/TanekLiang)
