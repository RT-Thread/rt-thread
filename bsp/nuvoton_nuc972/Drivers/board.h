/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2017/11/08     Urey			first version
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#ifndef __ASSEMBLY__

#define BOARD_SDRAM_SIZE            0x04000000
/*@{*/
#if defined(__CC_ARM)
    extern int Image$$RW_RAM1$$ZI$$Base;
    extern int Image$$RW_RAM1$$ZI$$Length;
    extern int Image$$RW_RAM1$$ZI$$Limit;

#	define BOARD_HEAP_START        (void*)&Image$$RW_RAM1$$ZI$$Limit

#elif (defined (__GNUC__))
extern unsigned char 			__bss_start__;
extern unsigned char 			__bss_end__;

#	define BOARD_HEAP_START 		(void*)&__bss_end__
#endif

#define BOARD_GUI_RAM_SIZE          (12 * 1024 * 1024)
#define BOARD_HEAP_END              (void*)(BOARD_SDRAM_SIZE - BOARD_GUI_RAM_SIZE)

#endif


/*
 * UART config...
 */
#define BOARD_USING_UART0

/*
 * SPI config...
 */
#define BOARD_USING_SPI0

/* I2C config */
//#define BOARD_USING_I2C0
//#define BOARD_USING_I2C1
#define BOARD_USING_I2C0_SW
#define BOARD_USING_I2C1_SW

/*
 * SDIO config
 */
#define BOARD_USING_SDIO0
#define BOARD_USING_SDIO1
/*
 * ETH config
 */
#define BOARD_USING_ETH0
//#define BOARD_USING_ETH1

/*
 *
 */
//#define APPFS_USING_SPIFFS


/* LCD config */
#define LCD_VRAM_SIZE       (2 * 1024 * 1024)
#define LCD_VFB_SIZE        (10 * 1024 * 1024)

#if ((LCD_VRAM_SIZE + LCD_VFB_SIZE) > BOARD_GUI_RAM_SIZE)
#  error "total size is large than the gui_ram size"
#endif

#define LCD_VRAM_ADDR       (BOARD_SDRAM_SIZE - BOARD_GUI_RAM_SIZE)
#define LCD_VRAM_SADDR      (0x80000000 | LCD_VRAM_ADDR)


#define LCD_VFB_ADDR        (LCD_VRAM_ADDR + LCD_VRAM_SIZE)
#define LCD_VFB_SADDR       (0x80000000 | LCD_VFB_ADDR)




#endif /* _BSP_NUC970_DEVBOARD_DRIVERS_BOARD_H_ */
