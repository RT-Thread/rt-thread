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

#include <stdio.h>
#include <stdlib.h>
#include "sdk.h"
#include "gpmi/gpmi.h"

#define ENABLE_ECC_TEST 1

#define __ALIGN4__ __attribute__((aligned(4)))

#define SIZE_IN_WORDS(s) (((s) + sizeof(uint32_t) - 1) / sizeof(uint32_t))

static uint8_t s_page_buffer[8192] __ALIGN4__;
static uint8_t s_read_buffer[8192] __ALIGN4__;
static uint8_t s_aux_buffer[1024] __ALIGN4__;

const unsigned kMaxBufferBytes = sizeof(s_page_buffer);

uint32_t g_actualBufferBytes = sizeof(s_page_buffer);

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! \brief Fill the given buffer with a pattern based on the sector number.
void fill_data_buffer(uint8_t * buffer, uint32_t sectorNumber, void * p)
{
    uint32_t i;
    
    for (i=0; i < SIZE_IN_WORDS(g_actualBufferBytes); ++i)
    {
        buffer[i] = (sectorNumber ^ ((~sectorNumber) << 8) ^ (sectorNumber << 16) ^ ((~sectorNumber) << 24)) ^ (uint32_t)p ^ 0x96f187e2 ^ i ^ (i << 8) ^ (i << 16) ^ (i << 24);
    }
}

void clear_buffer(uint8_t * buffer)
{
    memset(buffer, 0xff, kMaxBufferBytes);
}

void clear_aux()
{
    memset(s_aux_buffer, 0xff, sizeof(s_aux_buffer));
}

void fill_aux(uint8_t * buffer, uint32_t sectorNumber)
{
    memset(buffer, 0xff, sizeof(s_aux_buffer));
    
    int i;
    for (i=0; i<3; ++i)
    {
        buffer[i] = (sectorNumber ^ ((~sectorNumber) << 8) ^ (sectorNumber << 16) ^ ((~sectorNumber) << 24)) ^ 0x2e781f69;
    }
    
    // Make sure it doesn't look like a bad block
    ((uint8_t *)buffer)[0] = 0xff;
}

//! \param a The actual contents.
//! \param b The expected contents.
bool compare_buffers(const void * a, const void * b, uint32_t count)
{
#if 0
    const uint8_t * ca = (const uint8_t *)a;
    const uint8_t * cb = (const uint8_t *)b;
    uint32_t offset = 0;
    while (count--)
    {
        if (*ca++ != *cb++)
        {
            printf("buffer mismatch at offset %u (actual:0x%02x != expected:0x%02x)\n", offset, *(ca - 1), *(cb - 1));
            return false;
        }
        
        offset++;
    }
#else
    const uint32_t * ca = (const uint32_t *)a;
    const uint32_t * cb = (const uint32_t *)b;
    uint32_t offset = 0;
    count /= sizeof(uint32_t);
    while (count--)
    {
        if (*ca++ != *cb++)
        {
            printf("buffer mismatch at word %u (actual:0x%08x != expected:0x%08x)\n", offset, *(ca - 1), *(cb - 1));
            return false;
        }
        
        offset++;
    }
#endif
    
    return true;
}

