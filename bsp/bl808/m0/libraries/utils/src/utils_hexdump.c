/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <ctype.h>

#include <utils_hexdump.h>

#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 16
#endif
//FIXME fix putchar
extern int bl_putchar(int c);
 
void utils_hexdump(void *mem, unsigned int len)
{
    unsigned int i, j;

    for (i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++) {
        /* print offset */
        if (i % HEXDUMP_COLS == 0) {
            printf("0x%06x: ", i);
        }

        /* print hex data */
        if (i < len) {
            printf("%02x ", 0xFF & ((char*)mem)[i]);
        } else {
            /* end of block, just aligning for ASCII dump */
            printf("   ");
        }

        /* print ASCII dump */
        if (i % HEXDUMP_COLS == (HEXDUMP_COLS - 1)) {
            for (j = i - (HEXDUMP_COLS - 1); j <= i; j++) {
                if (j >= len) {
                    /* end of block, not really printing */
                    bl_putchar(' ');
                } else if(isprint((int)((char*)mem)[j])) {
                    /* printable char */
                    bl_putchar(0xFF & ((char*)mem)[j]);
                } else {
                    /* other char */
                    bl_putchar('.');
                }
            }
            puts("\r\n");
        }
    }
}
 
