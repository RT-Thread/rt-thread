#### 1.简介

用于GD32F470立创开发板配套RGB LCD屏幕的驱动，支持触摸。
#### 2.在 ENV 中的开启
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
#### 3.注意事项
1.如果屏幕出现刷新抖动，触摸屏出现连点的情况，可以尝试在 `libraries\GD32F4xx_Firmware_Library\CMSIS\GD\GD32F4xx\Source\system_gd32f4xx.c`将时钟值修改为
`#define __SYSTEM_CLOCK_240M_PLL_25M_HXTAL       (uint32_t)(240000000)`

#### 4.联系方式

- 维护：godmial
- 主页：<https://github.com/godmial>
