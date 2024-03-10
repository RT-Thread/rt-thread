/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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
 * @file  ocotp_test.c
 * @brief OCOTP driver unit test.
 * @ingroup diag-ocotp
 */

#include <stdio.h>
#include "sdk.h"
#include "ocotp/ocotp.h"

/*! 
 * OCOTP test.
 * This test allows to read or write a fuse location.
 *
 * @return  none
 */
int32_t ocotp_test(void)
{
    uint8_t sel, bank, row;
    uint32_t value;

    printf("Start OCOTP unit tests:");

    do {
        printf("\n  1 - to read a fuse location.\n");
        printf("  2 - to write a fuse location.\n");
        printf("  x - to exit.\n\n");

        do {
            sel = getchar();
        } while (sel == NONE_CHAR);

        if (sel == 'x') {
            printf("\nTest exit.\n");
            break;
        }

        if (sel == '1')
            printf("Go to sense function...\n");
        if (sel == '2')
            printf("Go to blow function...\n");

        printf("Please set the bank (0,1,2,...): \n");
        do {
            bank = getchar();
        } while (bank == NONE_CHAR);
        /* move from received ASCII code to real value */ 
        bank -= 0x30;
        printf("  %d\n",bank);

        printf("Please set the row (0,1,2,...): \n");
        do {
            row = getchar();
        } while (row == NONE_CHAR);
        /* move from received ASCII code to real value */
        row -= 0x30;
        printf("  %d\n",row);

        if (sel == '1') {
            printf("Value read in bank %d / row %d is:\n", bank, row);
            printf("0x%08X\n", ocotp_sense_fuse(bank, row));
        }
        if (sel == '2') {
            value = get_input_hex();

            printf("\n !! Do you really want to blow 0x%08X in bank %d / row %d ? (Y/N)!!\n",
                   value, bank, row);
            printf("Note that writing 0x0 is harmless.\n");
            do {
                sel = getchar();
            } while (sel == NONE_CHAR);
            if((sel == 'Y') || (sel == 'y'))
                ocotp_fuse_blow_row(bank, row, value);
        }

    } while(1);

    return 0;
}
