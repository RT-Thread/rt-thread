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
 * @file board_id_internal.h
 * @brief header file with board and chip defines to be included by all the tests/utils
 *
 */

#ifndef __BOARD_ID_INTERNAL_H__
#define __BOARD_ID_INTERNAL_H__

#include "registers/regsusbanalog.h"
#include "registers/regsocotp.h"


/* --- Register HW_USB_ANALOG_DIGPROG, field CHIP_TYPE[23:16] (RO)
 *
 * Fixed read-only value reflecting the CHIP_TYPE field of the RTL version.
 */

#define BP_USB_ANALOG_DIGPROG_CHIP_TYPE      (16)   //!< Bit position for USB_ANALOG_DIGPROG_CHIP_TYPE.
#define BM_USB_ANALOG_DIGPROG_CHIP_TYPE      (0x00ff0000)   //!< Bit mask for USB_ANALOG_DIGPROG_CHIP_TYPE.

//! @brief Get value of USB_ANALOG_DIGPROG_CHIP_TYPE from a register value.
#define BG_USB_ANALOG_DIGPROG_CHIP_TYPE(r)   (((r) & BM_USB_ANALOG_DIGPROG_CHIP_TYPE) >> BP_USB_ANALOG_DIGPROG_CHIP_TYPE)

/* --- Register HW_USB_ANALOG_DIGPROG, field MAJOR_REV[15:8] (RO)
 *
 * Fixed read-only value reflecting the MAJOR_REV field of the RTL version.
 */

#define BP_USB_ANALOG_DIGPROG_MAJOR_REV      (8)    //!< Bit position for USB_ANALOG_DIGPROG_MAJOR_REV.
#define BM_USB_ANALOG_DIGPROG_MAJOR_REV      (0x0000ff00)   //!< Bit mask for USB_ANALOG_DIGPROG_MAJOR_REV.

//! @brief Get value of USB_ANALOG_DIGPROG_MAJOR_REV from a register value.
#define BG_USB_ANALOG_DIGPROG_MAJOR_REV(r)   (((r) & BM_USB_ANALOG_DIGPROG_MAJOR_REV) >> BP_USB_ANALOG_DIGPROG_MAJOR_REV)

/*!
 * @brief HW_OCOTP_GP1 - Value of OTP Bank4 Word6 (HW Capabilities) (RW)
 *
 * Reset value: 0x00000000
 *
 * Copied from the OTP automatically after reset. Can be re-loaded by setting
 * HW_OCOTP_CTRL[RELOAD_SHADOWS]  Shadowed memory mapped access to OTP Bank 4, word 6 (ADDR = 0x26).
 * EXAMPLE   Empty Example.
 */
#define HW_OCOTP_GP1_BANK      4
#define HW_OCOTP_GP1_ROW       6

/* --- Register HW_OCOTP_GP1, field BOARD_TYPE[15:12] (RO)
 *
 * Fixed read-only value reflecting the BOARD_TYPE field of the Board Version set in the OCOTP fuses.
 */

#define BP_OCOTP_GP1_BOARD_TYPE      (12)   //!< Bit position for OCOTP_GP1_BOARD_TYPE.
#define BM_OCOTP_GP1_BOARD_TYPE      (0x0000f000)   //!< Bit mask for OCOTP_GP1_BOARD_TYPE.

//! @brief Get value of OCOTP_GP1_CHIP_TYPE from a register value.
#define BG_OCOTP_GP1_BOARD_TYPE(r)   (((r) & BM_OCOTP_GP1_BOARD_TYPE) >> BP_OCOTP_GP1_BOARD_TYPE)

/* --- Register HW_OCOTP_GP1, field BOARD_REV[11:8] (RO)
 *
 * Fixed read-only value reflecting the BOARD_REV field of the Board Version set in the OCOTP fuses.
 */

#define BP_OCOTP_GP1_BOARD_REV      (8) //!< Bit position for OCOTP_GP1_BOARD_REV.
#define BM_OCOTP_GP1_BOARD_REV      (0x00000f00)    //!< Bit mask for OCOTP_GP1_BOARD_REV.

//! @brief Get value of OCOTP_GP1_BOARD_REV from a register value.
#define BG_OCOTP_GP1_BOARD_REV(r)   (((r) & BM_OCOTP_GP1_BOARD_REV) >> BP_OCOTP_GP1_BOARD_REV)

#endif // __BOARD_ID_INTERNAL_H__
