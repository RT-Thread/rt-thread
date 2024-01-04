# AARCH64 工作模式使用

- 当开发者需要基于 Phytium 系列芯片进行开发时，可以从以下几个步骤出发配置芯片

## 1. 准备编译环境

- 创建tools目录，在 tools 目录下下载两个python 脚本，get_toolchain.py 和 ci.py，下载完后给两个脚本添加执行权限

```shell
mkdir tools
cd ./tools
wget https://gitee.com/rtthread/ART-Pi-smart/raw/master/tools/get_toolchain.py
wget https://gitee.com/rtthread/ART-Pi-smart/raw/master/tools/ci.py
chmod +x get_toolchain.py ci.py
```

- 运行 get_toolchain.py 脚本，拉取 aarch64 交叉编译链`aarch64-linux-musleabi_for_x86_64-pc-linux-gnu`

```shell
python3 ./get_toolchain.py aarch64
```

- 注：若拉取aarch64交叉编译链失败，请在网站下载压缩包
```shell
https://github.com/RT-Thread/toolchains-ci/releases/tag/v1.7
```
![aarch64_tools](./figures/aarch64_tools.png)

- 在tools/目录下新建gnu_gcc文件夹，将下载好的压缩包移至该文件夹下，并使用tar命令解压缩
```shell
mkdir gnu_gcc
cd ./gnu_gcc
tar jxvf aarch64-linux-musleabi_for_x86_64-pc-linux-gnu_stable.tar.bz2
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

以上步骤已在ubuntu20.04开发环境测试，在其他开发环境下若无法下载相关脚本，可使用以下链接手动下载

```shell
    get_toolchain.py下载地址
    https://gitee.com/rtthread/ART-Pi-smart/blob/master/tools/get_toolchain.py

    ci.py下载地址
    https://gitee.com/rtthread/ART-Pi-smart/blob/master/tools/ci.py

    当出现以下提示时，可采用以下链接下载 phytium_standalone_sdk_install.py
    "Please refer to the ./README and manual download phytium_standalone_sdk_install.py, place in current folder"
    phytium_standalone_sdk_install.py下载地址
    https://gitee.com/phytium_embedded/phytium-standalone-sdk/blob/Standalone-Sdk_RT-thread/phytium_standalone_sdk_install.py
```


## 2. 如何选择开发板

- 以 E2000Q RT-Smart为例，Linux 环境下，运行 make load_e2000q_demo_rtsmart 加载默认的 rtconfig, 然后输入下列命令，进入 menuconfig 进一步配置

```shell
    scons --menuconfig
```

开发者通过以下选择进行配置

```
Standalone Setting > Board Configuration
```

![](./figures/board_select.png)

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

![rtsmart_config](./figures/rtsmart_config.png)

开发者通过以上配置开启RT-Thread Smart 功能

## 5. 开启SDK中内部调试信息

```shell
    scons --menuconfig
```

开发者通过以下选项开启打印调试信息

![](./figures/debug_info.png)


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

config SDK_DIR
    string
    option env="SDK_DIR"
    default "./libraries/phytium_standalone_sdk"
```

- 输入 menuconfig 和 scons 完成编译

## 9. 将工程导入 RT-Studio

- 在 RT-Studio 使用功能 `RT-Thread Bsp 到工作空间`，导入 8. 中导出的 BSP 工程
- 设置 BSP 工程的交叉编译链后进行后续开发

![](./figures/import_project.png)
