## 在 MDK 中使用 FSP

1. 打开 MDK，选择 “Tools -> Customize Tools Menu…”
2. 点击 “new” 图标，添加一条自定义命令: RA Smart Configurator
3. Command 输入工具的安装路径， 点击“…”找到安装路径下的“rasc.exe”文件并选中 (setup_fsp_v3_1_0_rasc_ 安装目录下)
4. Initial Folder 输入参数: $P
5. Arguments 输入参数: --device $D --compiler ARMv6 configuration.xml
6. 点击 OK 保存命令“Tools -> RA smart Configurator”

![img](picture/customize.png)

7. 点击添加的命令打开配置工具：RA Smart Config

![image.png](picture/openrasc.png)

## UART

如何添加一个 UART 端口外设配置？

1. 选择 Stacks 配置页，点击 New Stack 找到 UART。

![image.png](picture/rascuart.png)

2. 配置 UART 参数，因为需要适配 RT-Thread 驱动中使用的命名，所以需要修改命名，设置 **name** 、**channel**  、**callback** 是一致的标号。
![image.png](picture/rascuart1.png)



## GPIO 中断

如何添加一个 IO 中断？

1. 选择引脚编号，进入配置，比如选择 P402 做为中断引脚。

![image-20211019142514276](picture/gpio.png)
  2. 打开 ICU 中断通道 IRQ4

![image-20211019142801323](picture/gpio_irq.png)
  3. 创建 stack 并进入配置。因为需要适配 RT-Thread 驱动中使用的命名，所以需要修改命名，设置 **name** 、**channel**  、**callback** 是一致的标号。选择你希望的触发方式。最后保存配置，生成配置代码。

![image-20211019142910292](picture/icu_stack.png)

![image-20211019143151891](picture/config_irq4.png)

4. 测试中断是否能够成功开启

   ```c
   
   void irq_callback_test(void *args)
   {
       rt_kprintf("\n Irq4 triggered \n");
   }
   
   void icu_sample(void)
   {
       /* 初始化P*/
       rt_uint32_t pin = rt_pin_get("P402");
       rt_kprintf("\n pin number : 0x%04X \n", pin);
       rt_err_t err = rt_pin_attach_irq(pin, PIN_IRQ_MODE_RISING, irq_callback_test, RT_NULL);
       if(RT_EOK != err)
       {
           rt_kprintf("\n attach irq failed. \n");
       }
       err = rt_pin_irq_enable(pin, PIN_IRQ_ENABLE);
       if(RT_EOK != err)
       {
           rt_kprintf("\n enable irq failed. \n");
       }
   }
   MSH_CMD_EXPORT(icu_sample, icu sample);
   ```

## WDT

1. 创建 WDT 

![image-20211019152302939](picture/wdt.png)

2. 配置 WDT，需要注意在 RT-Thread 中只是用了一个 WDT 设备，所以没有对其进行编号，如果是新创建的 WDT 设备需要注意 name 字段，在驱动中默认使用的是 `g_wdt` 。

![image-20211019152407572](picture/wdt_config.png)

3. [如何在 ENV 中打开 WDT](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/programming-manual/device/watchdog/watchdog) 

## RTC

1. 添加 RTC 设备

![image-20211019152536749](picture/rtc.png)

2. 配置 RTC，需要注意在 RT-Thread 中只是用了一个 RTC 设备，所以没有对其进行编号，如果是新创建的 RTC 设备需要注意 name 字段，在驱动中默认使用的是 `g_rtc` 。

![image-20211019152627412](picture/rtc_config.png)

3.  [如何在 ENV 中打开 RTC](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/programming-manual/device/rtc/rtc) 