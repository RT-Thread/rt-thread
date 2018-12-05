# STM32 系列 BSP 制作规范

本文档为 RT-Thread STM32 系列 BSP 制作规范 ，规定了 STM32 BSP 制作需要遵守的准则和需要实现的基本功能。方便开发者快速完成 BSP 的制作。同时，开发人员在 BSP 制作完成后，也可以使用本规范进行检查。

## BSP 制作规范

STM32 BSP 的制作规范分为 3 个方面：工程配置，ENV 配置和 IDE 配置。下面将分别详细介绍这 3 个方面需要准守的准则。

### 工程配置

- Main 函数执行的功能要统一
  - 如果有 LED 的话，main函数里只放一个 LED 1HZ 闪烁的程序
  - LED_PIN 定义在board.h，初始化在 board.c 完成
- 在 `rt_hw_board_init` 中需要完成堆的初始化：调用 `rt_system_heap_init`
- 默认只初始化 GPIO 驱动和 FinSH 对应的串口驱动，不使用 DMA
- 当使能板载外设驱动时，应做到不需要修改代码就能编译下载使用
- 代码注释风格要统一

### ENV 配置

- 系统心跳统一设置为 1000（宏：RT_TICK_PER_SECOND）
- BSP 中需要打开调试选项中的断言（宏：RT_DEBUG）
- 系统空闲线程栈大小统一设置为 256（宏：IDLE_THREAD_STACK_SIZE）
- 开启组件自动初始化（宏：RT_USING_COMPONENTS_INIT）
- 需要开启 user main 选项（宏：RT_USING_USER_MAIN）
- 默认关闭 libc（宏：RT_USING_LIBC）
- FinSH 默认只使用 MSH 模式（宏：FINSH_USING_MSH_ONLY）

### IDE 配置

- 使能下载代码后自动运行
- 使能 C99 支持
- 使能 One ELF Setion per Function（MDK）
- keil/iar 生成的临时文件分别放到build下的 keil/iar 文件夹下
- mdk/gcc/iar 生成 bin 文件名字统一成 rtthread.bin