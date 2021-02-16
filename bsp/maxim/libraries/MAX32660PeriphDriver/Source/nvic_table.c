/* *****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2019-06-05 16:53:29 -0500 (Wed, 05 Jun 2019) $
 * $Revision: 43696 $
 *
 **************************************************************************** */


#include "mxc_config.h"
#include <string.h>
#include "nvic_table.h"

#if !defined (NVIC_USER_IRQ_OFFSET)
    #define NVIC_USER_IRQ_OFFSET 16     /**! Offset for device specific IRQs */
#endif

/* RAM vector_table needs to be aligned with the size of the vector table */
#if defined ( __ICCARM__ )
    #pragma data_alignment = 512
#else
    __attribute__((aligned(512)))
#endif
static void (*ramVectorTable[MXC_IRQ_COUNT])(void);

void NVIC_SetRAM(void)
{
#if defined (__ICCARM__)
    extern void (* const __isr_vector[])(void);
#else
    /* should be defined in starup_<device>.S */
    extern uint32_t __isr_vector[97];
#endif
    
    memcpy(&ramVectorTable, &__isr_vector, sizeof(ramVectorTable));
    SCB->VTOR = (uint32_t)&ramVectorTable;
}

void NVIC_SetVector(IRQn_Type irqn, void(*irq_handler)(void))
{
    int index = irqn + 16;  /* offset for externals */
    
    /* If not copied, do copy */
    if (SCB->VTOR != (uint32_t)&ramVectorTable) {
        NVIC_SetRAM();
    }
    
    ramVectorTable[index] = irq_handler;
    NVIC_EnableIRQ(irqn);
}

uint32_t NVIC_GetVector(IRQn_Type irqn)
{
    uint32_t *vectors = (uint32_t *)SCB->VTOR;
    return vectors[(int32_t)irqn + NVIC_USER_IRQ_OFFSET];
}
