/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-15 11:27:24
 * @LastEditTime: 2021-04-26 17:24:53
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

//#include "FreeRTOS.h"
//#include "task.h"
#include "ft_trace.h"
#include "ft_printf.h"

// typedef struct MEMBLOCK_LINK
// {
//     struct MEMBLOCK_LINK *pxNextFreeBlock; /*<< The next free block in the list. */
//     size_t xBlockSize;                    /*<< The size of the free block. */
// } MEMBlockLink_t;   
void Sdmmc_TraceHeapAlloc(const char *tag)
{
// #ifdef FT_MEM_TRACE_ENABLED
//     MEMBlockLink_t *pNextBlk = pvHeapAllocAddr();
//     FT_MEM_TRACE("<%s> next blk to alloc 0x%p, next next blk to alloc 0x%p", 
//         tag,
//         pNextBlk, 
//         pNextBlk->pxNextFreeBlock);
// #endif
}

void dump_hex(const u8 *ptr, u32 buflen, const char *tag)
{
    unsigned char *buf = (unsigned char *)ptr;
    u32 i, j;

    Ft_printf("dump hex for %s\r\n", tag);
    for (i = 0; i < buflen; i += 16)
    {
        Ft_printf("%08X: ", ptr + i);

        for (j = 0; j < 16; j++)
        {
            if (i + j < buflen)
            {
                Ft_printf("%02X ", buf[i + j]);
            }
            else
            {
                Ft_printf("   ");
            }
        }
        Ft_printf(" ");

        for (j = 0; j < 16; j++)
        {
            if (i + j < buflen)
            {
                Ft_printf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
            }
        }
        Ft_printf("\r\n");
    }
}
