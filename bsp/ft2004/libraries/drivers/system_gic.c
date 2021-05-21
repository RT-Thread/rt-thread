/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-28 15:05:59
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_gicv3.h"
#include "ft_gicv3_hw.h"
#include "ft_io.h"
#include "ft_printf.h"
#include "ft_cpu.h"
#include "ft_types.h"
#include "ft_assert.h"
#include "ft_aarch32_asm.h"
#include "system_gic.h"

#include "ft_debug.h"
#define SYSTEM_GIC_DEBUG_TAG "SYSTEM_GIC"

#define SYSTEM_GIC_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(SYSTEM_GIC_DEBUG_TAG, format, ##__VA_ARGS__)
#define SYSTEM_GIC_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(SYSTEM_GIC_DEBUG_TAG, format, ##__VA_ARGS__)
#define SYSTEM_GIC_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(SYSTEM_GIC_DEBUG_TAG, format, ##__VA_ARGS__)

FGicv3 gicv3_object = {0};

void System_Gic_Init(void)
{
    Ft_assertVoid((FGicv3_Config_tInitalize(&gicv3_object, FGicv3_LookupConfig(0)) == FST_SUCCESS));
}

void System_Gic_Enable(u32 InterruptID, FGicv3_InterruptHandler_t InterruptHandler, u32 Priority, void *Args)
{
    Ft_assertVoid((FGicV3_Connect(&gicv3_object, InterruptID, InterruptHandler, Priority, Args) == FST_SUCCESS));
    FGicV3_Enable(&gicv3_object, InterruptID);
}

void System_Gic_Disable(u32 InterruptID)
{
    FGicV3_Disconnect(&gicv3_object, InterruptID);
    FGicV3_Disable(&gicv3_object, InterruptID);
}

void System_GicMask(u32 InterruptID)
{
    FGicV3_Enable(&gicv3_object, InterruptID);
}

void System_GicUnMask(u32 InterruptID)
{
    FGicV3_Enable(&gicv3_object, InterruptID);
}

void System_GicSetPriority(u32 InterruptID, u32 Priority)
{
    FGicV3_SetPriority(&gicv3_object, InterruptID, Priority);
}

s32 System_GicGetActiveIrq(void)
{
    return __MRC(15, 0, 12, 12, 0);
}

void System_GicAck(s32 InterruptID)
{
    sys_icc_eoir1_set((u32)InterruptID);
}

__STATIC_INLINE void System_SoftIrqSend(u32 ValLow, u32 ValHigh)
{
    __asm__ __volatile__("MCRR p15,0,%0,%1,c12"
                         :
                         : "r"(ValLow), "r"(ValHigh));
}

ft_error_t System_IpiGen(s32 InterruptID, s32 CpuIdMask)
{
    u32 cnt = 0;
    u8 aff1 = 0,
       aff2 = 0, CpuList = 0;
    volatile u32 LowWord = 0, HighWord = 0;

    for (cnt = 0; cnt < 32; cnt++)
    {
        /* code */
        if ((CpuIdMask >> cnt) & 0x1)
        {
            if (cnt < sizeof(SoftAffiTable) / sizeof(u32))
            {
                CpuList = (u8)(SoftAffiTable[cnt] & 0xff);
                aff1 = (u8)((SoftAffiTable[cnt] >> 8) & 0xff);
                aff2 = (u8)((SoftAffiTable[cnt] >> 16) & 0xff);
                CpuList = 1 << CpuList;
                LowWord |= CpuList;
                LowWord |= (InterruptID & 0xffff) << 24;
                LowWord |= aff1 << 16;
                HighWord |= aff2;
                rt_kprintf("HighWord %x \r\n", HighWord);
                rt_kprintf("LowWord %x \r\n", LowWord);
                System_SoftIrqSend(LowWord, HighWord);

                // SYSTEM_GIC_DEBUG_E("System_IpiGen IS OK cnt is %x  low %x, High %x \r\n", cnt, LowWord, HighWord);
            }
            else
            {
                SYSTEM_GIC_DEBUG_E("CpuId is over max size %x \r\n", CpuIdMask);
                return SYSGIC_FAILURE;
            }
        }
    }

    return SYSGIC_SUCCESS;
}