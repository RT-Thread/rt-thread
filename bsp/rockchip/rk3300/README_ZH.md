# RK3300 BSP 介绍

中文页 | [English](./README.md)

## 1. 介绍

### 产品细节

https://www.rock-chips.com/a/cn/product/RK33xilie/index.html

### 支持列表

| 驱动 | 支持情况  | Earlycon |
| ------ | ----  | ----  |
| RK3399Pro | - | - |
| RK3326 | - | - |
| RK3308 | 支持 | earlycon=uart8250,mmio32,0xff0a0000 |
| RK3328 | - | - |
| RK3399 | - | - |

## 2. 编译

使用RT-Thread Smart 专用工具链进行编译:

```plaintext
wget https://github.com/RT-Thread/rt-thread/releases/download/v5.2.0/aarch64-linux-musleabi_for_x86_64-pc-linux-gnu_242520-979be38cba.tar.bz2

sudo tar -xf aarch64-linux-musleabi_for_x86_64-pc-linux-gnu_242520-979be38cba.tar.bz2  -C /opt
```

将工具链下载后,解压至/opt目录。并设置环境变量

```shell
环境变量配置为：
export RTT_CC="gcc"
export RTT_EXEC_PATH="/opt/aarch64-linux-musleabi_for_x86_64-pc-linux-gnu/bin/"
export RTT_CC_PREFIX="aarch64-linux-musleabi-"
export PATH="$RTT_EXEC_PATH:$PATH"
```

进入`rt-thread/bsp/rockchip/rk3300`目录下输入:

```plaintext
scons --menuconfig
```

选择并拉取zlib软件包
![zlib_pack](./figures/zlib_pack.png)

执行一下命令拉取软件包并编译

```shell
source  ~/.env/tools/scripts/pkgs --update

scons
```
