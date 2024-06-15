# 飞腾派上开发和固化 RT-Thread 程序

> 本文主要介绍如何在飞腾派中进行 RT-Thread 程序的开发和固化

- 飞腾派开发板是一款面向广大工程师和爱好者的开源硬件。主板处理器采用飞腾四核处理器,兼容 ARM v8 指令集,主频最高可达 1.8GHz

## 开发和调试程序

- 在开发和调试程序的阶段可以参考 [Usage](../README.md) 编译 RT-Thread 程序，通过网络串口等方式下载到飞腾派的 RAM 中直接运行

## 使用飞腾派 RT-Thread 镜像

- 如果需要固化 RT-Thread 程序镜像在 SD 卡中，并实现开机自启动，可以使用下列的镜像，镜像中包含飞腾派的启动固件、飞腾派OS和一个 RT-Thread 的启动分区

- [镜像下载链接](https://pan.baidu.com/s/1asc3MdcIh71-fkjS6Rptvw)，提取码：PHYT 

- 下载之后解压，使用 sdcard-rtthread.img

    ```                            
    ------------------------------------------------------
    |                 |                                  |
    |  64MB (系统镜像) |    2G (RT-Thread文件系统)        |
    |     （无格式）   |    （fat32格式）                 |
    -----------------------------------------------------
    ```

- Windows 上使用 balenaEtcher 工具烧入一张 SD 卡，镜像的格式如下图所示，由1个分区组成，前 64MB 是二进制无格式的启动镜像，后面 2G 是 RT-Thread 文件系统，格式为 fat32，
 
- 在 linux 系统上，可以使用 dd 命令将镜像写入 SD 卡 (/dev/sdd)

    ```
    sudo dd if=./sdcard-rtthread-4g.img of=/dev/sdd bs=1M count=20000 status=progress
    ```

- SD 卡烧入完成之后插入飞腾派 SD 卡槽，重启飞腾派就会自动进入 RT-Thread 系统，

    ```
    PHYTIUM MCI: 0, PHYTIUM MCI: 1
    Loading Environment from MMC... OK
    In:    uart@2800d000
    Out:   uart@2800d000
    Err:   uart@2800d000
    Net:   eth0: ethernet@3200c000
    scanning bus for devices...
    SATA link 0 timeout.
    AHCI 0001.0301 32 slots 1 ports 6 Gbps 0x1 impl SATA mode
    flags: 64bit ncq stag pm led clo only pmp pio slum part ccc apst 
    SATA link 0 timeout.
    AHCI 0001.0301 32 slots 1 ports 6 Gbps 0x1 impl SATA mode
    flags: 64bit ncq stag pm led clo only pmp pio slum part ccc apst 
    Hit any key to stop autoboot:  0 
    2740352 bytes read in 578 ms (4.5 MiB/s)
    ## Starting application at 0x80080000 ...

    \ | /
    - RT -     Thread Operating System
    / | \     5.1.0 build Apr  9 2024 09:17:05
    2006 - 2024 Copyright by RT-Thread team
    lwIP-2.1.2 initialized!
    [I/I2C] I2C bus [MIO15] registered
    FXMAC OS Init Success!
    Xmac e0 Initiailized!
    Set netif e0 ip addr!
    [E/drv] Auto negotiation is error.
    FXMAC OS Init Success!
    Xmac e1 Initiailized!
    Set Xmac e1 ip addr!
    Start Xmac NUM0 
    Start Xmac NUM1 
    [I/sal.skt] Socket Abstraction Layer initialize success.
    msh />rt_device_find 0 
    [I/SDIO] SD card capacity 31178752 KB.
    found part[0], begin: 67108864, size: 2.0GB
    [I/mnt.filesystem] sd00 mount to '/'

    msh />ls /
    Directory /:
    System Volume Inform<DIR>                    
    rtthread_a64.bin    2740352                  
    msh />df
    disk free: 1.9 GB [ 4180704 block, 512 bytes per block ]
    msh />
    ```


## 修改自启动的 RT-Thread 镜像

- 通过在 u-boot 控制台修改 bootcmd，可以指定不同的 RT-Thread 镜像自启动，如下所示，指定启动 RT-Smart 镜像 `rtthread_a64.bin`

```
Phytium-Pi#printenv bootcmd
bootcmd=mw 0x32b301a8 0x275;mmc dev 0;mmc read 0x90000000 0x2000 0x10000;bootm 0x90000000#phytium
Phytium-Pi#setenv bootcmd "fatload mmc 0:1 0x80080000 rtthread_a64.bin;dcache flush;go 0x80080000;"
Phytium-Pi#saveenv
```

## 在 RT-Thread 应用中访问 SD 卡分区

- 如前面介绍的，参考 libraries/port/fboard_port/firefly/mnt_sdcard.c，启动后会将 SD 卡的第一个分区（2GB 大小）自动挂载到根目录下

```
[I/SDIO] SD card capacity 31178752 KB.
found part[0], begin: 67108864, size: 2.0GB
[I/mnt.filesystem] sd00 mount to '/'

msh />
msh />ls
Directory /:                   
rtthread_a64.bin    2740352                  
msh />df
disk free: 1.9 GB [ 4180704 block, 512 bytes per block ]
msh />
```

- 如果需要替换 SD 卡中的 RT-Thread 镜像，直接取下 SD 卡插入 Windows/Ubuntu PC 中进行替换即可