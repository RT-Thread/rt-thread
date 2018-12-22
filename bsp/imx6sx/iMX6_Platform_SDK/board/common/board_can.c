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

#include "iomux_config.h"
#include "ioexpander/max7310.h"
#include "gpio/gpio.h"
#include "registers/regsflexcan.h"
#include "flexcan/flexcan.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*!
 * board dependent IOMUX configuration functions
 */
void hw_can_iomux_config(uint32_t module_instance)
{

#ifdef BOARD_SABRE_AI
    board_ioexpander_iomux_config();
    /* CAN_EN active high output */
    max7310_set_gpio_output(1, 6, GPIO_HIGH_LEVEL); //expander b, io6

    /* CAN_STBY active high output */
    max7310_set_gpio_output(1, 5, GPIO_HIGH_LEVEL); //expander b, io5 
#endif

    flexcan_iomux_config(module_instance);

#ifdef BOARD_SABRE_AI
    switch (module_instance)
    {
    case HW_FLEXCAN1:
        board_ioexpander_iomux_config();
        /* Select CAN, ENET_CAN1_STEER(PORT_EXP_B3) */
        max7310_set_gpio_output(1, 3, GPIO_HIGH_LEVEL); //expander b, io3
        /* Select ALT5 mode of GPIO_4 for GPIO1_4 - CAN1_NERR_B */
        /* active low input */
        gpio_set_gpio(GPIO_PORT1, 4);
        gpio_set_direction(GPIO_PORT1, 4, GPIO_GDIR_INPUT);
        break;

    case HW_FLEXCAN2:
        /* Select ALT5 mode of SD4_DAT3 for GPIO2_11 - CAN2_NERR_B */
        /* active low input */
        gpio_set_gpio(GPIO_PORT2, 11);
        gpio_set_direction(GPIO_PORT2, 11, GPIO_GDIR_INPUT);
        break;

    default:
        printf("ERR: invalid FLEXCAN instance for iomux config\n");
        break;
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
