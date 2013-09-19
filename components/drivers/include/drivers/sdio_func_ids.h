/*
 * File      : sdio_func_ids.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2012-02-26     weety         first version
 */
 
#ifndef __SDIO_FUNC_IDS_H__
#define __SDIO_FUNC_IDS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Standard SDIO Function Interfaces */

#define SDIO_FUNC_CODE_NONE        0x00 /* Not a SDIO standard interface */
#define SDIO_FUNC_CODE_UART        0x01 /* SDIO Standard UART */
#define SDIO_FUNC_CODE_BT_A        0x02 /* SDIO Type-A for Bluetooth standard interface */
#define SDIO_FUNC_CODE_BT_B        0x03 /* SDIO Type-B for Bluetooth standard interface */
#define SDIO_FUNC_CODE_GPS         0x04 /* SDIO GPS standard interface */
#define SDIO_FUNC_CODE_CAMERA      0x05 /* SDIO Camera standard interface */
#define SDIO_FUNC_CODE_PHS         0x06 /* SDIO PHS standard interface */
#define SDIO_FUNC_CODE_WLAN        0x07 /* SDIO WLAN interface */
#define SDIO_FUNC_CODE_ATA         0x08 /* Embedded SDIO-ATA standard interface */

/* manufacturer id, product io */

#define SDIO_MANUFACTURER_ID_MARVELL        0x02df
#define SDIO_PRODUCT_ID_MARVELL_88W8686     0x9103

#ifdef __cplusplus
}
#endif

#endif
