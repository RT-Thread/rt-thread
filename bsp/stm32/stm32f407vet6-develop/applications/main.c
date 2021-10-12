/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2018-11-19     flybreak     add stm32f407-atk-explorer bsp
 */

/****************************************************************************
 *
 * File Name：
 *  
 * Author：
 *  
 * Date：
 * 
 * Descriptions:
 * 
 *
 ******************************************************************************/
/*----------------------------------------------------------------------------*
**                             Dependencies                                   *
**----------------------------------------------------------------------------*/
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "board_def_map.h"

#ifdef __cplusplus
extern   "C"
{
#endif

/**---------------------------------------------------------------------------*
 **                            Debugging Flag                                 *
 **---------------------------------------------------------------------------*/
#define DBG_TAG     "MAIN"
#define DBG_LVL     DBG_LOG
#include <rtdbg.h>

/**---------------------------------------------------------------------------*
**                             Compiler Flag                                  *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Mcaro Definitions                              *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Data Structures                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Vars                                     *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Extern Function                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Function                                 *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Public Function                                *
**----------------------------------------------------------------------------*/
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <u8g2_port.h>

// You may reference Drivers/drv_gpio.c for pinout
// In u8x8.h #define U8X8_USE_PINS 

//#define OLED_SPI_PIN_RES                     2  // PA2
//#define OLED_SPI_PIN_DC                      1  // PA1
//#define OLED_SPI_PIN_CS                      0  // PA0

//static void u8g2_Setup_ssd1327_i2c_ws_128x128(int argc,char *argv[])
//{
//    u8g2_t u8g2;

//    // Initialization
//    u8g2_Setup_ssd1327_i2c_ws_128x128_2( &u8g2, U8G2_R0, u8x8_byte_rtthread_4wire_hw_spi, u8x8_gpio_and_delay_rtthread);
//    u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_CS, OLED_SPI_PIN_CS);
//    u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_DC, OLED_SPI_PIN_DC);
//    u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_RESET, OLED_SPI_PIN_RES);
//    
//		u8g2_InitDisplay(&u8g2);
//    u8g2_SetPowerSave(&u8g2, 0);

//    // Draw Graphics
//    /* full buffer example, setup procedure ends in _f */
//    u8g2_ClearBuffer(&u8g2);
//    u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tr);
//    u8g2_DrawStr(&u8g2, 1, 18, "U8g2 on RT-Thread");
//    u8g2_SendBuffer(&u8g2);

//    u8g2_SetFont(&u8g2, u8g2_font_unifont_t_symbols);
//    u8g2_DrawGlyph(&u8g2, 112, 56, 0x2603 );
//    u8g2_SendBuffer(&u8g2);
//}
//MSH_CMD_EXPORT(u8g2_Setup_ssd1327_i2c_ws_128x128, hardware 4 wire spi ssd1306 sample);


/*----------------------------------------------------------------------------*
**                             Function Define                                *
**----------------------------------------------------------------------------*/
/*************************************************
* Function:
* Description:
* Author:
* Returns: 
* Parameter:
* History:
*************************************************/
int main(void)
{
	//  int main_ret = 0;

	  LOG_D("BUILD=%s\n", BUILD);
    while (1)
    {
			//	LOG_D("hello rt-thread!\n");
				rt_thread_mdelay(100);
    }
 //   return main_ret;
}



/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
// End of xxx.c
