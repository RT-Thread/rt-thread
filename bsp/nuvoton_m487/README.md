# NuMaker-PFM-M487

## 1. 简介

核心板板载主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| M487JIDAE |
|CPU| ARM Cortex-M4 |
|主频| 192MHz |
|片内SRAM| 160kB |
|片内Flash| 512kB |
|SPI FLASH| W25Q32 |
|PHY| IP101GR |
|Audio Codec| NAU88L25 |


## 2. 编译说明

板级包支持MDK4工程生成、GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| MDK4       | 4.73                         |
| GCC        | GCC 5.4.1 20160919 (release) |

使用MDK4打开工程需要安装Nu-Link_Keil_Driver

## 3. 烧写及执行

连接好串口，可以使用115200-N-8-1的配置方式连接到设备上。设备使用的串口引脚是：`[Tx:PB13  Rx:PB12]`

当正确编译产生出rtthread.bin映像文件后，可以使用Nu-link或者JLINK下载

### 3.1 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息

如挂载根目录失败，需要格式化SPI FLASH，请输入`mkfs -t elm flash0`

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0|
| EMAC | 支持 | EH0|
| QSPI | 支持 | QSPI0|
| SPIFLASH | 支持 | W25Q32 |


### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| PH0 | LED_R |
| PH1 | LED_Y |
| PH2 | LED_G |
| PG15 | KEY2 |
| PF11| KEY3 |

## 5. 联系人信息

维护人：[bluebear233](https://github.com/bluebear233)

## 6. 参考

* 板子[数据手册][1]
* 芯片[数据手册][2]

  [1]: http://www.nuvoton.com/resource-files/UM_NuMaker-PFM-M487_User_Manual_EN_Rev1.00.pdf
  [2]: http://www.nuvoton.com/resource-files/TRM_M480_Series_EN_Rev1.01.pdf