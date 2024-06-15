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

/*!
 * @file usb_common.c
 * @brief USB common routines.
 */
/*! This routine returns the current speed of the port\n
 * This must be called after the bus reset is completed.
 *
 * @param	port			The usb controller
 * @return	usbPortSpeed	The operating speed full/high
 */

#include "usb/usb.h"
#include <stdio.h>

usbPortSpeed_t usb_get_port_speed(usb_module_t * port)
{
    usbPortSpeed_t speed;
    uint32_t core = (uint32_t)port->controllerID;

    /* Determine the speed we are connected at. */
    switch (BG_USBC_UH1_PORTSC1_PSPD(HW_USBC_PORTSC1_RD(core))) { 
    case usbSpeedFull:
        speed = usbSpeedFull;
        printf("Connected at full-speed\n");
        break;
    case usbSpeedLow:
        speed = usbSpeedLow;
        printf("Connected at low-speed\n");
        break;
    case usbSpeedHigh:
        speed = usbSpeedHigh;
        printf("Connected at high-speed\n");
        break;
    default:
        speed = usbSpeedUnknown;
        printf("Invalid port speed\n");
        break;
    }
    printf("PORTSC = 0x%08x\n", HW_USBC_PORTSC1_RD(core));

    return speed;
}

/*!
 * This routine performs a byte swap on a 32-bit word
 *
 * @param data
 * @return	Swapped data
 */
uint32_t swap32(uint32_t data)
{
    uint32_t temp = 0;

    temp = (data & 0xff) << 24;
    temp |= ((data & 0xff00) << 8);
    temp |= ((data & 0xff0000) >> 8);
    temp |= ((data & 0xff000000) >> 24);

    return (temp);
}

/*!
 * This function displays a menu and waits for an input char to be received from the UART.\n
 * If the character is a numeric value within the table range, the entry number is returned.
 *
 * @param   *menu_table   the table containing the menu items
 * @return  menu_item     the table entry of the selected item
 *
 */
int get_menu_item(char *menu_table[])
{
    uint8_t input;
    int i, menu_item, num_items;

    for (i = 0; *menu_table[i] != '\0'; i++) {
        printf("%d. %s\n", i, menu_table[i]);
    }
    num_items = i;

    menu_item = -1;
    while (menu_item == -1) {
        printf("Select > ");

        do {
            input = getchar();
        } while (input == NONE_CHAR);   // wait for a character

        if ((input >= '0') && (input <= '9')) {
            menu_item = input - '0';
            if (menu_item < num_items) {
                printf("%1d\n", menu_item);
                return (menu_item);
            } else
                menu_item = -1;
        }
    }
    return (menu_item);
}
