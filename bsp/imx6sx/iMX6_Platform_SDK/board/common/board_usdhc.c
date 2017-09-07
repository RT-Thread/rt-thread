/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "sdk.h"
#include "registers/regsiomuxc.h"
#include "registers/regsusdhc.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*!
  * Set up the GPIO for USDHC
  */
void usdhc_gpio_config(uint32_t instance)
{
    switch (instance) {
    case HW_USDHC1:
#if defined(BOARD_SABRE_AI)
        /* Select ALT5 mode of CSI0_DATA_EN for GPIO5_20 - SDb_WP(CSI0_DATA_EN_GPIO5_20) */
        gpio_set_gpio(GPIO_PORT5, 20);
        gpio_set_direction(GPIO_PORT5, 20, GPIO_GDIR_INPUT);
#endif
        break;

    case HW_USDHC2:
        break;

    case HW_USDHC3:
#if defined(BOARD_SABRE_AI)
        /* Select ALT5 mode of NANDF_CS2 for GPIO6_15 - SDa_CD_B(GPIO6_15) */
        gpio_set_gpio(GPIO_PORT6, 15);
        gpio_set_direction(GPIO_PORT6, 15, GPIO_GDIR_INPUT);

        /* Select ALT5 mode of SD2_DAT2 for GPIO1_13 - SDa_WP(SD2_DAT2_GPIO1_13) */
        gpio_set_gpio(GPIO_PORT1, 13);
        gpio_set_direction(GPIO_PORT1, 13, GPIO_GDIR_INPUT);
#endif
        break;
    case HW_USDHC4:
        break;

    default:
        break;
    }
}

bool usdhc_card_detected(uint32_t instance)
{
    bool ret_val = false;

#if defined(BOARD_SABRE_AI)
    if (instance == HW_USDHC1) {
        // SDb_CD_B
        // Bit HIGH == pin LOW == Card Detected.
        if (BG_USDHC_PRES_STATE_CDPL(HW_USDHC_PRES_STATE_RD(instance))) {
            ret_val = true;
        }
    } else if (instance == HW_USDHC3) {
        // SDa_CD_B using GPIO6_15
        // Bit LOW == pin LOW ==  Card Detected.
        ret_val = gpio_get_level(GPIO_PORT6, 15) == GPIO_LOW_LEVEL;
    }
#elif defined(BOARD_SMART_DEVICE)
    if (instance == HW_USDHC2) {
        // SD2_CD_B using GPIO2_02
        // Bit LOW == pin LOW ==  Card Detected.
        ret_val = gpio_get_level(GPIO_PORT2, 2) == GPIO_LOW_LEVEL;
    } else if (instance == HW_USDHC3) {
        // SD3_CD_B using GPIO2_00
        // Bit LOW == pin LOW ==  Card Detected.
        ret_val = gpio_get_level(GPIO_PORT2, 0) == GPIO_LOW_LEVEL;
    }
#else
    if (BG_USDHC_PRES_STATE_CDPL(HW_USDHC_PRES_STATE_RD(instance))) {
        // Bit HIGH == pin LOW ==  Card Detected.
        ret_val = true;
    }
#endif

    return ret_val;
}

bool usdhc_write_protected(uint32_t instance)
{
    bool ret_val = true;

#if defined(BOARD_SABRE_AI)
    if (instance == HW_USDHC1) {
        // SDb_WP (CSI0_DATA_EN_GPIO5_20)
        // Bit HIGH == pin HIGH == Write Protected.
        ret_val = gpio_get_level(GPIO_PORT5, 20) == GPIO_HIGH_LEVEL;
    } else if (instance == HW_USDHC3) {
        // SDa_WP (SD2_DAT2_GPIO1_13)
        // Bit HIGH == pin HIGH == Write Protected.
        ret_val = gpio_get_level(GPIO_PORT1, 13) == GPIO_HIGH_LEVEL;
    }
#elif defined(BOARD_SMART_DEVICE)
    if (instance == HW_USDHC2) {
        // SD2_WP using GPIO2_03
        // Bit HIGH == pin HIGH == Write Protected.
        ret_val = gpio_get_level(GPIO_PORT2, 3) == GPIO_HIGH_LEVEL;
    } else if (instance == HW_USDHC3) {
        // SD3_WP using GPIO2_01
        // Bit HIGH == pin HIGH == Write Protected.
        ret_val = gpio_get_level(GPIO_PORT2, 1) == GPIO_HIGH_LEVEL;
    }
#else
    if (BG_USDHC_PRES_STATE_WPSPL(HW_USDHC_PRES_STATE_RD(instance))) {
        // Bit HIGH == pin LOW == NOT Write Protected (Write Enabled).
        ret_val = false;
    }
#endif

    return ret_val;
}
