/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 *
 * This file is part of Renesas RA Flexible Software Package (FSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas FSP license agreement. Unless otherwise agreed in an FSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * File Name    : board_keys.c
 * Description  : This module has information about the keys on this board.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_RA6M4_IOT_KEYS
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#if defined(BOARD_RA6M4_IOT)

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/** Array of KEY IOPORT pins. */
static const uint16_t g_bsp_prv_keys[] =
{
    (uint16_t) BSP_IO_PORT_00_PIN_01,  ///< USER KEY1
    (uint16_t) BSP_IO_PORT_00_PIN_02,  ///< USER KEY2
};

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/** Structure with KEY information for this board. */

const bsp_keys_t g_bsp_keys =
{
    .key_count = (uint16_t) ((sizeof(g_bsp_prv_keys) / sizeof(g_bsp_prv_keys[0]))),
    .p_keys    = &g_bsp_prv_keys[0]
};
extern bsp_leds_t g_bsp_leds;
void key_sample (void)
{
    #if BSP_TZ_SECURE_BUILD

        /* Enter non-secure code */
        R_BSP_NonSecureEnter();
    #endif

    bsp_leds_t leds = g_bsp_leds;
    bsp_keys_t keys = g_bsp_keys;

    uint32_t key1_pin=keys.p_keys[BSP_KEY_KEY1];
    uint32_t key2_pin=keys.p_keys[BSP_KEY_KEY2];
    uint32_t led_pin =leds.p_leds[BSP_LED_LED1];

    while (1)
    {
      R_BSP_PinAccessEnable();
      if ( R_BSP_PinRead((bsp_io_port_pin_t)key1_pin)==BSP_IO_LEVEL_LOW)
      {
          R_BSP_PinWrite((bsp_io_port_pin_t) led_pin,BSP_IO_LEVEL_LOW);
      }
      if ( R_BSP_PinRead((bsp_io_port_pin_t)key2_pin)==BSP_IO_LEVEL_LOW)
       {
           R_BSP_PinWrite((bsp_io_port_pin_t) led_pin, BSP_IO_LEVEL_HIGH);
       }

       R_BSP_PinAccessDisable();

    }
}
/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

#endif

/** @} (end addtogroup BOARD_RA6M4_RENESAS_IOT_KEYS) */
