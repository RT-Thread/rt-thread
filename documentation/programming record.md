

# RTT开发记录

stm32f407vet6

## 日志ulog

```c
#define DBG_TAG     "MAIN"
#define DBG_LVL     DBG_LOG
#include <rtdbg.h>

/*
 * The macro definitions for debug
 *
 * These macros are defined in static. If you want to use debug macro, you can
 * use as following code:
 *
 * In your C/C++ file, enable/disable DEBUG_ENABLE macro, and then include this
 * header file.
 *
 * #define DBG_TAG           "MOD_TAG"
 * #define DBG_LVL           DBG_INFO
 * #include <rtdbg.h>          // must after of DBG_LVL, DBG_TAG or other options
 *
 * Then in your C/C++ file, you can use LOG_X macro to print out logs:
 * LOG_D("this is a debug log!");
 * LOG_I("this is a info log!");
 * LOG_W("this is a warning log!");
 * LOG_E("this is a error log!");
 */
```

## 使用SFUD挂载W25Q128与easyflash

使用sfud挂载W25Q128参考链接：https://blog.csdn.net/sundm75/article/details/106455095?spm=1001.2101.3001.6650.4&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-4.highlightwordscore&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-4.highlightwordscore
RT-Thread：在W25Q128上搭载文件系统:https://blog.csdn.net/weixin_41738023/article/details/113247550

```c
#include <rtthread.h>
#include <spi_flash.h>
#include <spi_flash_sfud.h>
#include "drv_spi.h"

static int rt_hw_spi_flash_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
	/*往总线spi3挂载一个spi30的设备*/
    rt_hw_spi_device_attach("spi3", "spi30", GPIOA, GPIO_PIN_10);
	/*使用SFUD探测 spi30从设备，并将spi30连接的flash初始化为块设备，名称为：W25Q128*/
   if (RT_NULL == rt_sfud_flash_probe("W25Q128", "spi30"))
    {
        return -RT_ERROR;
    };  
    return RT_EOK;
}
/*导出到自动初始化*/
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);
```

![image-20211229091032301](F:\rt-thread\documentation\programming record.assets\image-20211229091032301.png)

![image-20211229091051230](F:\rt-thread\documentation\programming record.assets\image-20211229091051230.png)

![image-20211229091108686](F:\rt-thread\documentation\programming record.assets\image-20211229091108686.png)

![image-20211229091205152](F:\rt-thread\documentation\programming record.assets\image-20211229091205152.png)

SFUD与easyflash 区别：https://blog.csdn.net/h451884098/article/details/118544347

SFUD+FAL+EasyFlash典型场景需求分析:https://www.cnblogs.com/happybirthdaytoyou/p/12303872.html

