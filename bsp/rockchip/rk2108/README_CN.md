# Rockchip RK2108 BSP说明

---

**目录**

[TOC]

---

## 简介

本文档为Rockchip RK2108 （ARM Cortex-M4F with Cache）的BSP说明。目录结构如下：

```shell
bsp/rockchip
|-- common
|   |-- drivers                     # RT-Thread OS适配层通用驱动
|   |-- rk_hal                      # Rockchip HAL 硬件抽象层实现
|   |   |-- lib
|   |   |   |-- bsp                 # 芯片相关的初始化和功能实现
|   |   |   |-- CMSIS               # 标准CMSIS库
|   |   |   `-- hal                 # HAL 通用驱动
|-- rk2108
|   |-- application                 # 应用程序
|   |-- board                       # 板级支持
|   |   |-- common                  # 通用板级支持
|   |   `-- rk2108_evb              # rk2108_evb 板级支持
|   |-- driver                      # RK2108 私有驱动目录
|   `-- image                       # 存放打包固件
`-- tools                           # Rockchip 通用工具
```

## 开发流程

### 编译

在bsp/rockchip/rk2108下进行操作。

```shell
cd bsp/rockchip/rk2108
./mkimage.sh
```

### 打包

使用Rockchip工具resource_header_tool和firmware_merger进行固件打包，分区配置文件为setting.ini。固件打包命令在脚本mkimage.sh中一起完成。完成固件打包后能得到Firmware.img。

这里对loader相关文件进行说明：

- rk2108_loader.bin：用于启动引导的loader，将与rtthread.bin一起打包
- rk2108_loader_fake.bin：由于Rockchip固件打包时IDBlock格式要求固定需要两个bin文件，因此在没有外挂psram使用psram.bin的情况下需要增加一个没有实际作用的loader_fake.bin文件。
- rk2108_db_loader.bin：用于固件烧写的loader。

### 下载

保持maskrom按键按下的状态，然后重新上电或者按下reset按键，即可进入maskrom模式。

在Linux环境下，使用Rockchip工具upgrade_tool进行固件升级，脚本命令如下：

```shell
sudo ./upgrade_firmware.sh
```

如果没有sudo权限，请联系管理员修改rule.d，让Rockchip的设备节点有rw权限。请管理员在/etc/udev/rules.d下面创建文件70-usbboot.rules。注意，不同的系统版本70-usbboot.rules文件命名的前缀数字不同。

```shell
cd /etc/udev/rules.d
sudo touch 70-usbboot.rules
```

在70-usbboot.rules文件中增加以下内容，其中“2207”为Rockchip USB设备的VID。

```shell
SUBSYSTEM=="usb", ATTRS{idVendor}=="2207", GROUP="plugdev", MODE="0666", ENV{ID_MM_DEVICE_IGNORE}="1"
```

完成以上修改后，普通用户使用Rockchip工具upgrade_tool进行固件升级，脚本命令如下：

```shell
./upgrade_firmware.sh
```

在Windows环境下，使用Rockchip工具RKDevTool进行固件升级，首次使用前需要安装驱动程序DriverAssitant。工具获取请联系Rockchip。

## 维护

Steven Liu : steven.liu@rock-chips.com
