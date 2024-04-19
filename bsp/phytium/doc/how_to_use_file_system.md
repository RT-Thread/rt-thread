# 如何使用 RT-Thread 文件系统

- 文件系统是开发者最常用的操作系统功能之一，RT-Thread 中很多功能也依赖文件系统完成，后面以 SD 卡作为文件系统介质，介绍一下 RT-Thread 中文件系统的制作和使用

- 飞腾派如果固件在 SD 卡中，不适用于本文档，可以参考[飞腾派SD文件系统](./use_phytium_pi_sd_image.md)

## 配置 SD 驱动

- 打开配置 BSP_USING_SDIF，使能 SD 驱动
- 打开配置 BSP_USING_SDCARD_FATFS，使能 SD 文件系统
- 根据板子的实际情况选择 SD 控制器，SD0 打开 USING_SDIF0，SD1 打开 USING_SDIF1
- 根据 SD 控制器连接的介质选择，TF 卡或者 eMMC，例如 USE_SDIF1_TF
- 在 mnt_sdcard.c 中指定根目录和 SD 设备
- 进行编译生成镜像

## 识别 SD 设备

- 启动镜像后，输入 list devices，查看 SD 设备是否识别成功

```
msh />list device
device                   type         ref count
---------------- -------------------- ----------
sd10             Block Device         0       --> SD1 的第一个分区
sd1              Block Device         1       --> SD1
sd0              Block Device         1       
zero             Miscellaneous Device 0       
urandom          Miscellaneous Device 0       
random           Miscellaneous Device 0       
null             Miscellaneous Device 0       
e0               Network Interface    1       
SPI3             SPI Bus              0       
SPI2             SPI Bus              0       
SPI1             SPI Bus              0       
SPI0             SPI Bus              0       
PWM6             PWM Device           0       
MIO15            I2C Bus              0       
DC1              Graphic Device       0       
uart1            Character Device     2       
uart0            Character Device     0       
QSPI0            SPI Bus              0       
CAN0             CAN Device           0   
```

## 制作 SD 文件系统

- 如果之前 SD 卡里没有 FAT32 文件系统，自动挂载可能不会成功，需要启动 RT-Thread 后格式化一个 SD 设备，然后 mount 

```
msh />mkfs sd1 / elm
msh />mount sd1 / elm
mount device sd1(elm) onto / ... succeed!
```

- 文件系统制作好后，下次启动会自动挂载成根目录

## 使用 SD 文件系统

- 参考[RT-Thread 的文件系统使用说明](https://www.rt-thread.org/document/api/group___d_f_s.html)