[RT-Thread 配置片外Flash与EasyFlash组件](https://www.datasheep.cn/44.html):https://www.datasheep.cn/44.html

## 硬件RTC驱动

配置硬件RTC时钟树更新时钟代码。

![image-20211229104447685](F:\rt-thread\documentation\programming record.assets\image-20211229104447685.png)

```c
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}
```

![image-20211229105056067](F:\rt-thread\documentation\programming record.assets\image-20211229105056067.png)

配置Kconfig宏定义

```
config BSP_USING_ONCHIP_RTC
        bool "Enable RTC"
		select RT_USING_RTC
		select RT_USING_LIBC
        default n
```

![image-20211229105120931](F:\rt-thread\documentation\programming record.assets\image-20211229105120931.png)

RTC设备代码参考链接：https://blog.csdn.net/weixin_43810563/article/details/116813301?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.no_search_link&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.no_search_link&utm_relevant_index=2

RTC设备api

```c
//设置rtc日期
/*year：设置的年	month：设置的月	day：设置的日*/
rt_err_t set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day)
//设置rtc时间
/*hour：设置的时	minute：设置的分	second：设置的秒*/
rt_err_t set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second)
//获取当前时间
time_t time(time_t *t
```

RTC设备示例

```c
#include <rtthread.h>
#include <rtdevice.h>
static int rtc_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    time_t now;
    /* 设置日期 */
    ret = set_date(2018, 12, 3);
    if (ret != RT_EOK)
    {
        rt_kprintf("set RTC date failed\n");
        return ret;
    }
    /* 设置时间 */
    ret = set_time(11, 15, 50);
    if (ret != RT_EOK)
    {
        rt_kprintf("set RTC time failed\n");
        return ret;
    }
    /* 延时3秒 */
    rt_thread_mdelay(3000);
    /* 获取时间 */
    now = time(RT_NULL);
    rt_kprintf("%s\n", ctime(&now));

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(rtc_sample, rtc sample);
```



* dynmem_sample  

* event sample			事件最大值？

* semaphore_sample

   static 变量只初始化一次。

* idlehook_sample 	

   钩子函数作用参考https://www.freesion.com/article/7308411124/

* interrupt sample

* mutex_sample

* mailbox_sample



信号量、互斥量、事件集

* 信号量

  以生活中的停车场为例来理解信号量的概念：

  ①当停车场空的时候，停车场的管理员发现有很多空车位，此时会让外面的车陆续进入停车场获得停车位；

  ②当停车场的车位满的时候，管理员发现已经没有空车位，将禁止外面的车进入停车场，车辆在外排队等候；

  ③当停车场内有车离开时，管理员发现有空的车位让出，允许外面的车进入停车场；待空车位填满后，又禁止外部车辆进入。

  在此例子中，管理员就相当于信号量，管理员手中空车位的个数就是信号量的值（非负数，动态变化）；停车位相当于公共资源（临界区），车辆相当于线程。车辆通过获得管理员的允许取得停车位，就类似于线程通过获得信号量访问公共资源。

* 互斥量
  互斥量又叫相互排斥的信号量，是一种特殊的二值信号量。互斥量类似于只有一个车位的停车场：当有一辆车进入的时候，将停车场大门锁住，其他车辆在外面等候。当里面的车出来时，将停车场大门打开，下一辆车才可以进入。

* 事件集

  事件集也是线程间同步的机制之一，一个事件集可以包含多个事件，利用事件集可以完成一对多，多对多的线程间同步。下面以坐公交为例说明事件，在公交站等公交时可能有以下几种情况：

  ①P1 坐公交去某地，只有一种公交可以到达目的地，等到此公交即可出发。

  ②P1 坐公交去某地，有 3 种公交都可以到达目的地，等到其中任意一辆即可出发。

  ③P1 约另一人 P2 一起去某地，则 P1 必须要等到 “同伴 P2 到达公交站” 与“公交到达公交站”两个条件都满足后，才能出发。

  这里，可以将 P1 去某地视为线程，将 “公交到达公交站”、“同伴 P2 到达公交站” 视为事件的发生，情况①是特定事件唤醒线程；情况②是任意单个事件唤醒线程；情况③是多个事件同时发生才唤醒线程。

空闲钩子函数是空闲线程的钩子函数，如果设置了空闲钩子函数，就可以在系统执行空闲线程时，自动执行空闲钩子函数来做一些其他事情，比如系统指示灯、功耗管理、看门狗喂狗、CPU使用率。可以设置4个空闲钩子函数

volatile关键字:如果一个寄存器或者变量表示一个端口或者多个线程的共享数据，就容易出错，所以volatile可以保证对特殊地址的稳定访问。这样修改以后循环条件就不会被优化掉，当值改变的时候系统将会检测到。

优点：防止编译器对代码优化，变量值是直接从变量地址中读取和存储的。缺点： 这种使用过多会导致代码十分庞大。

解释 https://blog.csdn.net/weixin_44363885/article/details/92838607



指针解释：https://www.runoob.com/cprogramming/c-pointers.html

## CmBacktrace工具使用

工具复制到OBJ目录，打开EVN工具，复制run后面参数。如果rtthread.axf找不到头文件，将rt-thread.axf改为rtthread.axf或修改执行名称

![image-20211231153526731](F:\rt-thread\documentation\programming record.assets\image-20211231153526731.png)

![image-20211231141711323](F:\rt-thread\documentation\programming record.assets\image-20211231141711323.png)

补码：https://blog.csdn.net/weixin_38958597/article/details/86631639

