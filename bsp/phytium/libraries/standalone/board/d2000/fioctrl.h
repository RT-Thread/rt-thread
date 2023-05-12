/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fioctrl.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:35
 * Description:  This files is for io-ctrl function definition (io-mux/io-config/io-delay)
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/22   init commit
 */


#ifndef  BOARD_D2000_FIOCTRL_H
#define  BOARD_D2000_FIOCTRL_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/
#include "ftypes.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FIOCTRL_INDEX(offset, func_beg) \
    { \
        /* reg_off */   (offset),  \
        /* reg_bit */   (func_beg) \
    }

/************************** Variable Definitions *****************************/
#define FIOCTRL_CRU_CLK_OBV_PAD           (FPinIndex)FIOCTRL_INDEX(0x200, 24)
#define FIOCTRL_SPI0_CSN0_PAD             (FPinIndex)FIOCTRL_INDEX(0x208, 16)
#define FIOCTRL_SPI0_SCK_PAD              (FPinIndex)FIOCTRL_INDEX(0x208, 12)
#define FIOCTRL_SPI0_SO_PAD               (FPinIndex)FIOCTRL_INDEX(0x208, 8)
#define FIOCTRL_SPI0_SI_PAD               (FPinIndex)FIOCTRL_INDEX(0x208, 4)

#define FIOCTRL_TJTAG_TDI_PAD             (FPinIndex)FIOCTRL_INDEX(0x204, 24) /* can0-tx: func 1 */
#define FIOCTRL_SWDITMS_SWJ_PAD           (FPinIndex)FIOCTRL_INDEX(0x204, 12) /* can0-rx: func 1 */

#define FIOCTRL_NTRST_SWJ_PAD             (FPinIndex)FIOCTRL_INDEX(0x204, 20) /* can1-tx: func 1 */
#define FIOCTRL_SWDO_SWJ_PAD              (FPinIndex)FIOCTRL_INDEX(0x204, 8)  /* can1-rx: func 1 */

#define FIOCTRL_I2C0_SCL_PAD              (FPinIndex)FIOCTRL_INDEX(0x208, 24) /* i2c0-scl: func 0 */
#define FIOCTRL_I2C0_SDA_PAD              (FPinIndex)FIOCTRL_INDEX(0x208, 20) /* i2c0-sda: func 0 */
#define FIOCTRL_ALL_PLL_LOCK_PAD          (FPinIndex)FIOCTRL_INDEX(0x200, 28) /* i2c1-scl: func 2 */
#define FIOCTRL_CRU_CLK_OBV_PAD           (FPinIndex)FIOCTRL_INDEX(0x200, 24) /* i2c1-sda: func 2 */
#define FIOCTRL_SWDO_SWJ_PAD              (FPinIndex)FIOCTRL_INDEX(0x204, 8)  /* i2c2-scl: func 2 */
#define FIOCTRL_TDO_SWJ_IN_PAD            (FPinIndex)FIOCTRL_INDEX(0x204, 4)  /* i2c2-sda: func 2 */
#define FIOCTRL_HDT_MB_DONE_STATE_PAD     (FPinIndex)FIOCTRL_INDEX(0x204, 0)  /* i2c3-scl: func 2 */
#define FIOCTRL_HDT_MB_FAIL_STATE_PAD     (FPinIndex)FIOCTRL_INDEX(0x208, 28) /* i2c3-sda: func 2 */

#define FIOCTRL_UART_2_RXD_PAD            (FPinIndex)FIOCTRL_INDEX(0x210, 0)  /* spi1_csn0: func 1 */
#define FIOCTRL_UART_2_TXD_PAD            (FPinIndex)FIOCTRL_INDEX(0x214, 28) /* spi1_sck: func 1 */
#define FIOCTRL_UART_3_RXD_PAD            (FPinIndex)FIOCTRL_INDEX(0x214, 24) /* spi1_so: func 1 */
#define FIOCTRL_UART_3_TXD_PAD            (FPinIndex)FIOCTRL_INDEX(0x214, 20) /* spi1_si: func 1 */
#define FIOCTRL_QSPI_CSN2_PAD             (FPinIndex)FIOCTRL_INDEX(0x214, 8)  /* spi1_csn1: func 1 */
#define FIOCTRL_QSPI_CSN3_PAD             (FPinIndex)FIOCTRL_INDEX(0x214, 4)  /* spi1_csn2: func 1 */



#ifdef __cplusplus
}
#endif

#endif
