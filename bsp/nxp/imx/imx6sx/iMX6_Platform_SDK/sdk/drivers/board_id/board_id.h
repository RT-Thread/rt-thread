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
 * @file board_id.h
 * @brief header file with board and chip defines to be included by all the tests/utils
 *
 */

#ifndef BOARD_ID_H_
#define BOARD_ID_H_

#include "sdk_types.h"
#include "board_id_registers.h"

/*!
 * @brief Fused Freescale Reference Board ID
 *
 * This struct represents the fused board ID for Freescale Reference Boards.
 */
typedef union _fsl_board_id {
    uint32_t U;
    struct _fsl_board_id_bitfields {
        unsigned CHIP_REV_MINOR:8;  //!< [7:0] Fixed read-only value reflecting the MINOR field of the RTL version.
        unsigned CHIP_REV_MAJOR:8;  //!< [15:8] Fixed read-only value reflecting the MAJOR field of the RTL version.
        unsigned CHIP_TYPE_ID:8;    //!< [23:16] Fixed read-only value reflecting the CHIP_TYPE field of the RTL version.
        unsigned BOARD_REV:4;   //!< [27:24] Fixed read-only value reflecting the BOARD_REV field of the Board Version set in the OCOTP fuses.
        unsigned BOARD_TYPE_ID:4;   //!< [31:28] Fixed read-only value reflecting the BOARD_TYPE field of the Board Version set in the OCOTP fuses.
    } B;
} fsl_board_id_t;

// Get the FSL Board ID  (fsl_board_id_t)
fsl_board_id_t get_board_id(void);
// Get strings describing the various components of the FSL Board ID  (fsl_board_id_t)
void chip_name(char* const name, const uint32_t chip_id, const bool long_name_flag);
void chip_revision(char* const rev_str, const uint32_t major_rev, const uint32_t minor_rev);
void board_name(char* const name, const uint32_t board_id);
void board_revision(char* const name, const uint32_t board_rev);
void board_description(char* const desc);

void show_board_id(const fsl_board_id_t board_id, const char* const indent);

//! @name Chip Type
//@{
#define CHIP_TYPE_MX6SL         0x60
#define CHIP_TYPE_MX6SDL        0x61
#define CHIP_TYPE_MX6DQ         0x63
//@}

//! @name Chip Major Revision
//@{
#define CHIP_MAJOR_REV_TO1      0x00
#define CHIP_MAJOR_REV_TO2      0x01
//@}

//! @name Chip Minor Revision
//@{
#define CHIP_MINOR_REV_DOT0     0x00
#define CHIP_MINOR_REV_DOT1     0x01
#define CHIP_MINOR_REV_DOT2     0x02
//@}

//! @name Board Type
//@{
#define BOARD_TYPE_DEFAULT      0x0
#define BOARD_TYPE_SABRE_AI     0x1
#define BOARD_TYPE_SMART_DEVICE 0x2
#define BOARD_TYPE_EVB          0x4
#define BOARD_TYPE_EVK          0x5
//@}

//! @name Board Revision
//@{
#define BOARD_REVISION_DEFAULT  0x0
#define BOARD_REVISION_A        0x1
#define BOARD_REVISION_B        0x2
#define BOARD_REVISION_BX       0x3
#define BOARD_REVISION_C        0x4
#define BOARD_REVISION_D        0x5
//@}

#if defined(CHIP_MX6SL)
#define CHIP_TYPE        CHIP_TYPE_MX6SL
#elif defined(CHIP_MX6SDL)
#define CHIP_TYPE        CHIP_TYPE_MX6SDL
#elif defined(CHIP_MX6DQ)
#define CHIP_TYPE        CHIP_TYPE_MX6DQ
#else
#error Need to define a chip type
#endif

#if defined(BOARD_SABRE_AI)
#define BOARD_TYPE            BOARD_TYPE_SABRE_AI
#elif defined(BOARD_SMART_DEVICE)
#define BOARD_TYPE            BOARD_TYPE_SMART_DEVICE
#elif defined(BOARD_EVB)
#define BOARD_TYPE            BOARD_TYPE_EVB
#elif defined(BOARD_EVK)
#define BOARD_TYPE            BOARD_TYPE_EVK
#else
#error Need to define a board type
#endif

#if defined(BOARD_REV_A)
#define BOARD_REVISION        BOARD_REVISION_A
#elif defined(BOARD_REV_B)
#define BOARD_REVISION        BOARD_REVISION_B
#elif defined(BOARD_REV_C)
#define BOARD_REVISION        BOARD_REVISION_C
#elif defined(BOARD_REV_D)
#define BOARD_REVISION        BOARD_REVISION_D
#else
#error Need to define a board revision
#endif

#endif /*BOARD_ID_H_ */
