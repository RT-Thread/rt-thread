# RK3300 BSP Introduction

[中文页](./README_ZH.md) | English

## 1. Introduction

### Product Details

https://www.rock-chips.com/a/cn/product/RK33xilie/index.html

### Condition

| SoC | Condition | Earlycon |
| ------ | ----  | ----  |
| RK3399Pro | - | - |
| RK3326 | - | - |
| RK3308 | Support | earlycon=uart8250,mmio32,0xff0a0000 |
| RK3328 | - | - |
| RK3399 | - | - |

## 2. Compiling

Use the RT-Thread Smart dedicated toolchain to compile:

```plaintext
wget https://github.com/RT-Thread/rt-thread/releases/download/v5.2.0/aarch64-linux-musleabi_for_x86_64-pc-linux-gnu_242520-979be38cba.tar.bz2

sudo tar -xf aarch64-linux-musleabi_for_x86_64-pc-linux-gnu_242520-979be38cba.tar.bz2 -C /opt
```

After downloading, extract the toolchain to the /opt directory.Then configure your environment variables:

```plaintext
export RTT_CC="gcc"
export RTT_EXEC_PATH="/opt/aarch64-linux-musleabi_for_x86_64-pc-linux-gnu/bin/"
export RTT_CC_PREFIX="aarch64-linux-musleabi-"
export PATH="$RTT_EXEC_PATH:$PATH"
```

Navigate to the rt-thread/bsp/rockchip/rk3300 directory and enter:

```shell
scons --menuconfig
```

Select and pull the zlib package in the menu:
![zlib_pack](./figures/zlib_pack.png)

Then run the following commands to fetch packages and build the project:

```shell
source  ~/.env/tools/scripts/pkgs --update

scons
```
