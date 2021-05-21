/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 15:40:19
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_assert.h"
#include "ft_printf.h"
#include "system_gic.h"
#include "ft_generic_timer.h"
#include "ft_aarch32_asm.h"

static void AssertCallback(FT_IN s8 *File, s32 Line)
{
    Ft_printf("Assert Error is %s : %d \r\n", File, Line);
}

void SystemInit(void)
{
    //<! 初始化串口
    Ft_assertSetCallBack(AssertCallback);
    __set_VBAR(0x80100200);
    System_Gic_Init();
}

void SystemInitIrqTable(void)
{
}

/* ----------------------------------------------------------------------------
   -- System_IrqHandler()
   ---------------------------------------------------------------------------- */

void SystemSetupSystick(u32 tickRateHz, void *tickHandler, u32 intPriority)
{
    Ft_printf("SystemSetupSystick %d \r\n", intPriority);
    Ft_GenericTimer_Init(0, tickHandler);
    Ft_GenericTimer_IsrSet(tickRateHz, 1);
    System_Gic_Enable(GEN_TIMER_PHYSICAL_NOSECURE_IRQN, Ft_GenericTimer_IrqHandler, intPriority, NULL);
}

void SystemClearSystickFlag(void)
{
}

void vApplicationIRQHandler(u32 ulICCIAR)
{
    System_IrqHandler(ulICCIAR);
}

u32 SystemGetIRQNestingLevel(void)
{
    return 0;
}

void vAssertCalled(const char *pcFile, unsigned long ulLine)
{
    Ft_assert(pcFile, ulLine);
    while (1)
    {
        /* code */
    }
}

void vApplicationMallocFailedHook(void)
{
    Ft_printf("Malloc Failed\r\n");
    while (1)
        ;
}

void vApplicationTickHook(void)
{
    //Ft_printf("vApplicationTickHook \r\n");
}

void vApplicationIdleHook(void)
{
    //Ft_printf("idle hook is on the way \r\n");
}
