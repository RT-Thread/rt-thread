# IMX6ULL板级支持包说明

## 1. 简介

​	IMX6ULL rt-smart 系统由百问网韦东山老师移植提供，作为CortexA7单核800M主频处理器的开发环境，开发板由myir公司提供核心板，百问网公司设计底板外设等资源 是一套专门用于学习的开发板套件，其中开发板介绍可以参考页面  http://download.100ask.org/boards/Nxp/100ask_imx6ull_pro 。

* 当前IMX6ULL开发板对应的硬件特性：

| 硬件 | 描述 |
| -- | -- |
| CPU主频 | CortexA7 800Mhz x1 |
| DDR | 512MB |
| Flash| 4GB Emmc|
| Ethernet | lan8720a，10M/100M |
| Usb  | UsbHost x2       UsbOtg  x1 |
| wifi&bluetooth | rtl8723bu |
| Audio | wm8960 |
| Display | RGB888 LCD x1  HDMI x1 |
| Can | x1 |
| RS485 | x1 |
| AP6216 module | x1 |
| ICM8235 module | x1 |
|GPIO prot | Several |


* 同时开发板有配套的编译移植教程，可以使用浏览器访问此连接进行观看学习    https://www.bilibili.com/video/BV1ti4y1w7VQ



## 2. 编译说明

​	使用浏览器参考此页面 https://www.rt-thread.org/document/site/rt-smart/rt-smart-quickstart/rt-smart-quickstart/  参考官方编译说明文档下载并配置相应的环境。

### 2.1 下载ENV工具

​	在Windows下请下载[env工具](https://www.rt-thread.org/page/download.html)。

### 2.2 下载工具链

请先下载对应的工具链并展开到`rtthread-smart/tools/gnu_gcc`目录：

* [Windows环境](http://117.143.63.254:9012/www/rt-smart/install_arm-linux-musleabi_for_i686-w64-mingw32.zip)
* [Linux环境](http://117.143.63.254:9012/www/rt-smart/install_arm-linux-musleabi_for_x86_64-pc-linux-gnu.tar.bz2)

目录参考如下：

``` bash
rtthread-smart\tools\gnu_gcc\install_arm-linux-musleabi_for_i686-w64-mingw32
```

下载env工具，运行`env.bat`进入命令行。
然后切换到这个代码包根目录rtthread-smart，**运行smart-env.bat**，它会设置一定的环境变量，然后整体的smart开发环境就可以使用了。

```bash
> cd \workspace\rt-smart
> smart-env.bat
```

**注**

此处运行smart-env.bat以设置环境，这步非常重要，它包括编译器设置。同时它也会设置工具链的前缀，可以在env终端下输入`set RTT_CC_PREFIX`命令看看返回结果是否生效：

```bash
> set RTT_CC_PREFIX
RTT_CC_PREFIX=arm-linux-musleabi-
```



## 2.3 获取最新kernel源码并编译

​	参考上述说明配置好编译环境后，我们需要获取最新支持 imx6ull开发板的kernel源码，进入rt-smart目录下,首先移除掉默认的kernel 再使用git命令获取最新的rt-smart  kernel源码.

```
> mv kerenl kernel_bak
> git clone  https://gitee.com/rtthread/rt-thread.git  -b rt-smart kernel
```

​	使用[env工具][2]，可以在console下进入到rt-smart源码 kernel/bsp/imx6ull目录中，运行以下编译命令：

    scons

​	来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin    rtthread.imx文件。需要使用 百问网imx6ull烧写工具  http://wiki.100ask.org/100ask_imx6ull_tool  烧写更新 rtthread.imx 至imx6ull开发板。



## 3. 执行

​	烧写方式请参考 https://www.bilibili.com/video/BV19A411s7f9?p=2  视频进行操作，

​	烧写成功后打开串口输出就可以看到如下启动打印信息了。

```text
 \ | /
- RT -     Thread Smart Operating System
 / | \     5.0.0 build Dec 22 2020
 2006 - 2020 Copyright by rt-thread team
lwIP-2.0.2 initialized!
[I/sal.skt] Socket Abstraction Layer initialize success.
Dir /mnt mount failed!
hello rt-thread
msh />

```

## 4. 联系人信息

维护人：[weidongshan][2]

[1]: http://infocenter.arm.com/help/index.jsp?
[2]: https://gitee.com/weidongshan
