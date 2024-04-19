# RT-Thread Smart for i.MX6ULL

这是一份ART-pi smart开发板的BSP，支持smart模式

ART-pi smart采用了米尔科技的imx6ull核心板，硬件由韦东山团队完成，由社区来完成整体的BSP。硬件规格情况如下：

![硬件资源](figures/hw_resources.png)

## 应用列表

-[x] cpp_tc

-[x] hello

-[x] zlib_tc

-[x] smart-fetch

-[x] umailbox

-[x] busybox命令(可通过help查看)

-[x] WIFI

-[x] EMMC读写

下列应用支持ash后才可以使用

-[ ] shm_ping

-[ ]shm_pong

-[ ]webclient

-[ ]webserver  

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

* 从eMMC中加载运行(目前不推荐)

```bash
bootcmd=fatload mmc 1:1 0x80001000 /kernel/rtthread.bin; dcache flush; go 0x80001000
```

* 网络方式启动

```bash
tftp 0x80001000 rtthread.bin
dcache flush
go 0x80001000
```

* 从sd卡启动 (目前推荐)

```bash
fatload mmc 0:1 0x80001000 rtthread.bin; dcache flush; go 0x80001000
```

## 待改进

* 支持ash开机自启动

* 以太网网络问题

* Emmc1、2、3 mkfs失败

* 从emmc启动内核