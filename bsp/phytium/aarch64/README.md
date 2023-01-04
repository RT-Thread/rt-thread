<!--
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: README.md
 * Date: 2022-10-17 15:16:12
 * LastEditTime: 2022-10-17 15:16:12
 * Description:  This file is for 
 * 
 * Modify History: 
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
-->

# AARCH64 工作模式使用

- 当开发者需要基于 Phytium 系列芯片进行开发时，可以从以下几个步骤出发配置芯片

## 1. 如何选择芯片

```shell
    scons --menuconfig
```

开发者通过以下选择进行配置

```
Standalone Setting > Board Configuration > Chip 
```

![](./figures/chip_select.png)
![](./figures/phytium_cpu_select.png)

## 2. 如何选择驱动


```shell
    scons --menuconfig
```

开发者通过以下选项进行驱动的使能

```
Hardware Drivers Config > On-chip Peripheral Drivers
```

![](./figures/select_driver.png)


## 3. 开启SDK中内部调试信息


```shell
    scons --menuconfig
```

开发者通过以下选项进行调试信息等级的设置

![](./figures/select_debug_info.png)



## 4. 编译程序

```shell
    scons -c
    scons
```

- 完成编译之后目录下将会生成以下几个文件

```
rtthread_a64.bin
rtthread_a64.elf
rtthread_a64.map
```

## 5. 打包导出工程源代码


- 指定工程名和路径，打包RT-Thread内核和Phytium BSP代码，可以导出一个工程工程
```
python ./export_project.py -n=phytium-a64 -o=D:/proj/rt-thread-e2000/phytium-a64
```

![](./figures/export_project.png)


- 进入打包工程的目录，修改工程根目录 Kconfig 中的路径 BSP_DIR 和 STANDALONE_DIR 
> env 环境中的 menuconfig 不会调用 SConstruct 修改路径环境变量，因此需要手动修改路径

```
config BSP_DIR
    string
    option env="BSP_ROOT"
    default "."

config STANDALONE_DIR
    string
    option env="STANDALONE_DIR"
    default "libraries/standalone"
```

- 输入 menuconfig 和 scons 完成编译


## 6. 将工程导入 RT-Studio

- 在 RT-Studio 使用功能`RT-Thread Bsp 到工作空间`，导入 5. 中导出的 BSP 工程
- 设置 BSP 工程的交叉编译链后进行后续开发

![](./figures/import_project.png)