int gpmi_test(void)
{
    int status;
    
    printf("---- GPMI driver unit test ----\n\n");
    
    BchEccLayout_t ecc;
    status = bch_calculate_best_level(4096, 218, &ecc);
    
    g_actualBufferBytes = 4096;

    status = gpmi_init(0, 0);
    if (status)
    {
        printf("GPMI init failed with error %d\n", status);
        return status;
    }
    
    status = gpmi_nand_configure(3, 2, 128, &ecc);
    if (status)
    {
        printf("gpmi_nand_configure failed with error %d\n", status);
        return status;
    }
    
    // ----------
    
    printf("Sending reset...\n");
    status = gpmi_nand_reset(0);
    if (status)
    {
        printf("Reset failed with error %d\n", status);
        return status;
    }
    
    printf("Reading ID...\n");
    uint8_t idResult[6];
    status = gpmi_nand_read_id(0, (uint8_t *)&idResult);
    if (status)
    {
        printf("Failed to read ID with error %d\n", status);
        return status;
    }
    printf("NAND ID = %02x-%02x-%02x-%02x-%02x-%02x\n", idResult[0], idResult[1], idResult[2], idResult[3], idResult[4], idResult[5]);
    
    // ----------
    
    // Erase block 0.
    printf("Erasing block 0...\n");
    status = gpmi_nand_erase_block(0, 0);
    if (status)
    {
        printf("Failed to erase with error %d\n", status);
        return status;
    }
    
    // Read page 0 of erased block. Compare against erased page.
    printf("Raw read from page 0...\n");
    status = gpmi_nand_read_raw(0, 0, (uint8_t *)&s_read_buffer, 0, 4096);
    if (status)
    {
        printf("Raw read failed with error %d\n", status);
        return status;
    }

    memset(s_page_buffer, 0xff, 4096);
    if (compare_buffers((uint8_t *)&s_page_buffer, (uint8_t *)&s_read_buffer, 4096))
    {
        printf("No bit errors in raw read/write test\n");
    }
    else
    {
        printf("Raw read back comparison failed (may be due to bit errors and not a real problem)!\n");
    }
    
    // Fill buffer with pattern.
    fill_data_buffer((uint8_t *)&s_page_buffer, 0, 0);
    fill_aux((uint8_t *)&s_aux_buffer, 0);
    
    // Raw write to page 0.
    printf("Raw write to page 0...\n");
    status = gpmi_nand_write_raw(0, 0, (uint8_t *)&s_page_buffer, 0, 4096);
    if (status)
    {
        printf("Raw write failed with error %d\n", status);
        return status;
    }
    
    // Raw read from page 0 and compare (which may fail due to bit errors).
    printf("Raw read from page 0...\n");
    status = gpmi_nand_read_raw(0, 0, (uint8_t *)&s_read_buffer, 0, 4096);
    if (status)
    {
        printf("Raw read failed with error %d\n", status);
        return status;
    }

    if (compare_buffers((uint8_t *)&s_page_buffer, (uint8_t *)&s_read_buffer, 4096))
    {
        printf("No bit errors in raw read/write test\n");
    }
    else
    {
        printf("Raw read back comparison failed (may be due to bit errors and not a real problem)!\n");
    }
    
    // ---------- ECC r/w test
    
#if ENABLE_ECC_TEST
    // Erase block 0.
    printf("Erasing block 0...\n");
    status = gpmi_nand_erase_block(0, 0);
    if (status)
    {
        printf("Failed to erase with error %d\n", status);
        return status;
    }
    
    // Write pattern to page 0.
    fill_data_buffer((uint8_t *)&s_page_buffer, 0, 0);
    fill_aux((uint8_t *)&s_aux_buffer, 0);
    
    // Write page 0.
    printf("Writing page 0...\n");
    status = gpmi_nand_write_page(0, 0, (uint8_t *)&s_page_buffer, (uint8_t *)&s_aux_buffer);
    if (status)
    {
        printf("Failed to write page with error %d\n", status);
        return status;
    }
    
    // Read back page 0 and compare.
    printf("Reading page 0...\n");
    status = gpmi_nand_read_page(0, 0, (uint8_t *)&s_read_buffer, (uint8_t *)&s_aux_buffer);
    if (status)
    {
        printf("Failed to read page with error %d\n", status);
        return status;
    }
    
    if (!compare_buffers((uint8_t *)&s_page_buffer, (uint8_t *)&s_read_buffer, g_actualBufferBytes))
    {
        printf("Read back comparison failed!\n");
        return ~0;
    }
#endif // ENABLE_ECC_TEST

    printf("Done!\n");
    
    return status;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
