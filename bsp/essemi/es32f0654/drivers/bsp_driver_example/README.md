# 外设驱动测试用例

## 1、介绍

这个软件包包含一些外设设备操作的例程。

### 1.1 例程说明

| 文件             | 说明                            |
| ---------------- | ------------------------------- |
| adc_vol_sample.c       | 使用 ADC 设备转换电压数据 |
| can_sample.c | 通过 CAN 设备发送一帧，并创建一个线程接收数据然后打印输出。 |
| hwtimer_sample.c       | 使用 硬件定时器定时 |
| i2c_sample.c     | 使用 i2c 设备进行读写 |
| pm.c | 反复进入不同程度的睡眠。 |
| led_blink_sample.c     |  使用 pin 设备控制 LED 闪烁 |
| pin_beep_sample.c      | 使用 pin 设备控制蜂鸣器 |
| pwm_led_sample.c       | 使用 pwm 设备控制 LED 的亮度 |
| rtc_sample.c           | 使用 rtc 设备设置年月日时分秒信息 |
| spi_sample.c     | 使用 spi 设备进行读写 |
| uart_sample.c          | 使用 serial 设备中断接收及轮询发送模式收发数据 |

### 1.2 依赖

依赖设备管理模块提供的设备驱动。

## 2、如何打开 外设驱动测试用例

使用 外设驱动测试用例 需要在 RT-Thread 的menuconfig中选择它，具体路径如下：

```
Hardware Driver Config --->
    Peripheral Driver test example--->
```

## 3、使用 外设驱动测试用例

在打开 Peripheral Driver test example 后，当进行 BSP 编译时，选择的软件包相关源代码会被加入到 BSP 工程中进行编译。

## 4、注意事项

暂无。

## 5、联系方式 & 感谢

* 维护：[misonyo](https://github.com/misonyo)
* 主页：https://github.com/RT-Thread-packages/peripheral-sample
