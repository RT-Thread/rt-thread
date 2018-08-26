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
 * @file hardware.c
 * @brief This file contains the module definitions and some init functions.
 *
 * @ingroup diag_init
 */

#include <stdio.h>
#include "sdk_types.h"
#include "board_id/board_id.h"
#include "board_id/board_id_registers.h"

void chip_name(char* const name, const uint32_t chip_id, const bool long_name_flag)
{
    char long_name[64] = { 0 };

    switch (chip_id) {
    case CHIP_TYPE_MX6SL:
        sprintf(name, "MX6SL");
        sprintf(long_name, "MX6 Solo-Lite (MX6SL)");
        break;
    case CHIP_TYPE_MX6SDL:
        sprintf(name, "MX6SDL");
        sprintf(long_name, "MX6 Solo/Dual-Lite (MX6SDL)");
        break;
    case CHIP_TYPE_MX6DQ:
        sprintf(name, "MX6DQ");
        sprintf(long_name, "MX6 Dual/Quad (MX6DQ)");
        break;
    default:
        sprintf(name, "UNKNOWN");
        sprintf(long_name, "UNKNOWN CHIP");
        break;
    }

    if (long_name_flag) {
        sprintf(name, long_name);
    }
}

void chip_revision(char* const rev_str, const uint32_t major_rev, const uint32_t minor_rev)
{
    char major = 'x';
    char minor = 'x';

    switch (major_rev) {
    case CHIP_MAJOR_REV_TO1:
        major = '1';
        break;
    case CHIP_MAJOR_REV_TO2:
        major = '2';
        break;
    default:
        major = 'x';
        break;
    }

    switch (minor_rev) {
    case CHIP_MINOR_REV_DOT0:
        minor = '0';
        break;
    case CHIP_MINOR_REV_DOT1:
        minor = '1';
        break;
    case CHIP_MINOR_REV_DOT2:
        minor = '2';
        break;
    default:
        minor = 'x';
        break;
    }

    sprintf(rev_str, "TO%c.%c", major, minor);
}

#define SIPIX_DISABLED_MASK 0x01000000
#define EPDC_DISABLED_MASK  0x02000000

void board_name(char* const name, const uint32_t board_id)
{
    switch (board_id)
    {
        case BOARD_TYPE_SABRE_AI:
            sprintf(name, "Sabre AI (ARD)");
            break;
        case BOARD_TYPE_SMART_DEVICE:
            sprintf(name, "Smart Device (SD)");
            break;
        case BOARD_TYPE_EVB:
            sprintf(name, "EVB");
            break;
        case BOARD_TYPE_EVK:
        {
            if ( HW_OCOTP_CFG2_RD() & EPDC_DISABLED_MASK )
                sprintf(name, "EVK SPDC");
            else if ( HW_OCOTP_CFG2_RD() & SIPIX_DISABLED_MASK )
                sprintf(name, "EVK EPDC");
            else
                sprintf(name, "EVK");

            break;
        }
        default:
            sprintf(name, "UNKNOWN BOARD");
            break;
    }
}

void board_revision(char* const name, const uint32_t board_rev)
{
    char revision[8] = "rev. x\0\0";

    switch (board_rev) {
    case 1:
        revision[5] = 'A';
        break;
    case 2:
        revision[5] = 'B';
        break;
    case 3:
        revision[5] = 'B';
        revision[6] = 'x';
        break;
    case 4:
        revision[5] = 'C';
        break;
    case 5:
        revision[5] = 'D';
        break;
    default:
        revision[5] = (char)((board_rev & 0xFF) + '0');
        break;
    }

    sprintf(name, revision);
}

void board_description(char* const desc)
{
    fsl_board_id_t board_id = get_board_id();

    char chip_str[64] = { 0 };
    char chip_rev_str[64] = { 0 };
    char board_str[64] = { 0 };
    char board_rev_str[64] = { 0 };

    chip_name(chip_str, board_id.B.CHIP_TYPE_ID, false);
    chip_revision(chip_rev_str, board_id.B.CHIP_REV_MAJOR, board_id.B.CHIP_REV_MINOR);
    board_name(board_str, board_id.B.BOARD_TYPE_ID);
    board_revision(board_rev_str, board_id.B.BOARD_REV);

    sprintf(desc, "%s %s %s %s", chip_str, chip_rev_str, board_str, board_rev_str);
}

/*!
 * Get the board id info
 */
fsl_board_id_t get_board_id(void)
{
    fsl_board_id_t fsl_board_id = { 0 };

    uint32_t chip_id = HW_USB_ANALOG_DIGPROG_RD();
    fsl_board_id.B.CHIP_TYPE_ID = BG_USB_ANALOG_DIGPROG_CHIP_TYPE(chip_id);
    fsl_board_id.B.CHIP_REV_MAJOR = BG_USB_ANALOG_DIGPROG_MAJOR_REV(chip_id);
    fsl_board_id.B.CHIP_REV_MINOR = BG_USB_ANALOG_DIGPROG_MINOR(chip_id);
//    printf("read 0x%08X from HW_USB_ANALOG_DIGPROG(0x%08X)\n", chip_id, HW_USB_ANALOG_DIGPROG_ADDR);

    uint32_t fused_board_id = HW_OCOTP_GP1_RD();
    fsl_board_id.B.BOARD_TYPE_ID = BG_OCOTP_GP1_BOARD_TYPE(fused_board_id);
    fsl_board_id.B.BOARD_REV = BG_OCOTP_GP1_BOARD_REV(fused_board_id);
//    printf("read 0x%08X from HW_OCOTP_GP1(0x%08X)\n", fused_board_id, HW_OCOTP_GP1_ADDR);

    return fsl_board_id;
}

/*!
 * Display board id info
 */
void show_board_id(const fsl_board_id_t board_id, const char* const indent)
{
    const char* const loc_indent = indent == NULL ? "" : indent;

    printf("%s========== board id\n", loc_indent);

    char chip_str[64] = { 0 };
    char chip_str_full[64] = { 0 };
    char chip_rev_str[64] = { 0 };
    char board_str[64] = { 0 };
    char board_rev_str[64] = { 0 };

    chip_name(chip_str, board_id.B.CHIP_TYPE_ID, false);
    chip_name(chip_str_full, board_id.B.CHIP_TYPE_ID, true);
    chip_revision(chip_rev_str, board_id.B.CHIP_REV_MAJOR, board_id.B.CHIP_REV_MINOR);
    board_name(board_str, board_id.B.BOARD_TYPE_ID);
    board_revision(board_rev_str, board_id.B.BOARD_REV);

    printf("\n%s%s %s %s %s (0x%08X)\n", loc_indent, chip_str, chip_rev_str, board_str, board_rev_str,
           board_id.U);
    printf("%s    Chip Type       = %s (0x%02X)\n", loc_indent, chip_str_full, board_id.B.CHIP_TYPE_ID);
    printf("%s    Chip Revision   = %s (0x%02X)(0x%02X)\n", loc_indent, chip_rev_str,
            board_id.B.CHIP_REV_MAJOR, board_id.B.CHIP_REV_MINOR);
    printf("%s    Board Type      = %s (0x%02X)\n", loc_indent, board_str, board_id.B.BOARD_TYPE_ID);
    printf("%s    Board Revision  = %s (0x%02X)\n", loc_indent, board_rev_str, board_id.B.BOARD_REV);

    printf("%s==================================\n", loc_indent);
}

