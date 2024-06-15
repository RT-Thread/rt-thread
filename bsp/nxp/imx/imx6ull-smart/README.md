# RT-Thread Smart for i.MX6ULL

这是一份ART-pi smart开发板的BSP，支持smart模式

ART-pi smart采用了米尔科技的imx6ull核心板，硬件由韦东山团队完成，由社区来完成整体的BSP。硬件规格情况如下：

![硬件资源](figures/hw_resources.png)

> ## 当前支持情况
> ### 内核
> * [ ]  rt-thread
> * [x]  rt-smart
> 
> ### 驱动
> * [x]  uart
> * [x]  SPI
> * [x]  GPIO
> * [x]  sdcard
> * [x]  RW007
> * [x]  enet
> * [ ]  usb
> * [x]  emmc
> 
> ### 组件
> * [x]  fat文件系统
> * [x]  LWIP网络协议栈
> * [x]  wlan
> 
> ### 应用
> * [x]  xmake 构建环境
> * [x]  busybox
> * [x]  smart-apps
> * [x]  ash  支持ash开机自启动
> * [x]  emmc 从emmc启动内核、挂载文件系统
> 
> ### 待完善、修复

> * [ ]  信号 信号处理问题修复

 
## 应用编译

参考https://github.com/RT-Thread/userapps.git的README.md搭建xmake编译环境并编译smart应用

生成的应用在userapps/apps/build/rootfs文件夹中，将它们拷贝到sd卡中

## 内核编译

* 注意：请使用xmake下载下来的工具链，工具链具体位置在

```bash
~/.xmake/packages/a/arm-smart-musleabi/211536-3de435f234/f5d0c3febbd2497fa950eb569871a3c0
```

* 更新在线wifi软件包
```bash
 source ~/.env/env.sh 
 pkgs --update
 ```

* 进入到rt-thread/bsp/nxp/imx/imx6ull-smart目录，执行

```bash
scons -j12
```

## 启动内核

* 从eMMC中加载运行

```bash
bootcmd=fatload mmc 1:1 0x80001000 /kernel/rtthread.bin; dcache flush; go 0x80001000
```

* 网络方式启动

```bash
tftp 0x80001000 rtthread.bin
dcache flush
go 0x80001000
```

* 从sd卡启动

```bash
fatload mmc 0:1 0x80001000 rtthread.bin; dcache flush; go 0x80001000
```

## 制作从emmc启动所用映像文件

* 在rt-thread/bsp/nxp/imx/imx6ull-smart/emmc下按照emmc.sh内容进行制作，
  生成物art-pi.img在rt-thread/bsp/nxp/imx/imx6ull-smart/emmc/image/images下

* 使用100ask_imx6ull_flashing_tool.exe工具进行烧写

* 工具获取https://github.com/100askTeam/gui_for_nxp_uuu/blob/master/100ask_imx6ull%E7%83%A7%E5%86%99%E5%B7%A5%E5%85%B7/100ask_imx6ull_flashing_tool.exe
  
* 烧写说明：
  
  * 在烧写软件的基础版，点击更新uboot![alt text](image-1.png)
  
  * 在烧写软件的专业版，烧写制作的映像文件art-pi.img![alt text](image-2.png)
  