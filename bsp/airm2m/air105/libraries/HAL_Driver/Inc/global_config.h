/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __GLOBAL_CONFIG_H__
#define __GLOBAL_CONFIG_H__
#ifndef HSE_VALUE
#define HSE_VALUE    ((uint32_t)12000000) /*!< Value of the HSE oscillator in Hz */
#endif
//#define __DEBUG__
#define IRQ_LINE_OFFSET (16)    //如果想要用sys_tick,改成15
#define IRQ_LINE_MAX (52)
#define CORE_TICK_BASE  (1000)
#define HW_TICK_BASE    (48000000)
#define __WDT_TO_MS__   (15000)
#define __FLASH_SECTOR_SIZE__ (0x00001000)
#define __FLASH_PAGE_SIZE__ (0x00000100)
#define __CORE_FLASH_SECTOR_NUM__ (768) //__FLASH_BASE_ADDR__ + __CORE_FLASH_SECTOR_NUM__ * __FLASH_SECTOR_SIZE__，是脚本区， 3M开始
#define __SCRIPT_FLASH_SECTOR_NUM__  (128)  //__SCRIPT_FLASH_SECTOR_NUM__ * __FLASH_SECTOR_SIZE__，是脚本区长度，512K，剩余512K是文件区
#define __FLASH_BASE_ADDR__ (0x01000000)
#define __RAMRUN_ISR_ADDR__ (0x20004000)
#define __SRAM_BASE_ADDR__ (0x20000000)
#define __APP_START_MAGIC__ (0x5ae1f0b5)
#ifndef __BUILD_OS__
#define __FUNC_IN_RAM__
#else
#define __FUNC_IN_RAM__ __attribute__((section (".RamFunc")))
#endif
#endif
