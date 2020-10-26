# BM3803板级支持包

## 1. 简介

BM3803是中国航天科技集团公司第九研究院第七七二研究所推出的基于SPARC V8内核的抗辐射32位处理器
包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| BM3803 |
|CPU| SPARC V8 |
|主频| 50 - 100MHz |
|SRAM | 2MB |

## 2. 编译说明

| 环境 | 说明 |
| --- | --- |
|PC操作系统|Windows|
|编译器|sparc-gaisler-elf-gcc|
|构建工具|scons|
1) 下载源码
```
git clone https://github.com/RT-Thread/rt-thread.git
```
2) 下载编译工具和调试工具
```
下载对应的编译工具链 https://www.gaisler.com/index.php/downloads/compilers
下载对应的调试工具 https://www.gaisler.com/index.php/downloads/debug-tools
```
3) 通过env配置工程
```
打开env工具，并切换到bsp/bm3803目录
输入menuconfig进行配置并保存
```
4) 编译
```
配置rtconfig.py中的EXEC_PATH为对应的编译工具目录
输入scons进行编译
```
如果编译正确无误，会产生rtthread-bm3803.elf、rtthread.bin文件。可以使用rtthread-bm3803.elf进行调试。

5) 调试
```
调试环境配置请参考 https://www.gaisler.com/eclipse/qsg_sw_ide.pdf
```
