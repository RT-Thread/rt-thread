# Kendryte K210板级支持包说明

## 1. 简介

Kendryte K210 是集成机器视觉与机器听觉能力的系统级芯片(SoC)。使用台积电 (TSMC) 超低功耗的 28 纳米先进制程，具有双核64位处理器，拥有较好的功耗性能，稳定性与可靠性。该方案力求零门槛开发，可在最短时效部署于用户的产品中，赋予产品人工智能。

Kendryte K210 定位于AI与IoT市场的SoC，同时是使用非常方便的MCU。

Kendryte中文含义为勘智，而勘智取自勘物探智。这颗芯片主要应用领域为物联网领域，在物联网领域进行开发，因此为勘物；这颗芯片主要提供的是人工智能解决方案，在人工智能领域探索，因此为探智。

* 具备机器视觉能力
* 具备机器听觉能力
* 更好的低功耗视觉处理速度与准确率
* 具备卷积人工神经网络硬件加速器KPU，可高性能进行卷积人工神经网络运算
* TSMC 28nm先进制程，温度范围-40°C到125°C，稳定可靠
* 支持固件加密，难以使用普通方法破解
* 独特的可编程IO阵列，使产品设计更加灵活
* 低电压，与相同处理能力的系统相比具有更低功耗
* 3.3V/1.8V双电压支持，无需电平转换，节约成本

芯片规格包括如下：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| K210 |
|CPU| 双核RV64GC |
|主频| 400MHz |
|片内SRAM| 8MB |
| 外设 | 内嵌AES与SHA256算法加速器 |
| | DVP、JTAG、OTP、FPIOA、GPIO、UART、SPI、RTC、I²S、I²C、WDT、Timer与PWM |

## 2. 编译说明

编译K210，需要先下载K210 BSP以及RT-Thread代码：

    git clone https://github.com/BernardXiong/K210.git
    cd K210
    git submodule init
    git submodule update

    git clone https://github.com/RT-Thread/rt-thread.git
    cd rt-thread
    git checkout -b dev-4.0.x origin/dev-4.0.x

注意，因为RT-Thread整体代码太庞大，所以并未把RT-Thread git repo以一个submodule方式加入到K210 BSP git repo中，
而是需要把RT-Thread代码克隆到K210目录下，并切换到dev-4.0.x分支。

编译推荐使用[env工具][1]，可以在console下进入到`K210`目录中，运行以下命令：

    set RTT_EXEC_PATH=your_toolchains
    scons

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。其中rtthread.bin需要烧写到设备中进行运行。

## 3. 烧写及执行

连接好串口，然后使用[K-Flash](https://kendryte.com/downloads/)工具进行烧写bin文件。

![K-Flash](images/flash.png)

### 3.1 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

![terminal](images/k210.png)

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | 高速UART，用于shell |

## 5. 联系人信息

维护人：[bernard](https://github.com/BernardXiong)

## 6. 注意事项

在进行系统menuconfig配置时，以下项是必选的

| 配置项 | 强制配置值 |
| -----  | --------- |
| Alignment size for CPU architecture data access | 8 |
| The stack size of idle thread | > 1024 |
| the device name for console | "uarths" |
| Set main thread stack size | 4096 |

## 7. 参考

* 芯片[datasheet][2]

  [1]: https://www.rt-thread.org/page/download.html
  [2]: https://s3.cn-north-1.amazonaws.com.cn/dl.kendryte.com/documents/kendryte_datasheet_20180919020633.pdf
