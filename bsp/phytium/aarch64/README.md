# AARCH64 工作模式使用

- 当开发者需要基于 Phytium 系列芯片进行开发时，可以从以下几个步骤出发配置芯片

## 1. 准备编译环境

- 在 aarch64 目录下创建 tools 目录，后续用于存放 RT-Thread 编译工具链

```sh
cd ./aarch64
mkdir tools
```

- 在 tools 目录下下载两个 python 脚本，get_toolchain.py 和 ci.py，下载完后给两个脚本添加执行权限

```shell
cd ./tools
wget https://gitee.com/rtthread/ART-Pi-smart/raw/master/tools/get_toolchain.py
wget https://gitee.com/rtthread/ART-Pi-smart/raw/master/tools/ci.py
chmod +x get_toolchain.py ci.py
```

- 然后运行 get_toolchain.py 脚本，拉取 aarch64 交叉编译链`aarch64-linux-musleabi_for_x86_64-pc-linux-gnu`

```shell
python3 ./get_toolchain.py aarch64
```

> RT-Thread 5.0 后必须使用这个带 musl-libc 的编译链，不能使用`aarch64-none-elf`

- 在 aarch64 目录下下载脚本 smart_env.sh ，然后运行脚本生效环境变量

```shell
cd ./aarch64
wget https://gitee.com/rtthread/ART-Pi-smart/raw/master/smart-env.sh
source ./smart-env.sh aarch64
```

- 如下所示是 aarch64 编译相关的环境变量，运行 scons 前要确保环境变量设置正确

![aarch64_env](./figures/aarch64_env.png)

## NOTE

- 请使用ubuntu20.04 开发环境进行上述操作，其他开发环境没有进行测试

## 2. 如何选择芯片

- 以 E2000Q RT-Smart为例，Linux 环境下，运行 make load_e2000q_rtsmart 加载默认的 rtconfig, 然后输入下列命令，进入 menuconfig 进一步配置，

```shell
    scons --menuconfig
```

开发者通过以下选择进行配置

```
Standalone Setting > Board Configuration > Chip 
```

![](./figures/chip_select.png)
![](./figures/phytium_cpu_select.png)

## 3. 如何选择驱动

```shell
    scons --menuconfig
```

开发者通过以下选项进行驱动的使能

```
Hardware Drivers Config > On-chip Peripheral Drivers
```

![](./figures/select_driver.png)

## 4. 如何切换至RT-Thread Smart 工作模式

```shell
 scons --menuconfig
```

![1682474861110](./figures/1682474861110.png)

开发者通过以上配置开启RT-Thread Smart 功能

## 5. 开启SDK中内部调试信息

```shell
    scons --menuconfig
```

开发者通过以下选项进行调试信息等级的设置

![](./figures/select_debug_info.png)

## 6. 编译程序

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

## 7. 启动镜像程序

- 可以用串口通过 XMODEM 协议将 bin/elf 文件上传到开发板，然后启动，

- 如果使用 SD-1 控制器

```
mw.l 0x32b31178 0x1f
```

- 首先在 Phytium 开发板上输入，上传 bin 文件

```
loadx 80080000
```

![](./figures/ymodem_upload.png)

- 加载 bin 文件完成后，输入下列命令启动

```
go 80080000
```

> RT-Smart 模式下，64 位不能用 bootelf 启动 elf 文件

## 8. 打包导出工程源代码

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

## 9. 将工程导入 RT-Studio

- 在 RT-Studio 使用功能 `RT-Thread Bsp 到工作空间`，导入 5. 中导出的 BSP 工程
- 设置 BSP 工程的交叉编译链后进行后续开发

![](./figures/import_project.png)
