#### 1. 简介

用于 GD32F470 立创开发板配套 RGB LCD 屏幕的驱动，支持触摸。

> **原作者：LCKFB**  
> 本驱动最初由 LCKFB 开发，由 godmial 移植到本BSP。

#### 2. 在 ENV 中的开启  
ps：建议全部开启  
```
Hardware Drivers Config  --->
      Board extended module Drivers --->
                            Enable LCD --->
                                - [*]Enable TLI
                                - [*]Enable SDRAM
                                - [*]Enable TOUCH
                                - [*]Enable GPU
                                - [*]Enable DRAW PANEL EXAMPLE
```

#### 3. 注意事项

1. 如果屏幕出现刷新抖动，触摸屏出现连点的情况，可以尝试在 `libraries\GD32F4xx_Firmware_Library\CMSIS\GD\GD32F4xx\Source\system_gd32f4xx.c` 将时钟值修改为  
   `#define __SYSTEM_CLOCK_240M_PLL_25M_HXTAL       (uint32_t)(240000000)`  
   然后重新编译即可

2. 由于代码格式审查原因，本驱动未包含中文显示函数。但可直接移植官方源码中的中文显示函数进行使用。

3. 为避免 `scons` 命令编译不通过，代码使用了如下代码段以适配不同编译器：
   ```
   #if defined(__CC_ARM) || defined(__ARMCC_VERSION)
   // Keil MDK
   uint16_t ltdc_lcd_framebuf0[800][480] __attribute__((at(LCD_FRAME_BUF_ADDR)));
   #elif defined(__GNUC__)
   // GCC (RT-Thread)
   uint16_t ltdc_lcd_framebuf0[10][10]; // 此行为避免 scons 编译错误而添加
   #endif
     


#### 4. 联系方式  

- 维护：godmial  
- 主页：<https://github.com/godmial>
