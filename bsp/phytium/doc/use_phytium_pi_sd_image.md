# 飞腾派上开发和固化 RT-Thread 程序

> 本文主要介绍如何在飞腾派中进行 RT-Thread 程序的开发和固化

- 飞腾派开发板是一款面向广大工程师和爱好者的开源硬件。主板处理器采用飞腾四核处理器,兼容 ARM v8 指令集,主频最高可达 1.8GHz
- 由于默认系统需要 16G 的空间，推荐使用 32G 的 SD 卡开发 RT-Thread 程序

## 开发和调试程序

- 在开发和调试程序的阶段可以参考 [Usage](../README.md) 编译 RT-Thread 程序，通过网络串口等方式下载到飞腾派的 RAM 中直接运行

## 使用飞腾派 RT-Thread 镜像

- 如果需要固化 RT-Thread 程序镜像在 SD 卡中，并实现开机自启动，可以使用下列的镜像，镜像中包含飞腾派的启动固件、飞腾派OS和一个 RT-Thread 的启动分区

- [镜像下载链接](https://pan.baidu.com/s/1eL2ElKeVBU5GOyvzn2kl-A)，提取码：PIIM 

- 下载之后解压，使用 sdcard-rtthread.img

    ```                            
    -----------------------------------------------------------------------------------
    |                 |                                    |                                  |
    |  64MB (系统镜像) |   16G (Phytium Pi OS 根文件系统)    |    4G (RT-Thread文件系统)        |
    |     （无格式）    |        （ext4格式）                |    （fat32格式）                 |
    ----------------------------------------------------------------------------------
    ```

- Windows 上使用 balenaEtcher 工具烧入一张 SD 卡（>= 32G），镜像的格式如下图所示，由3个分区组成，前 64MB 是二进制无格式的启动镜像，然后 16G 是 Phytium Pi OS 的根文件系统，格式为 ext4，最后 4G 是 RT-Thread 文件系统，格式为 fat32，
 
- 在 linux 系统上，可以使用 dd 命令将镜像写入 SD 卡 (/dev/sdd)

    ```
    sudo dd if=./sdcard-rtthread-4g.img of=/dev/sdd bs=1M count=20000 status=progress
    ```

- SD 卡烧入完成之后插入飞腾派 SD 卡槽，重启飞腾派就会自动进入 RT-Thread 系统，

    ```
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
    739360 bytes read in 206 ms (3.4 MiB/s)
    ## Starting application at 0x80080000 ...

    \ | /
    - RT -     Thread Operating System
    / | \     5.1.0 build Nov  9 2023 09:13:25
    2006 - 2022 Copyright by RT-Thread team
    do components initialization.
    initialize rti_board_end:0 done
    initialize dfs_init:0 done
    initialize rt_work_sys_workqueue_init:0 done
    initialize rt_mmcsd_core_init:0 done
    ```

## 更新飞腾派 RT-Thread 镜像

- 有两种方式可以更新 SD 卡第三个分区中的 RT-Thread 镜像
- 1. 将 SD 卡插入一台能识别第三个分区的电脑 (Ubuntu 系统能识别，Windows 可能不能识别)，直接将 RT-Thread 镜像复制入 SD 卡
- 2. 可以通过 u-boot 上传 RT-Thread 镜像，然后保存在 SD 卡第三个分区中，注意保存文件的大小 (0xc0000)，要超过 tftpboot 加载的文件大小

    ```
    Phytium-Pi#setenv ipaddr 192.168.4.20;setenv serverip 192.168.4.50;setenv gatewayip 192.168.4.1;  
    Phytium-Pi#tftpboot 0x90100000 rtthread_a64.bin 
    ethernet@3200c000: PHY present at 0
    ethernet@3200c000: Starting autonegotiation...
    ethernet@3200c000: Autonegotiation complete
    ethernet@3200c000: link up, 1000Mbps full-duplex (lpa: 0x2800)
    ft sgmii speed 1000M!
    Using ethernet@3200c000 device
    TFTP from server 192.168.4.50; our IP address is 192.168.4.20
    Filename 'rtthread_a64.bin'.
    Load address: 0x90100000
    Loading: #################################################################
            #################################################################
            ###############
            133.8 KiB/s
    done
    Bytes transferred = 739840 (b4a00 hex)
    Phytium-Pi#fatls mmc 0:2
                rtthread-images/
                .Trash-1000/
                ram/
                System Volume Information/

    0 file(s), 4 dir(s)

    Phytium-Pi#fatwrite mmc 0:2 0x90100000 rtthread-images/rtthread_a64.bin 0xc0000
    786432 bytes written in 398 ms (1.9 MiB/s)
    Phytium-Pi#fatls mmc 0:2 rtthread-images
                ./
                ../
    786432   rtthread_a64.bin
    944384   rtsmart_a64.bin
    950828   rtsmart_a32.bin
    722580   rtthread_a32.bin

    4 file(s), 2 dir(s)

    Phytium-Pi#
    ```

## 修改自启动的 RT-Thread 镜像

- 通过在 u-boot 控制台修改 bootcmd，可以指定不同的 RT-Thread 镜像自启动，如下所示，指定启动 RT-Smart 镜像 `rtsmart_a64.bin`

    ```
    Phytium-Pi#printenv bootcmd
    bootcmd=mw 0x32b301a8 0x275;mmc dev 0;mmc read 0x90000000 0x2000 0x10000;bootm 0x90000000#phytium
    Phytium-Pi#setenv bootcmd "fatload mmc 0:2 0x80080000 rtthread-images/rtthread_a64.bin;dcache flush;go 0x80080000;"
    Phytium-Pi#saveenv
    ```


## 切换成 linux 开发模式

- 本文提供的 RT-Thread 开发镜像中，有一个 linux 系统，需要的时候可以修改 bootcmd，切换成自启动 linux 系统

    ```
    Phytium-Pi#setenv bootcmd "mw 0x32b301a8 0x275;mmc dev 0;mmc read 0x90000000 0x2000 0x10000;bootm 0x90000000#phytium"
    Phytium-Pi#saveenv
    Saving Environment to MMC... Writing to MMC(0)... OK
    ```

## 在 RT-Thread 应用中访问 SD 卡分区

- 如前面介绍的，RT-Thread 应用可以使用第二个分区，分区文件系统格式为 FAT32
- 打开配置 BSP_USING_SDCARD_FATFS 后， RT-Thread / RT-Smart 启动过程中会将 SD 卡挂载为根目录，将配置 BSP_USING_SDCARD_PARTITION 设置为 `sd1`，指定第二个分区为 RT-Thread 根目录，启动后创建的文件都会使用这个 SD 分区