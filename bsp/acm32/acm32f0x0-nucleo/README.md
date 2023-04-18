# acm32f0x0板级支持包

## 1. 简介

ACM32F0x0芯片是上海爱信诺航芯电子科技有限公司(后续简称上海航芯)一系列支持多种低功耗模式的通用MCU。包括如下硬件特性：

|--------------------------|--------------------|
|         硬件             |         描述       |
| -------------------------|--------------------|
|芯片型号                  | ACM32F0X0系列      |
|CPU                       | ARM Cortex-M0      |
|主频                      | 64MHz              |
|片内SRAM                  | 32K                |
|片内Flash                 | 128K               |
|--------------------------|--------------------|

具体型号及资源请参考上海航芯官方网站[ACM32F0](www.aisinochip.com/index.php/product/child1/id/217.html)。

## 2. 编译说明

推荐使用[env工具][1]，可以在console下进入到`bsp/acm32f0x0-nucleo`目录中，运行以下命令：

`scons`

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。其中rtthread.bin需要烧写到设备中进行运行。

也可以通过`scons --target=iar`或`scons --target=mdk5`生成IAR或是keil工程，再使用相应的工具进行编译。

## 3. 烧写及执行

开发板的使用请参考上海航芯官方网站相应型号的[开发工具](www.aisinochip.com/index.php/product/detail/id/25.html)。

### 3.1 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

## 4. 驱动支持情况及计划

| **片上外设**  | **支持情况** |               **备注**                |
| ------------- | ------------ | ------------------------------------- |
| GPIO          |     支持     | PA0, PA1... PD15 ---> PIN: 0, 1...63  |
| UART          |     支持     |              UART1/UART2              |
| LED           |     支持     |              LED1                     |
| WDT           |     支持     |              WDT/IWDT                 |
| ADC           |     支持     |                                       |

## 5. 联系人信息

维护人：AisinoChip < xiangfeng.liu@aisinochip.com >

## 6. 参考

* 板子[数据手册][2]
* 芯片[数据手册][3]

  [1]: https://www.rt-thread.org/download.html#download-rt-thread-env-tool
  [2]: www.aisinochip.com/index.php/product/detail/id/32.html
  [3]: www.aisinochip.com/index.php/product/detail/id/32.html
