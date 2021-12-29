# RTT开发记录

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

SFUD与easyflash 区别：https://blog.csdn.net/h451884098/article/details/118544347

SFUD+FAL+EasyFlash典型场景需求分析:https://www.cnblogs.com/happybirthdaytoyou/p/12303872.html

[RT-Thread 配置片外Flash与EasyFlash组件](https://www.datasheep.cn/44.html):https://www.datasheep.cn/44.html



